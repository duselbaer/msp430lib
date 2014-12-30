#pragma once

#include <stdio.h>

namespace msp430lib {
inline namespace v1 {

template<typename DEVICE>
class Output
{
  DEVICE& m_device;

  public:
    Output(DEVICE& device)
    : m_device(device)
    {
    }

    void puts(const char* str)
    {
      while (*str)
      {
        m_device.putc((uint8_t)*str++);
      }
    }

    void putc(char c)
    {
      m_device.putc((uint8_t) c);
    }
};

template<typename D>
Output<D>& operator<<(Output<D>& os, const char* str)
{
  os.puts(str);
  return os;
}

template<typename D>
void writeNibble(Output<D>& os, uint8_t nibble)
{
  nibble = nibble & 0x0F;
  if (nibble >= 0x0A)
  {
    nibble = nibble - 10;
    nibble = nibble + 'a';
  }
  else
  {
    nibble = nibble + '0';
  }
  os.putc((char) nibble);
}

template<typename D>
Output<D>& operator<<(Output<D>& os, uint8_t const byte)
{
  os.puts("0x");
  writeNibble(os, byte >> 4);
  writeNibble(os, byte);
  return os;
}

template<typename D>
Output<D>& operator<<(Output<D>& os, uint32_t const x)
{
  char buf[16];
  sprintf(buf, "%lu", x);

  os << buf;
  return os;
}
}
}

