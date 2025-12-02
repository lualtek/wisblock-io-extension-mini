#ifndef WBIOEXTMINI_H
#define WBIOEXTMINI_H

#include <Arduino.h>
#include <Wire.h>
#include "ADS1X15.h"

#define IOEXTMINI_ADS_ADDR 0x48
#define IOEXTMINI_POWER_PIN WB_IO2

enum ioextmini_analogpin_enum
{
  AIN0 = 0,
  AIN1,
  AIN2,
  AIN3
};

enum ioextmini_interruptpin_enum
{
  INT_PIN_4 = WB_IO4,
  INT_PIN_5 = WB_IO5
};

enum ioextmini_interrupt_mode_enum
{
  EXT_RISING = RISING,
  EXT_FALLING = FALLING,
  EXT_CHANGE = CHANGE
};

class WBIOExtMini
{
public:
  WBIOExtMini(Stream *debugStream = nullptr);

  bool begin();
  void powerOn();
  void powerOff();

  // Reads voltage in mV
  uint16_t readAnalog(ioextmini_analogpin_enum pin);

  /* Attach interrupt. Default INT_PIN_4 = WB_IO4 */
  void attachToInterrupt(void (*callback)(void), ioextmini_interrupt_mode_enum mode, ioextmini_interruptpin_enum pin = INT_PIN_4);
  /* Attach interrupt to IOEXTMINI_INTERRUPT_PIN_4 = WB_IO4 */
  void attachToInterrupt(void (*callback)(void), ioextmini_interrupt_mode_enum mode, int pinModeValue, ioextmini_interruptpin_enum pin = INT_PIN_4);

private:
  Stream *_debug;
  ADS1115 _ads; // The ADS instance is now part of this class
  bool _adsReady;
};

#endif
