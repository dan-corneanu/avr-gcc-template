# Uart library

cmake_minimum_required(VERSION 3.25)
set (CMAKE_CXX_STANDARD 11)

project(uart
  DESCRIPTION "Interrupt UART library with receive/transmit circular buffers")

add_library(uart STATIC
  "src/uart.c")

target_include_directories(uart
   PUBLIC "headers")
