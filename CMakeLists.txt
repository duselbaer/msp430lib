include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(msp430lib STATIC

  src/MSP430_System.cpp
  src/MSP430_USCI_UART.cpp
)
