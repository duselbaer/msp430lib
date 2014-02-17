#pragma once

#include <stdint.h>

namespace msp430lib {
inline namespace v1 {

  /*!
   * \brief Interface providing some functions
   *
   * Provides some common functions like sleeping for other components. This
   * has become an interface because there is likely more than one component
   * which will need to access the implementation.
   */
  class ISys
  {
  public:
    //! \brief Initialization
    virtual void init() = 0;

    //! \brief Sleep the given amount of microseconds
    virtual void delay_us(register uint16_t us) const = 0;

    //! \brief Number of Milliseconds since start
    virtual uint32_t millisecondsSinceStart() const = 0;
  };
}
}

