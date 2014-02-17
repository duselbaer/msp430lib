#pragma once

#include "msp430lib/sys/v1/ISys.hpp"

namespace msp430lib {
inline namespace v1 {

  /*!
   * \brief Implementation of ISys suitable for MSP430 microcontrollers
   *
   * \see ISys
   */
  class MSP430_System : public ISys
  {
  public:
    virtual auto init() override -> void;
    virtual auto delay_us(register uint16_t us) const override -> void;
    virtual auto delay_ms(register uint16_t ms) const -> void;
    virtual auto millisecondsSinceStart() const override -> uint32_t;
  };
}
}

