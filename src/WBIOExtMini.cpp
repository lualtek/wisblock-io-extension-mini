#include "WBIOExtMini.h"

// Constructor initializes the _ads member with the HARDCODED address
WBIOExtMini::WBIOExtMini(Stream *debugStream)
    : _debug(debugStream),
      _ads(IOEXTMINI_ADS_ADDR),
      _adsReady(false)
{
}

void WBIOExtMini::powerOn()
{
  pinMode(IOEXTMINI_POWER_PIN, OUTPUT);
  digitalWrite(IOEXTMINI_POWER_PIN, HIGH);
  // RAK3172 is fast, give external sensor/ADS time to wake up and stabilize capacitors
  delay(200);
}

void WBIOExtMini::powerOff()
{
  digitalWrite(IOEXTMINI_POWER_PIN, LOW);
  // Crucial: Reset ready flag so begin() runs again on next power up
  // The ADS loses its config (Gain/Mode) when power is cut.
  _adsReady = false;
}

bool WBIOExtMini::begin()
{
  // Initialize I2C.
  // It is safe to call Wire.begin() multiple times in RUI3,
  // but usually better to let the main sketch handle it if you have other I2C devices.
  Wire.begin();

  // Initialize ADS
  if (!_ads.begin())
  {
    if (_debug)
      _debug->printf("[IOExt] ADS1115 not found at 0x%x\r\n", IOEXTMINI_ADS_ADDR);
    return false;
  }

  // Set Gain: 1 = +/- 4.096V
  _ads.setGain(1);
  _adsReady = true;
  return true;
}

uint16_t WBIOExtMini::readAnalog(ioextmini_analogpin_enum pin)
{
  // Auto-recovery: If we aren't ready (e.g., just powered on), try to init
  if (!_adsReady)
  {
    if (!begin())
      return 0;
  }

  int16_t raw = _ads.readADC(pin);

  // OPTIMIZATION: Integer Math replacement for floats.
  // ADS1115 @ Gain 1 (+/- 4.096V) -> 1 bit = 0.125mV
  // Voltage = Raw * 0.125  ===  Voltage = Raw / 8
  // Bit shifting (>> 3) is significantly faster/smaller than float multiplication.

  if (raw < 0)
    raw = 0; // Clamp negative differential noise

  return (uint16_t)(raw >> 3);
}

void WBIOExtMini::attachToInterrupt(void (*callback)(void), ioextmini_interrupt_mode_enum mode, ioextmini_interruptpin_enum pin)
{
  // Default to INPUT_PULLUP if not specified
  attachToInterrupt(callback, mode, INPUT_PULLUP, pin);
}

void WBIOExtMini::attachToInterrupt(void (*callback)(void), ioextmini_interrupt_mode_enum mode, int pinModeValue, ioextmini_interruptpin_enum pin)
{
  pinMode(pin, pinModeValue);
  attachInterrupt(digitalPinToInterrupt(pin), callback, mode);
}
