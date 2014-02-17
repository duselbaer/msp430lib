#include "msp430lib/usci/v1/MSP430_USCI_B0.hpp"

namespace msp430lib {
namespace v1 {

    constexpr bool MSP430_USCI_B0::supports_uart;
    constexpr bool MSP430_USCI_B0::supports_spi;
    constexpr bool MSP430_USCI_B0::supports_i2c;

    constexpr volatile uint8_t& MSP430_USCI_B0::DIR;

    constexpr volatile uint8_t& MSP430_USCI_B0::SEL;
    constexpr volatile uint8_t& MSP430_USCI_B0::SEL2;

    constexpr volatile uint8_t& MSP430_USCI_B0::CTL0;
    constexpr volatile uint8_t& MSP430_USCI_B0::CTL1;

    constexpr volatile uint8_t& MSP430_USCI_B0::TXBUF;
    constexpr const volatile uint8_t& MSP430_USCI_B0::RXBUF;

    constexpr volatile uint8_t& MSP430_USCI_B0::BR0;
    constexpr volatile uint8_t& MSP430_USCI_B0::BR1;

    constexpr uint8_t MSP430_USCI_B0::MOSI;
    constexpr uint8_t MSP430_USCI_B0::MISO;
    constexpr uint8_t MSP430_USCI_B0::SCLK;
}
}

