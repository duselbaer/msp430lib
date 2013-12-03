#pragma once

#include <stdint.h>
#include <msp430.h>

namespace msp430lib {
inline namespace v1 {

  /*!
   * \brief Generically interfacing the SPI interface provided by an USCI
   *
   * \tparam IF interface description - eg. MSP430_USCI_A0
   */
  template<typename IF>
  class MSP430_USCI_SPI
  {
  public:
    void init()
    {
      static_assert(IF::supports_spi, "Interface type does not support SPI");

      //! \todo Whenever this should be used as a slave - think about the
      //! directions
      // Set MOSI & SCLK as OUTPUT
      // Set MISO as input
      IF::DIR |= IF::MOSI + IF::SCLK;
      IF::DIR &= ~(IF::MISO);

      // Select USCI functions for GPIO pins
      IF::SEL  |= IF::MOSI + IF::SCLK + IF::MISO;
      IF::SEL2 |= IF::MOSI + IF::SCLK + IF::MISO;

      // Put device into RESET mode and start configuring
      IF::CTL1 = UCSWRST;

      // UCCKPH - Data is captured on the first UCLK edge and changed on the following edge.
      // UCSYNC - Synchronous mode
      // UCMST  - Master Mode
      // UCMODE_0 - 3 pin SPI
      // UCMSB  - MSB first
      IF::CTL0 = UCCKPH | UCSYNC | UCMST | UCMODE_0 | UCMSB;

      // UCSSEL_3 - use MLCK
      // Keep RESET
      IF::CTL1 = UCSSEL_3 + UCSWRST;

      // No prescaler - use MCLK
      IF::BR0 = 1;
      IF::BR1 = 0;

      // Clear RESET
      IF::CTL1 &= ~UCSWRST;
    }

    //! \brief Write a byte of data to the SPI and return the read byte
    //!
    //! Sends a byte on the SPI and reads at the same time
    uint8_t shift_data(const uint8_t out)
    {
      // Data written to UCxTXBUF when UCxTXIFG = 0 may result in erroneous data transmission.
      while (!(IFG2 & UCB0TXIFG));

      // Move data to the output buffer
      IF::TXBUF = out;

      // Wait for data to be sent
      while (!(IFG2 & UCB0TXIFG));

      // And return the read data
      return IF::RXBUF;
    }
  };
}
}

