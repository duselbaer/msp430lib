#include "MSP430_System.hpp"
#include <msp430g2553.h>

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
void MSP430_System::delay_us(register uint16_t us) const {
  register volatile uint32_t count;
  register uint32_t tmp;

  // fast approximation of:
  // count = (us*F_CPU)/(8*1000000)
  count = us; //8

  tmp = F_CPU >> 10; //76
  tmp = tmp * count; // 102
  tmp >>= 13; // 136
  count = tmp; // 138
  tmp >>= 5; // 156
  count += tmp; // 158
  tmp >>= 1; // 160
  count += tmp; // 162

#if(USE_ASM_SPINNING == 1)
  if(count <= 31) return; //169
  count = count - 31; //172; 172/8 = 21; adjusted to 31

  asmspin(count);
#else
  if(count <= 25) return; //169
  count = count - 25; //172; 172/8 = 21; adjusted to 25

  while(count){ // 8 cyc per loop
    count--;
  }
#endif
}

void MSP430_System::init()
{
}

