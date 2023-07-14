
#ifdef _VARIANT_RAK4630_
#include <Adafruit_TinyUSB.h>
#endif
#include "WBIOExtMini.h"

Serial debugSerial;

WBIOExtMini ioextmini(&debugSerial);

void setup()
{
  Serial.begin(115200);
  delay(2000);
  Serial.println("WBIOExtMini example: AnalogRead");
}

void loop()
{
  ioextmini.powerOn();
  uint8_t analog0 = ioextmini.readAnalog(IOEXTMINI_ANALOGPIN_0);
  uint8_t analog1 = ioextmini.readAnalog(IOEXTMINI_ANALOGPIN_1);
  ioextmini.powerOff();

  // Pretty print values as voltage in mV
  Serial.print("\tAnalog0: ");
  Serial.print(analog0);
  Serial.println(" mV");

  Serial.print("\tAnalog1: ");
  Serial.print(analog1);
  Serial.println(" mV");

  delay(2000);
}
