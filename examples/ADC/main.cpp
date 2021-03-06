#include "msp430lib/adc/ADC10.hpp"

#include "msp430lib/usci/v1/MSP430_USCI_UART.hpp"
#include "msp430lib/usci/v1/MSP430_USCI_A0.hpp"

#include "msp430lib/utils/Output.hpp"

#include <stdio.h>

int main()
{
  // Disable Watchdog, Setup Clock Module
  WDTCTL  = WDTPW + WDTHOLD;  // Stop WDT
  BCSCTL1 = CALBC1_16MHZ;      // Set DCO
  DCOCTL  = CALDCO_16MHZ;

  typedef msp430lib::MSP430_USCI_UART<msp430lib::MSP430_USCI_A0> UART_HW;
  UART_HW uart;
  uart.init();

  // Output Stream
  msp430lib::Output<UART_HW> os(uart);

  // ADC
  msp430lib::ADC10 adc(msp430lib::ADC10_VCC_2);

  os << "Continuously sending the VCC/2 ADC result" << "\n";
  __eint();

  while (1)
  {
    uint32_t temp = (adc.singleConversion() * 5); /* Vcc_2 * 2 * (2500/1024) is about Vcc_2 * 5 */

    os << "VCC/2 = " << temp << " mV\n";
  }
}
