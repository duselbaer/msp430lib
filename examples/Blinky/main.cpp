#include "msp430lib/sys/v1/MSP430_System.hpp"

#include <msp430.h>

int main()
{
  // Disable Watchdog, Setup Clock Module
  WDTCTL  = WDTPW + WDTHOLD;  // Stop WDT
  BCSCTL1 = CALBC1_1MHZ;      // Set DCO
  DCOCTL  = CALDCO_1MHZ;

  msp430lib::MSP430_System sys;
  sys.init();

  __eint();

  P1DIR |= BIT0 + BIT6;

  while (1)
  {
    P1OUT |= BIT0;
    sys.delay_ms(500);
    P1OUT &= ~BIT0;
    P1OUT |= BIT6;
    sys.delay_ms(500);
    P1OUT &= ~BIT6;
  }
}
