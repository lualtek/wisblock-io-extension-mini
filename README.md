# WBIOExtMini (Mini RAK5804) Arduino Library

The WBIOExtMini library is designed for the Lualtek custom WB IO Extension Mini board. This library allows you to interface with the IO Extension Mini board, which is a mini version of the RAK5804 IO Extension Module. The WB IO Extension Mini board is specifically designed for the 10x23 sensor slot of the WisBlock base board.

## Hardware

The WB IO Extension Mini board is a mini version of the RAK5804 IO module built for a 10x23mm sensor slot. It provides the following features:

- Choice between VDD and +3V3_S to power up peripherals.
- Exposed pins:
  - 2 GPIOs (1-2 or 3-4)
  - I2C
  - TX/RX
  - 2 ANALOG inputs

The board is equipped with redundant GND and +3V3 connections on each SMD connector. All IOs are protected with ESD bidirectional diodes. The analog inputs are provided by the ADS1115 chip mounted on the bottom of the board. The pins can be wired through SH 1.0mm pitch horizontal connectors.

![IO_MOSAIC](https://github.com/piecol/Wisblock_IO_extention_10x23/assets/29545872/d94824b2-ea09-4e53-92ed-dce951a62d62)

The main purpose of the WB IO Extension Mini board is to enable analog measurements on the RAK19003 mini WisBlock base, which does not have an IO slot. Having a dedicated ADC also allows measuring either 2 single-ended channels or one in differential mode.

![test_RAK v1](https://github.com/piecol/Wisblock_IO_extention_10x23/assets/29545872/fa6455f0-08eb-4e42-8286-08541ba00e5f)

For more detailed information about the hardware setup and connections, please refer to the [`hardware` folder](hardware) of the repository.

## Features

- Power on/off the WB IO Extension Mini board.
- Read analog values using the ADS1x15 chip.
- Expose the WB_IO4 pin from the RAK board as an interrupt.

## Installation

You can install the WBIOExtMini library through the Arduino Library Manager or manually as a ZIP file.

### Arduino Library Manager (Recommended)

1. Open the Arduino IDE.
2. Go to **Sketch** -> **Include Library** -> **Manage Libraries**.
3. In the Library Manager, search for "WBIOExtMini".
4. Click on the WBIOExtMini library and click the **Install** button.

### Manual Installation

1. Download the WBIOExtMini library as a ZIP file from the [GitHub repository](https://github.com/username/repo).
2. In the Arduino IDE, navigate to **Sketch** -> **Include Library** -> **Add .ZIP Library**.
3. Select the downloaded ZIP file of the library and click **Open**.

## Dependencies

The WBIOExtMini library depends on the [ADS1x15 library](https://github.com/RobTillaart/ADS1X15/). Make sure to install the ADS1x15 library before using the WBIOExtMini library.

## Usage

### Wiring

Connect the WB IO Extension Mini board to your WisBlock base board using the appropriate connector.

### Library Initialization

To begin using the WBIOExtMini library, include the library header at the beginning of your sketch:

```cpp
#include <WBIOExtMini.h>
```

Next, create an instance of the `WBIOExtMini` class:

```cpp
WBIOExtMini wbioextmini(&Serial);
```

Replace `Serial` with the appropriate serial object for debugging.

### Power On/Off

To power on or off the WB IO Extension Mini board, use the `powerOn()` and `powerOff()` methods:

```cpp
wbioextmini.powerOn();
// Perform operations with the powered-on board
wbioextmini.powerOff();
```

### Reading Analog Values

To read analog values from the IO Extension Mini board using the ADS1x15 chip, use the `readAnalog()` method:

```cpp
uint8_t analog0 = wbioextmini.readAnalog(IOEXTMINI_A0);
uint8_t analog1 = wbioextmini.readAnalog(IOEXTMINI_A1);
```

Replace `IOEXTMINI_A0` and `IOEXTMINI_A1` with the appropriate analog pin constants.

### Interrupt Pin

The WB IO Extension Mini board exposes the WB_IO4 pin from the RAK board as an interrupt. You can attach an interrupt to this pin using the `attachToInterrupt()` method:

```cpp
void interruptCallback() {
  // Handle the interrupt event
}

wbioextmini.attachToInterrupt(interruptCallback, IOEXTMINI_INTERRUPT_RISING);
```

Replace `interruptCallback` with the function that should be called when the interrupt is triggered. You can specify the interrupt mode using `IOEXTMINI_INTERRUPT_RISING`, `IOEXTMINI_INTERRUPT_FALLING`, or `IOEXTMINI_INTERRUPT_CHANGE`. By default, the interrupt pin is configured as INPUT.

## Example Sketch

Here's an example sketch that demonstrates analog reading and interrupt usage using the WBIOExtMini library:

```cpp
#ifdef _VARIANT_RAK4630_
#include <Adafruit_TinyUSB.h>
#endif
#include "WBIOExtMini.h"

Serial debugSerial;

WBIOExtMini wbioextmini(&debugSerial);

void setup()
{
  Serial.begin(115200);
  delay(2000);
  Serial.println("WBIOExtMini example: AnalogRead and Interrupt");

  // Attach interrupt
  wbioextmini.attachToInterrupt(interruptCallback, IOEXTMINI_INTERRUPT_RISING);
}

void loop()
{
  wbioextmini.powerOn();
  uint8_t analog0 = wbioextmini.readAnalog(IOEXTMINI_A0);
  uint8_t analog1 = wbioextmini.readAnalog(IOEXTMINI_A1);
  wbioextmini.powerOff();

  // Pretty print values as voltage in mV
  Serial.print("\tAnalog0: ");
  Serial.print(analog0);
  Serial.println(" mV");

  Serial.print("\tAnalog1: ");
  Serial.print(analog1);
  Serial.println(" mV");

  delay(2000);
}

void interruptCallback() {
  // Handle the interrupt event
}
```

Make sure to wire the WB IO Extension Mini board correctly and modify the sketch according to your requirements.

## License

This project is licensed under the [MIT License](LICENSE).
