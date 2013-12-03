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
    virtual void init() override;
    virtual void delay_us(register uint16_t us) const override;
  };
}
}

