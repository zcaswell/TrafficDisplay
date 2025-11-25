# Wiring Notes

## Common Grounds

All grounds **must** be common:
- Arduino Nano GND
- 5 V power supply GND
- TFT GND
- LED strips GND

Connect all of these together.

## Power

- **5 V supply →**
  - TFT breakout `5V` or `VIN`
  - LED strip `+5V`
  - Arduino Nano 5 V (or power Nano via USB from the same supply)
- Do **not** power the LED strips directly from the Nano’s 5 V pin.

Place a **1000 µF capacitor** between 5 V and GND near the first LED strip.

## LED Strips (WS2812B)

- `Arduino D4` → 330 Ω resistor → all LED strip `DIN` pins
- LED strip `+5V` → 5 V PSU
- LED strip `GND` → common GND

You can either:
- Wire the three strips in **parallel** on the data line (all show the same pattern), or
- Daisy-chain them so `DO` of one goes to `DIN` of the next (they will still show the same color when all LEDs are driven identically).

## Button

- One leg of the button → `D2`
- Other leg → GND
- Use `pinMode(D2, INPUT_PULLUP)` (included in the sketch), no external pull-up needed.

## 3.2" ILI9341 TFT (SPI mode, Adafruit breakout)

Example wiring to Nano:

- TFT `VIN` / `5V` → 5 V
- TFT `GND` → GND
- TFT `CLK` / `SCK` → Arduino `D13`
- TFT `MISO` → Arduino `D12`
- TFT `MOSI` → Arduino `D11`
- TFT `CS`   → Arduino `D10`
- TFT `DC`   → Arduino `D9`
- TFT `RST`  → Arduino `D8`
- TFT `LED`  → 5 V (or 3.3 V) depending on the breakout; many have this tied internally

Touch and MicroSD pins can remain unconnected for this project.
