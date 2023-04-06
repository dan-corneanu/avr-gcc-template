# Taken from Nicolas Goy
# https://www.kuon.ch/post/2018-07-11-avr-cmake/

# For a somehow more portable version of an AVR CMake Toolchain
# see https://nnarain.github.io/2016/03/29/AVR-CMake-Toolchain.html
cmake_minimum_required(VERSION 3.25)
set (CMAKE_CXX_STANDARD 11)

## AVR Chip Configuration
# 16Mhz clock
set(F_CPU 16000000UL)

# CPU, you can find the list here:
# https://gcc.gnu.org/onlinedocs/gcc/AVR-Options.html
set(MCU atmega328p)

# AVR Fuses, must be in concordance with your hardware and F_CPU
# http://eleccelerator.com/fusecalc/fusecalc.php?chip=atmega328p
set(E_FUSE 0xfd)
set(H_FUSE 0xda)
set(L_FUSE 0xff)

# Default Baudrate for UART, read avr include/util/setbaud.h for usage
set(UART_BAUD_RATE 9600)

# The programmer to use, read avrdude manual for list
set(PROG_TYPE usbtiny)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER_VERSION 4.5)

include(cmake/avr-gcc.toolchain.cmake)

# Product filename
set(PRODUCT_NAME avr-template)

project("avr-template"
  DESCRIPTION "Template project for avr-gcc development, based on CMake.")

# Explicitely list all dependencies.
list(APPEND SRC_FILES
  "src/main.c"
  "src/drivers/uart/uart.c")

# Create one target
add_executable(${PRODUCT_NAME} ${SRC_FILES})

target_include_directories(${PRODUCT_NAME} PRIVATE
  "headers"
)

# Rename the output to .elf as we will create multiple files
set_target_properties(${PRODUCT_NAME} PROPERTIES OUTPUT_NAME ${PRODUCT_NAME}.elf)

# Strip binary for upload
add_custom_target(strip ALL avr-strip ${PRODUCT_NAME}.elf DEPENDS ${PRODUCT_NAME})

# Transform binary into hex file, we ignore the eeprom segments in the step
add_custom_target(hex ALL avr-objcopy -R .eeprom -O ihex ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.hex DEPENDS strip)

# Transform binary into hex file, this is the eeprom part (empty if you don't
# use eeprom static variables)
# add_custom_target(eeprom avr-objcopy -j .eeprom  --set-section-flags=.eeprom="alloc,load"  --change-section-lma .eeprom=0 -O ihex ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.eep DEPENDS strip)

# Upload the firmware with avrdude
add_custom_target(upload avrdude  -c ${PROG_TYPE} -p ${MCU} -U flash:w:${PRODUCT_NAME}.hex DEPENDS hex)

# Burn fuses.
# !!!! Be careful with this one.
# add_custom_target(fuses avrdude -c ${PROG_TYPE} -p ${MCU}  -U lfuse:w:${L_FUSE}:m -U hfuse:w:${H_FUSE}:m -U efuse:w:${E_FUSE}:m )

# Clean extra files
set_directory_properties(PROPERTIES ADDITIONAL_CLEAN_FILES "${PRODUCT_NAME}.hex;${PRODUCT_NAME}.eeprom;${PRODUCT_NAME}.lst")
