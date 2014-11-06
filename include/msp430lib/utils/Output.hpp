#pragma once

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
};

template<typename D>
Output<D>& operator<<(Output<D>& os, const char* str)
{
  os.puts(str);
  return os;
}
}
}

