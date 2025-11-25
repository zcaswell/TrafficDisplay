# Bill of Materials (BOM)

## Core

- 1× **Arduino Nano V3.0** (ATmega328P, 5 V / 16 MHz)
- 1× **5 V power supply**, ≥ 3 A
  - Example: 5 V 4–5 A wall adapter or bench supply
- 1× USB cable for programming the Nano

## Display

- 1× **3.2" TFT LCD with Touchscreen Breakout Board w/MicroSD Socket – ILI9341**
  - Adafruit product #1743 or compatible ILI9341 SPI breakout
  - Must be 5 V logic–compatible (built-in level shifting + 3.3 V regulator)

## LED Traffic Signals

- 3× **WS2812B addressable RGB LED strips**
  - Example: 15 LEDs per strip (adjust `NUM_LEDS` in code if needed)
  - All three strips share the same data line
- 1× **330 Ω resistor** in series with the LED data line
- 1× **1000 µF electrolytic capacitor** (≥ 6.3 V) across 5 V and GND near the first LED strip

## Controls

- 1× **Momentary push button**, normally open (NO)
  - Wired from Arduino D2 to GND

## Misc

- Breadboard or protoboard
- Dupont jumper wires / hookup wire
- Optional:
  - Screw terminals for LED power connections
  - Standoffs or enclosure for the TFT and Nano
