#pragma once

#include <stdint.h>
#include <msp430.h>

namespace msp430lib {
inline namespace v1 {

  /*!
   * \brief Structure describing the USCI_A0 interface
   *
   * \note Currently specific to the MSP430G2553
   */
  struct MSP430_USCI_B0
  {
    constexpr static bool supports_uart = false;
    constexpr static bool supports_spi = true;
    constexpr static bool supports_i2c = true;

    constexpr static volatile uint8_t& DIR  = P1DIR;

    constexpr static volatile uint8_t& SEL  = P1SEL;
    constexpr static volatile uint8_t& SEL2 = P1SEL2;

    constexpr static volatile uint8_t& CTL0 = UCB0CTL0;
    constexpr static volatile uint8_t& CTL1 = UCB0CTL1;

    constexpr static volatile uint8_t& TXBUF = UCB0TXBUF;
    constexpr static const volatile uint8_t& RXBUF = UCB0RXBUF;

    constexpr static volatile uint8_t& BR0 = UCB0BR0;
    constexpr static volatile uint8_t& BR1 = UCB0BR1;

    constexpr static uint8_t MOSI = BIT7;
    constexpr static uint8_t MISO = BIT6;
    constexpr static uint8_t SCLK = BIT5;
  };
}
}

