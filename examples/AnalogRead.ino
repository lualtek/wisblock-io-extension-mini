
#ifdef _VARIANT_RAK4630_
#include <Adafruit_TinyUSB.h>
#endif
#include "WBIOExtMini.h"

#define debugSerial Serial

WBIOExtMini ioextmini(&debugSerial);

void setup()
{
  debugSerial.begin(115200);
  delay(2000);
  debugSerial.println("WBIOExtMini example: AnalogRead");
}

void loop()
{
  ioextmini.powerOn();
  ioextmini.begin();
  uint16_t analog0 = ioextmini.readAnalog(IOEXTMINI_A0);
  uint16_t analog1 = ioextmini.readAnalog(IOEXTMINI_A1);
  ioextmini.powerOff();

  // Pretty print values as voltage in mV
  debugSerial.print("\tAnalog0: ");
  debugSerial.print(analog0);
  debugSerial.println(" mV");

  debugSerial.print("\tAnalog1: ");
  debugSerial.print(analog1);
  debugSerial.println(" mV");

  delay(2000);
}
