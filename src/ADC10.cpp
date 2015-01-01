#include <msp430lib/adc/ADC10.hpp>

#include <msp430.h>
#include <msp430g2553.h>

#pragma vector=ADC10_VECTOR
__interrupt void adc10Interrupt(void)
{
  LPM1_EXIT;
}

namespace msp430lib {

  ADC10::ADC10(uint8_t const channel)
  {
    ADC10CTL0 = 0
      /* | ADC10SREF_0 */ // VR+ = Vcc, VR- = Vss
      | ADC10SHT_3        // 64 x ADC10CLK
      | ADC10SR           // 50 ksps
      /* | REFOUT */      // REFOUT disabled
      | REFBURST          // Reference buffer only during sample and conversion
      /* | MSC */         // the sampling requires a rising edge of the SHI signal
      | REF2_5V           // 2.5V reference
      | REFON             // see above
      | ADC10ON           // enable ADC10
      | ADC10IE           // enable ADC10 interrupt
    ;

    ADC10CTL1 = ((uint16_t) channel << 12)
      |SHS_0               // ADC10SC bit starts conversion
      /* |ADC10DF */       // Straight binary
      /* |ISSH */          // Sample and Hold not inverted
      | ADC10DIV_7         // ADC10 clock divider = 8
      | ADC10SSEL_3        // SMCLK is source for ADC10
      | CONSEQ_0           // Single Channel single conversion
    ;

    // Enable analog input
    if (channel < 8)
    {
      ADC10AE0 |= (1 << channel);
    }

    // Analog inputs > 8 are only available on MSP430F22xx
  }

  uint16_t ADC10::singleConversion() const
  {
    ADC10CTL0 |= ENC |ADC10SC; // Enable and start conversion

    while ((ADC10CTL1 & ADC10BUSY) == ADC10BUSY)
    {
      LPM1;
    }

    return ADC10MEM;
  }

}
