#ifndef _WBIOExtMini_H_
#define _WBIOExtMini_H_

#include <Arduino.h>
#include <ADS1X15.h>

#define IOEXTMINI_POWER_PIN WB_IO2
#define IOEXTMINI_ADS1115_ADDR 0x48
#define IOEXTMINI_INTERRUPT_PIN WB_IO4

enum ioextmini_interrupt_mode_enum : uint8_t
{
  IOEXTMINI_INTERRUPT_RISING = RISING,
  IOEXTMINI_INTERRUPT_FALLING = FALLING,
  IOEXTMINI_INTERRUPT_CHANGE = CHANGE
};

enum ioextmini_analogpin_enum : uint8_t
{
  IOEXTMINI_A0 = 0,
  IOEXTMINI_A1 = 1,
  IOEXTMINI_A2 = 2,
  IOEXTMINI_A3 = 3
};

class WBIOExtMini
{
public:
  WBIOExtMini(Stream *debugStream = nullptr);
  void powerOn();
  void powerOff();
  /**
   * @brief Initialize ADS1115 for analog read
   * This function should be called before readAnalog() is called.
   * NOTE: the readAnalog() function will call this function if it has not been called yet.
   *
   * @return true if ADS1115 is ready to be used
   */
  bool begin();
  /**
   * @brief Read analog value from IOExtMini
   * The analog value is read from the ADS1115 ADC and gain is set to 1 and cannot be changed.
   *
   * @param pin ioextmini_analogpin_enum
   * @return uint8_t voltage in mV
   */
  uint16_t readAnalog(ioextmini_analogpin_enum pin);
  /**
   * @brief Attach interrupt to IOExtMini
   * The interrupt pin is IOEXTMINI_INTERRUPT_PIN which is WB_IO4 on the WisBlock Core.
   *
   * @param callback void (*callback)(void) function to call when interrupt is triggered
   * @param mode ioextmini_interrupt_mode_enum interrupt mode
   */
  void attachToInterrupt(void (*callback)(void), ioextmini_interrupt_mode_enum mode);
  /**
   * @brief Attach interrupt to IOExtMini
   * The interrupt pin is IOEXTMINI_INTERRUPT_PIN which is WB_IO4 on the WisBlock Core.
   *
   * @param callback void (*callback)(void) function to call when interrupt is triggered
   * @param mode ioextmini_interrupt_mode_enum interrupt mode
   * @param pinModeValue int pin mode between INPUT, INPUT_PULLUP, INPUT_PULLDOWN
   */
  void attachToInterrupt(void (*callback)(void), ioextmini_interrupt_mode_enum mode, int pinModeValue);

private:
  bool adsReady = false;
  Stream *debugStream;

  // Returns a reference to a dummy debug stream (that doesn't print anything)
  static Stream &getDummyDebugStream();
};

#endif
