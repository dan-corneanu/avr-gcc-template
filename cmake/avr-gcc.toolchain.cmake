# Check that all mandatory variables are defined.  TODO: Define custom
# functino that checks that all variables in a list of mandatory
# variables are defined.
if(NOT DEFINED F_CPU)
  message(FATAL_ERROR "Mandatory F_CPU variable not defined.")
endif()  
if(NOT DEFINED MCU)
  message(FATAL_ERROR "Mandatory MCU variable not defined.")
endif()  
if(NOT DEFINED E_FUSE)
  message(FATAL_ERROR "Mandatory E_FUSE variable not defined.")
endif()  
if(NOT DEFINED H_FUSE)
  message(FATAL_ERROR "Mandatory H_FUSE variable not defined.")
endif()  
if(NOT DEFINED L_FUSE)
  message(FATAL_ERROR "Mandatory L_FUSE variable not defined.")
endif()
if(NOT DEFINED BAUD)
  message(FATAL_ERROR "Mandatory BAUD variable not defined.")
endif()  
if(NOT DEFINED PROG_TYPE)
  message(FATAL_ERROR "Mandatory PROG_TYPE variable not defined.")
endif()

# Use AVR GCC toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_ASM_COMPILER avr-gcc)

# Pass defines to compiler
add_definitions(
    -DF_CPU=${F_CPU}
    -DBAUD=${BAUD}
)

# mmcu MUST be passed to both the compiler and linker. This set
# directive handles the linker.
set(CMAKE_EXE_LINKER_FLAGS -mmcu=${MCU})

# TODO: Set different compiler options based on the value of
# CMAKE_BUILD_TYPE. Check documentation at
# https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html
add_compile_options(
    -mmcu=${MCU} # MCU
    -std=gnu99 # C99 standard
    -Os # optimize
    -Wall # enable warnings
    -Wno-main
    -Wundef
    -pedantic
    -Wstrict-prototypes
    -Werror
    -Wfatal-errors
    -Wl,--relax,--gc-sections
    -g
    -gdwarf-2
    -funsigned-char # a few optimizations
    -funsigned-bitfields
    -fpack-struct
    -fshort-enums
    -ffunction-sections
    -fdata-sections
    -fno-split-wide-types
    -fno-tree-scev-cprop
)

# add_link_options(
#     LINKER:-Map,output.map
# )
