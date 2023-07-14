#include "WBIOExtMini.h"

ADS1115 ADS(IOEXTMINI_ADS1115_ADDR);

WBIOExtMini::WBIOExtMini(Stream *debugStream)
    : debugStream(debugStream == nullptr ? &getDummyDebugStream() : debugStream)
{
}

void WBIOExtMini::powerOn()
{
  pinMode(IOEXTMINI_POWER_PIN, OUTPUT);
  digitalWrite(IOEXTMINI_POWER_PIN, HIGH);
  delay(1000);
}

void WBIOExtMini::powerOff()
{
  pinMode(IOEXTMINI_POWER_PIN, OUTPUT);
  digitalWrite(IOEXTMINI_POWER_PIN, LOW);
}

uint8_t WBIOExtMini::readAnalog(ioextmini_analogpin_enum pin)
{
  if (!adsInit())
  {
    return 0;
  }

  return (uint8_t)(ADS.readADC(pin) * ADS.toVoltage(pin)) * 1000;
}

void WBIOExtMini::attachToInterrupt(void (*callback)(void), ioextmini_interrupt_mode_enum mode)
{
  pinMode(IOEXTMINI_INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IOEXTMINI_INTERRUPT_PIN), callback, mode);
}

void WBIOExtMini::attachToInterrupt(void (*callback)(void), ioextmini_interrupt_mode_enum mode, int pinModeValue)
{
  pinMode(IOEXTMINI_INTERRUPT_PIN, pinModeValue);
  attachInterrupt(digitalPinToInterrupt(IOEXTMINI_INTERRUPT_PIN), callback, mode);
}

bool WBIOExtMini::adsInit()
{
  if (!ADS.begin())
  {
    debugStream->printf("ADS1115 not found or not working correctly on address %x", IOEXTMINI_ADS1115_ADDR);
    return false;
  }
  ADS.setGain(1);
  return true;
}

Stream &WBIOExtMini::getDummyDebugStream()
{
  static Stream *dummyDebugStream = nullptr;
  if (dummyDebugStream == nullptr)
  {
    class DummyStream : public Stream
    {
    public:
      int available() { return 0; }
      int read() { return -1; }
      int peek() { return -1; }
      void flush() {}
      void printf(const char *, ...) {}
      size_t write(uint8_t) { return 1; }
    };
    static DummyStream instance;
    dummyDebugStream = &instance;
  }
  return *dummyDebugStream;
}
