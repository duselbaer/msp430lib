#pragma once

#include "ISys.hpp"

class MSP430_System : public ISys
{
public:
  void init();
  void delay_us(register uint16_t us) const;
};

