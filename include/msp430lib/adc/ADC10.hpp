#pragma once

#include <stdint.h>

namespace msp430lib {

  static constexpr uint8_t ADC10_A0 = 0;
  static constexpr uint8_t ADC10_A1 = 1;
  static constexpr uint8_t ADC10_A2 = 2;
  static constexpr uint8_t ADC10_A3 = 3;
  static constexpr uint8_t ADC10_A4 = 4;
  static constexpr uint8_t ADC10_A5 = 5;
  static constexpr uint8_t ADC10_A6 = 6;
  static constexpr uint8_t ADC10_A7 = 7;
  static constexpr uint8_t ADC10_A12 = 12;
  static constexpr uint8_t ADC10_A13 = 13;
  static constexpr uint8_t ADC10_A14 = 14;
  static constexpr uint8_t ADC10_A15 = 15;

  static constexpr uint8_t ADC10_VCC_2 = 11;

  class ADC10 {
  public:
    ADC10(uint8_t const channel);

    uint16_t singleConversion() const;

  protected:

  private:
  };
}

