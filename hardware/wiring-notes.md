# Wiring Notes – Arduino Nano Traffic + Pedestrian Signal

This document defines the complete pin mapping and electrical wiring for the project using:

* Arduino Nano V3.0
* ILI9341 3.2" TFT Display
* 3 × WS2812B LED strips (Red / Yellow / Green)
* Push Button

---

## Arduino Nano Pin Mapping

### LED Strips (Traffic Lamps)

Each WS2812B strip has its own data pin:

| Function         | Arduino Pin | Notes                     |
| ---------------- | ----------- | ------------------------- |
| Red lamp data    | D4          | Via 330 Ω resistor to DIN |
| Yellow lamp data | D5          | Via 330 Ω resistor to DIN |
| Green lamp data  | D6          | Via 330 Ω resistor to DIN |

All LED strips:

* +5V → External 5 V PSU
* GND → Common GND (shared with Nano and TFT)

Add a **1000 µF capacitor** between +5V and GND near the LED input point.

---

## TFT Display (ILI9341 SPI Mode)

| TFT Pin    | Arduino Nano Pin |
| ---------- | ---------------- |
| VCC / VIN  | 5V               |
| GND        | GND              |
| CS         | D10              |
| DC         | D9               |
| RST        | D8               |
| MOSI / SDI | D11              |
| MISO / SDO | D12              |
| SCK / CLK  | D13              |

> Display must support 5 V logic. Recommended: Adafruit #1743 breakout.

---

## Button Wiring

| Button Pin | Arduino Nano |
| ---------- | ------------ |
| One side   | D2           |
| Other side | GND          |

Button uses Arduino internal pull-up resistor.

---

## Power Distribution

```
5V PSU
 ├── LED Strips +5V
 ├── TFT VCC
 └── Arduino 5V (optional or via USB)

Ground
 ├── LED Strips GND
 ├── TFT GND
 └── Arduino GND
```

⚠ DO NOT power LED strips directly from Nano 5V pin.

---

## Common Ground Requirement

All devices must share the same ground reference:

* Arduino GND
* LED strip GND
* TFT GND
* PSU GND

Failure to share ground will result in erratic LED behavior or no response.

---

## Free Pins Remaining

After wiring, the following Nano pins remain available:

* D3
* D7
* A0–A7

These may be used for sensors, sounders, or future expansion.

---

## Connection Checklist

✔ Each LED strip has its own 330 Ω resistor
✔ Strips wired to DIN (not DOUT)
✔ 1000 µF capacitor installed
✔ Common ground verified
✔ TFT supports 5 V logic
✔ Button uses INPUT_PULLUP configuration

---

For visual clarity, include a wiring diagram image in the repository if sharing publicly.
