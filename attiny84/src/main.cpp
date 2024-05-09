#include <Arduino.h>
#include <EEPROM.h>
#include <TinyWireS.h>

#define PWR_LED_PIN   PA0
#define HDD_LED_PIN   PA1
#define RED_PIN       PA2
#define GREEN_PIN     PA3
#define CLICK_PIN     PA5
#define CLICK_PIN_A   PIN_PA5
#define ON_PIN        PB3
#define SD_CMD_PIN    PB2
#define SD_CMD_PCI    PCINT10
#define SD_DAT0_PIN   PA7
#define SD_DAT0_PCI   PCINT7

#define I2C_SLAVE_ADDRESS 0x20

#define I2C_LED_ENABLED_REG     0x01  // RW - 0x00 - disabled, 0x01 - enabled
#define I2C_LED_INTENSITY_REG   0x02  // RW - 0x00-0xFF, 0-100% intensity

#define I2C_CLICK_ENABLED_REG   0x11  // RW - 0x00 - disabled, 0x01 - enabled

#define EEPROM_LED_VALUES_MODIFIED_ADDRESS    (int)0x00
#define EEPROM_LED_ENABLED_ADDRESS            (int)0x01
#define EEPROM_LED_INTENSITY_ADDRESS          (int)0x02

#define EEPROM_CLICK_VALUES_MODIFIED_ADDRESS  (int)0x10
#define EEPROM_CLICK_ENABLED_ADDRESS          (int)0x11

#define EEPROM_MODIFIED_MAGIC_BYTE 0x55

#define LED_DEFAULT_ENABLED     1
#define LED_DEFAULT_INTENSITY   64   // 25% of 255
#define CLICK_DEFAULT_ENABLED   1
#define CLICK_DEFAULT_FREQ      30   // Hz
#define CLICK_DEFAULT_DURATION  20   // ms
#define CLICK_DEFAULT_PAUSE     3    // ms

#define LED_FREQ 100 // Hz

enum ActState : uint8_t { ACT_IDLE, ACT_ON, ACT_OFF };

enum LEDState : uint8_t { LED_OFF, LED_ON };

volatile uint8_t sd_act = 0;

ActState act_state                = ACT_IDLE;
unsigned long act_timer_start     = 0;
unsigned long click_freq          = CLICK_DEFAULT_FREQ;            // Hz
unsigned long click_timer_period  = CLICK_DEFAULT_DURATION * 1000; // microseconds
unsigned long click_pause         = CLICK_DEFAULT_PAUSE * 1000;    // microseconds

unsigned long led_cycle_length    = 1000000 / LED_FREQ;            // microseconds

LEDState red_led_state              = LED_OFF;
unsigned long red_led_timer_start   = 0;
uint8_t red_led_pwm_duty            = LED_DEFAULT_INTENSITY;
LEDState green_led_state            = LED_OFF;
unsigned long green_led_timer_start = 0;
uint8_t green_led_pwm_duty          = LED_DEFAULT_INTENSITY;

uint8_t global_led_enabled          = LED_DEFAULT_ENABLED;
uint8_t global_click_enabled        = CLICK_DEFAULT_ENABLED;

uint8_t pwr_led_on = 0;
uint8_t hdd_led_on = 0;

volatile uint8_t i2c_received_byte = 0xFF;
uint8_t i2c_reg = 0xFF;

ISR(PCINT0_vect) {
  sd_act = 1;
}

// ISR(PCINT1_vect) {
//   sd_act = 1;
// }

void receiveEvent(uint8_t howMany) {
  if (howMany != 1) return;
  i2c_received_byte = TinyWireS.receive();
}

void requestEvent(void) {
  if (i2c_reg == 0xFF) { // can't read from register without setting its address first
    TinyWireS.send(0x00);
    return;
  }
  switch (i2c_reg) {
    case I2C_LED_ENABLED_REG: {
      TinyWireS.send(global_led_enabled);
      break;
    }
    case I2C_LED_INTENSITY_REG: {
      TinyWireS.send(red_led_pwm_duty);
      break;
    }
    case I2C_CLICK_ENABLED_REG: {
      TinyWireS.send(global_click_enabled);
      break;
    }
    default: {
      TinyWireS.send(0x00);
      break;
    }
  }
  i2c_reg = 0xFF;
}

void processAct(unsigned long micros, uint8_t act) {
  switch (act_state) {
    case ACT_IDLE: {
      if (act) {
        act_timer_start = micros;
        if (global_click_enabled) {
          tone(CLICK_PIN_A, click_freq);
        }
        act_state = ACT_ON;
      }
      break;
    }
    case ACT_ON: {
      if ((micros - act_timer_start) > click_timer_period) {
        noTone(CLICK_PIN_A);
        act_timer_start = micros;
        act_state = ACT_OFF;
      }
      break;
    }
    case ACT_OFF: {
      if ((micros - act_timer_start) > click_pause) {
        act_state = ACT_IDLE;
      }
    }
  }
}

void processLEDs(unsigned long micros) {

  uint8_t has_power = PINB & _BV(ON_PIN);
  uint8_t process_red = !has_power || act_state == ACT_ON;
  uint8_t process_green = has_power;

  if (has_power && global_led_enabled) {
    if (!pwr_led_on) {
      PORTA |= _BV(PWR_LED_PIN);
      pwr_led_on = 1;
    }
  } else {
    if (pwr_led_on) {
      PORTA &= ~_BV(PWR_LED_PIN);
      pwr_led_on = 0;
    }
  }

  if (act_state == ACT_ON && global_led_enabled) {
    if (!hdd_led_on) {
      PORTA |= _BV(HDD_LED_PIN);
      hdd_led_on = 1;
    }
  } else {
    if (hdd_led_on) {
      PORTA &= ~_BV(HDD_LED_PIN);
      hdd_led_on = 0;
    }
  }

  if (process_red) {
    if (!process_green) PORTA &= ~_BV(GREEN_PIN);
    unsigned long on_time = led_cycle_length * red_led_pwm_duty / 0xFF;
    unsigned long off_time = led_cycle_length - on_time;
    switch (red_led_state) {
      case LED_OFF: {
        if ((micros - red_led_timer_start) > off_time) {
          if (global_led_enabled) {
            PORTA |= _BV(RED_PIN);
          }
          red_led_timer_start = micros;
          red_led_state = LED_ON;
        }
        break;
      }
      case LED_ON: {
        if ((micros - red_led_timer_start) > on_time) {
          PORTA &= ~_BV(RED_PIN);
          red_led_timer_start = micros;
          red_led_state = LED_OFF;
        }
        break;
      }
    }
  }

  if (process_green) {
    if (!process_red) PORTA &= ~_BV(RED_PIN);
    unsigned long on_time = led_cycle_length * green_led_pwm_duty / 0xFF;
    unsigned long off_time = led_cycle_length - on_time;
    switch (green_led_state) {
      case LED_OFF: {
        if ((micros - green_led_timer_start) > off_time) {
          if (global_led_enabled) {
            PORTA |= _BV(GREEN_PIN);
          }
          green_led_timer_start = micros;
          green_led_state = LED_ON;
        }
        break;
      }
      case LED_ON: {
        if ((micros - green_led_timer_start) > on_time) {
          PORTA &= ~_BV(GREEN_PIN);
          green_led_timer_start = micros;
          green_led_state = LED_OFF;
        }
        break;
      }
    }
  }
}

void processI2C(void) {
  uint8_t byte = i2c_received_byte;
  if (i2c_reg == 0xFF) { // no register set, hopefully the received byte is a call to set the address
    switch (byte) {
      case I2C_LED_ENABLED_REG: {
        i2c_reg = I2C_LED_ENABLED_REG;
        break;
      }
      case I2C_LED_INTENSITY_REG: {
        i2c_reg = I2C_LED_INTENSITY_REG;
        break;
      }
      case I2C_CLICK_ENABLED_REG: {
        i2c_reg = I2C_CLICK_ENABLED_REG;
        break;
      }
      default: break;
    }
  } else { // call to write to register
    switch (i2c_reg) {
      case I2C_LED_ENABLED_REG: {
        global_led_enabled = byte;
        EEPROM.update(EEPROM_LED_ENABLED_ADDRESS, byte);
        break;
      }
      case I2C_LED_INTENSITY_REG: {
        red_led_pwm_duty = byte;
        green_led_pwm_duty = byte;
        EEPROM.update(EEPROM_LED_INTENSITY_ADDRESS, byte);
        break;
      }
      case I2C_CLICK_ENABLED_REG: {
        global_click_enabled = byte;
        EEPROM.update(EEPROM_CLICK_ENABLED_ADDRESS, byte);
        break;
      }
      default: break;
    }
    i2c_reg = 0xFF;
  }
  i2c_received_byte = 0xFF;
}

void load_eeprom_values(void) {
  uint8_t led_values_modified = EEPROM.read(EEPROM_LED_VALUES_MODIFIED_ADDRESS);
  if (led_values_modified == EEPROM_MODIFIED_MAGIC_BYTE) {
    global_led_enabled = EEPROM.read(EEPROM_LED_ENABLED_ADDRESS);
    uint8_t led_intensity = EEPROM.read(EEPROM_LED_INTENSITY_ADDRESS);
    red_led_pwm_duty = led_intensity;
    green_led_pwm_duty = led_intensity;
  } else {
    EEPROM.update(EEPROM_LED_ENABLED_ADDRESS, LED_DEFAULT_ENABLED);
    delay(5);
    EEPROM.update(EEPROM_LED_INTENSITY_ADDRESS, LED_DEFAULT_INTENSITY);
    delay(5);
    EEPROM.update(EEPROM_LED_VALUES_MODIFIED_ADDRESS, EEPROM_MODIFIED_MAGIC_BYTE);
    delay(5);
  }

  uint8_t click_values_modified = EEPROM.read(EEPROM_CLICK_VALUES_MODIFIED_ADDRESS);
  if (click_values_modified == EEPROM_MODIFIED_MAGIC_BYTE) {
    global_click_enabled = EEPROM.read(EEPROM_CLICK_ENABLED_ADDRESS);
  } else {
    EEPROM.update(EEPROM_CLICK_ENABLED_ADDRESS, CLICK_DEFAULT_ENABLED);
    delay(5);
    EEPROM.update(EEPROM_CLICK_VALUES_MODIFIED_ADDRESS, EEPROM_MODIFIED_MAGIC_BYTE);
    delay(5);
  }
}

void setup() {
  DDRA &= ~_BV(SD_DAT0_PIN); // define as input
  DDRA |= _BV(PWR_LED_PIN) | // define as outputs
          _BV(HDD_LED_PIN) |
          _BV(RED_PIN)     |
          _BV(GREEN_PIN)   |
          _BV(CLICK_PIN);
  PORTA |= _BV(SD_DAT0_PIN); // pull-up

  DDRB &= ~(_BV(ON_PIN) | _BV(SD_CMD_PIN)); // define as inputs
  PORTB |= _BV(ON_PIN) | _BV(SD_CMD_PIN); // pull-up

  load_eeprom_values();

  // init interrupt
  cli();
  GIMSK = _BV(PCIE0);
  //GIMSK |= _BV(PCIE0) | _BV(PCIE1);
  PCMSK0 = _BV(SD_DAT0_PCI);
  //PCMSK1 |= _BV(SD_CMD_PCI);
  sei();

  TinyWireS.begin(I2C_SLAVE_ADDRESS);
  TinyWireS.onReceive(receiveEvent);
  TinyWireS.onRequest(requestEvent);
}

void loop() {
  TinyWireS_stop_check();
  if (i2c_received_byte != 0xFF) {
    processI2C();
  }
  unsigned long micros_now = micros();
  uint8_t act = sd_act;
  cli();
  sd_act = 0;
  sei();
  processAct(micros_now, act);
  processLEDs(micros_now);
}
