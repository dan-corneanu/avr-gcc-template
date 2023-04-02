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
set(BAUD 9600)

# The programmer to use, read avrdude manual for list
set(PROG_TYPE usbtiny)

include(cmake/avr-gcc.toolchain.cmake)

# Product filename
set(PRODUCT_NAME avr-template)

project("avr-template"
  DESCRIPTION "Template project for avr-gcc development, based on CMake.")

file(GLOB SRC_FILES
  "src/*.c")

# Create one target
add_executable(${PRODUCT_NAME} ${SRC_FILES})

# target_include_directories(${PRODUCT_NAME} PUBLIC
#   "headers"
# )
