cmake_minimum_required(VERSION 3.13)
include (pico_sdk_import.cmake)
project(itxllama-rp2040)

pico_sdk_init()

add_subdirectory("./Pico-PIO-USB" pico_pio_usb)

set(target_name itxllama-rp2040)
add_executable(${target_name})
target_sources(${target_name} PRIVATE
 main.c
 # can use 'tinyusb_pico_pio_usb' library later when pico-sdk is updated
 ${PICO_TINYUSB_PATH}/src/portable/raspberrypi/pio_usb/dcd_pio_usb.c
 ${PICO_TINYUSB_PATH}/src/portable/raspberrypi/pio_usb/hcd_pio_usb.c
 )

 # print memory usage, enable all warnings
target_link_options(${target_name} PRIVATE -Xlinker --print-memory-usage)
target_compile_options(${target_name} PRIVATE -Wall -Wextra)

# use tinyusb implementation
target_compile_definitions(${target_name} PRIVATE PIO_USB_USE_TINYUSB PICO_XOSC_STARTUP_DELAY_MULTIPLIER=128)
# target_compile_definitions(${target_name} PUBLIC CFG_TUSB_DEBUG=3)

# needed so tinyusb can find tusb_config.h
target_include_directories(${target_name} PRIVATE ${CMAKE_CURRENT_LIST_DIR})

add_compile_definitions(DEBUG=0)
add_compile_definitions(PICO_DEFAULT_UART_TX_PIN=12)
add_compile_definitions(PICO_DEFAULT_UART_RX_PIN=13)
add_compile_definitions(PICO_DEFAULT_UART_BAUD_RATE=115200)

pico_enable_stdio_uart(${target_name} 1)
pico_enable_stdio_usb(${target_name} 0)

target_link_libraries(${target_name} PRIVATE pico_stdlib pico_pio_usb tinyusb_host)
pico_add_extra_outputs(${target_name})
