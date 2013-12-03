#pragma once

#include <stdint.h>

class ISys
{
  public:
    virtual void init() = 0;
    virtual void delay_us(register uint16_t us) const = 0;
};

