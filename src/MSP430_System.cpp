#include "msp430lib/sys/v1/MSP430_System.hpp"
#include <msp430.h>

namespace {
  volatile uint32_t milliseconds_since_start = 0;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void systickTimerInterrupt(void)
{
  milliseconds_since_start++;
  LPM1_EXIT;
}

#define USE_ASM_SPINNING    1
//--------------------------------------------------------------------------------------------------
#if(USE_ASM_SPINNING == 1)
#if defined(__GNUC__) && defined(__MSP430__)
// MSPGCC
#define ARG32_MSB    "R15"
#define ARG32_LSB    "R14"

#elif defined(__TI_COMPILER_VERSION__)
// TI's Code Composer Studio
#define ARG32_MSB    "R13"
#define ARG32_LSB    "R12"

#else
#error "Compiler not supported yet."
#endif

static void asmspin(uint32_t count){
  // count SHOULD always be located at R13:R12 when compiling with CCS
  // count SHOULD always be located at R15:R14 when compiling with MSPGCC

  // Loop until count == 0 (8 cycles/loop)
  __asm__("  nop             ");        // 1 // Loop1:
  __asm__("  nop             ");        // 1
  __asm__("  nop             ");        // 1
  __asm__("  nop             ");        // 1 // Loop2:
  __asm__("  dec.w " ARG32_LSB);        // 1
  __asm__("  sbc.w " ARG32_MSB);        // 1
  __asm__("  jnz $-12        ");        // 2 // jnz Loop1
  __asm__("  tst.w " ARG32_LSB);        // 1
  __asm__("  jnz $-10        ");        // 2 // jnz Loop2
}
#endif

//--------------------------------------------------------------------------------------------------

namespace msp430lib {
namespace v1 {

auto MSP430_System::delay_us(register uint16_t us) const -> void
{
  while (us--)
  {
    __delay_cycles( F_CPU / 1000000UL );
  }
}

void MSP430_System::init()
{
  // The internal very-low-power low-frequency oscillator (VLO) provides a typical frequency
  // of 12 kHz (see device-specific data sheet for parameters) without requiring a crystal.
  // VLOCLK source is selected by setting LFXT1Sx = 10 when XTS = 0. The OSCOFF bit disables
  // the VLO for LPM4. The LFXT1 crystal oscillators are disabled when the VLO is selected
  // reducing current consumption. The VLO consumes no power when not being used.
  //
  // Devices without LFXT1 (for example, the MSP430G22x0) should be configured to use
  // the VLO as ACLK.
  BCSCTL1 &= ~XTS;
  BCSCTL3 &= ~LFXT1S_3;
  BCSCTL3 |= LFXT1S_2;

  // Setup the Systick Timer
  milliseconds_since_start = 0;

  // TASSEL2 - SMCLK
  // ID3 - DIVIDER 8
  TA0CTL = TASSEL_1 | ID_1 ; // SRC = ACLK / 2
  TA0CCTL0 = CCIE;
  TA0CCR0  = 3; // count up to 3, then down, then IRQ - using ACLK / 2 this results in 1 kHz
  TA0CTL |= MC_3;
}

auto MSP430_System::millisecondsSinceStart() const -> uint32_t
{
  return milliseconds_since_start;
}

auto MSP430_System::delay_ms(register uint16_t ms) const -> void
{
  uint32_t wait_until = millisecondsSinceStart() + ms;
  while (millisecondsSinceStart() < wait_until)
  {
    LPM3;
  }
}
}
}

