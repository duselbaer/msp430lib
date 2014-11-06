set(CMAKE_TOOLCHAIN_FILE "cmake/msp430.cmake")

project(SerialCommunication)
cmake_minimum_required(VERSION 2.8)

# Configuration
# =============
#
set(CONF_FREQUENCY_IN_HZ "16000000UL" CACHE STRING "CPU frequency used")

# RF2500 UPLOAD
add_custom_target(upload
  COMMAND mspdebug rf2500 "prog SerialCommunication"
  DEPENDS SerialCommunication
  COMMENT "Uploading SerialCommunication")

# Compiler Settings
add_definitions("-DF_CPU=${CONF_FREQUENCY_IN_HZ}")

# MSP430Lib
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)
add_subdirectory("../.." msp430lib)

add_executable(
  SerialCommunication
    main.cpp
)
target_link_libraries(
  SerialCommunication
    msp430lib
)
