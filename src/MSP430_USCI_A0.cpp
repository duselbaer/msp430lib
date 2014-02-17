#include "msp430lib/usci/v1/MSP430_USCI_A0.hpp"

namespace msp430lib {
namespace v1 {

    constexpr bool MSP430_USCI_A0::supports_uart;
    constexpr bool MSP430_USCI_A0::supports_spi;
    constexpr bool MSP430_USCI_A0::supports_i2c;

    constexpr uint8_t MSP430_USCI_A0::RXD;
    constexpr uint8_t MSP430_USCI_A0::TXD;

    constexpr volatile uint8_t& MSP430_USCI_A0::SEL;
    constexpr volatile uint8_t& MSP430_USCI_A0::SEL2;

    constexpr volatile uint8_t& MSP430_USCI_A0::CTL0;
    constexpr volatile uint8_t& MSP430_USCI_A0::CTL1;

    constexpr volatile uint8_t& MSP430_USCI_A0::TXBUF;

    constexpr volatile uint8_t& MSP430_USCI_A0::BR0;
    constexpr volatile uint8_t& MSP430_USCI_A0::BR1;

    constexpr volatile uint8_t& MSP430_USCI_A0::MCTL;
}
}

