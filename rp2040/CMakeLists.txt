cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK
include(pico_sdk_import.cmake)

if (NOT PICO_SDK_VERSION_STRING VERSION_EQUAL "1.5.1")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.5.1 required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(target_name itxllama-rp2040)
set(target_version 0.2)
project(${target_name} C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(${target_name} main.c ps2x2pico/src/usbin.c ps2x2pico/src/scancodes.c ps2x2pico/src/ps2kb.c ps2x2pico/src/ps2ms.c ps2x2pico/src/ps2out.c)

target_sources(${target_name} PRIVATE
 # can use 'tinyusb_pico_pio_usb' library later when pico-sdk is updated
 ${PICO_TINYUSB_PATH}/src/portable/raspberrypi/pio_usb/hcd_pio_usb.c
)

pico_generate_pio_header(${target_name} ${CMAKE_CURRENT_LIST_DIR}/ps2x2pico/src/ps2out.pio)

 # print memory usage, enable all warnings
target_link_options(${target_name} PRIVATE -Xlinker --print-memory-usage)
target_compile_options(${target_name} PRIVATE -Wall -Wextra)

# use tinyusb implementation
target_compile_definitions(${target_name} PRIVATE PIO_USB_USE_TINYUSB)

pico_set_program_name(${target_name} ${target_name})
pico_set_program_version(${target_name} ${target_version})

add_compile_definitions(PICO_XOSC_STARTUP_DELAY_MULTIPLIER=64)
add_compile_definitions(PICO_DEFAULT_UART_TX_PIN=12)
add_compile_definitions(PICO_DEFAULT_UART_RX_PIN=13)

pico_enable_stdio_uart(${target_name} 1)
pico_enable_stdio_usb(${target_name} 0)

add_subdirectory("./Pico-PIO-USB" pico_pio_usb)
target_include_directories(${target_name} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(${target_name} pico_stdlib hardware_pio tinyusb_host tinyusb_board pico_pio_usb)

pico_add_extra_outputs(${target_name})
