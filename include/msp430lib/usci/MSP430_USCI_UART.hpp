#pragma once

#include <stdint.h>
#include <msp430.h>

template<typename IF>
class MSP430_USCI_UART
{
public:
  //! Initialize the Port
  void init()
  {
    static_assert(IF::supports_uart, "Interface type does not support UART");

    // RESET
    IF::CTL1 |= UCSWRST;

    // Configure Port1
    IF::SEL  |= IF::TXD + IF::RXD;
    IF::SEL2 |= IF::TXD + IF::RXD;

    // Use SMCLK
    IF::CTL1 |= UCSSEL_2;

    // Baudrate
    setBaudrate(9600);

    // ENABLE AGAIN
    IF::CTL1 &= ~UCSWRST;

    // ENABLE RX INTERRUPT
    IE2 |= UCA0RXIE;
  }

  //! Write a character to the serial port
  void putc(const uint8_t c)
  {
    // Wait for the TX buffer to become ready
    while (!(IFG2&UCA0TXIFG));

    IF::TXBUF = c;
  }

  //! Blocking get character
  uint8_t getc()
  {
    //! \todo Implement
    return 0;
  }

  //! Change Baudrate
  void setBaudrate(const uint32_t baudrate)
  {
    // Baudrate
    // Clock prescaler setting of the Baud rate generator.
    // The 16-bit value of (UCAxBR0 + UCAxBR1 × 256) forms the prescaler value.
    IF::BR0 = (F_CPU / baudrate) % 0xFF;
    IF::BR1 = ((F_CPU / baudrate) % 0xFF00) >> 8;

    //! \todo Look @ Table 15-5 @ Family Users Guide
    IF::MCTL = UCBRS0;
  }
};

