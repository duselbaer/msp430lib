#pragma once

#include <stdint.h>
#include <msp430.h>

struct MSP430_USCI_A0
{
  constexpr static bool supports_uart = true;
  constexpr static bool supports_spi = true;
  constexpr static bool supports_i2c = true;

  constexpr static uint8_t RXD = BIT1;
  constexpr static uint8_t TXD = BIT2;

  constexpr static volatile uint8_t& SEL  = P1SEL;
  constexpr static volatile uint8_t& SEL2 = P1SEL2;

  constexpr static volatile uint8_t& CTL0 = UCA0CTL0;
  constexpr static volatile uint8_t& CTL1 = UCA0CTL1;

  constexpr static volatile uint8_t& TXBUF = UCA0TXBUF;

  constexpr static volatile uint8_t& BR0 = UCA0BR0;
  constexpr static volatile uint8_t& BR1 = UCA0BR1;

  constexpr static volatile uint8_t& MCTL = UCA0MCTL;
};

