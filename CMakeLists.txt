include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(
  msp430lib STATIC

    src/MSP430_System.cpp
    src/MSP430_USCI_A0.cpp
    src/MSP430_USCI_B0.cpp
    src/MSP430_USCI_UART.cpp
    src/ADC10.cpp
)
