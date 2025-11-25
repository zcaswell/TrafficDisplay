# 🚦 Arduino Traffic & Pedestrian Signal System

A fully-functional traffic and pedestrian crossing signal system built using an **Arduino Nano V3.0**, an **ILI9341 3.2" TFT display**, and **three independent WS2812B LED strips** representing real-world Red, Yellow, and Green traffic lamps.

This project simulates a realistic road signal with pedestrian interaction, animated walking man, and randomized countdown timing.

---

## ✨ Features

* ✅ Realistic traffic light sequence
* ✅ Pedestrian request via pushbutton
* ✅ Animated walking man on TFT screen
* ✅ Randomized pedestrian countdown (10–30s)
* ✅ Three independent LED strips (true signal behavior)
* ✅ Start / Stop control with single button
* ✅ Designed for Arduino Nano (ATmega328P, 5V)

---

## 🕹️ How It Works

1. Press button to start cycle
2. System flashes red, then solid red
3. Runs 3 full vehicle cycles:

   * Red → Green → Yellow
4. Pedestrian phase activates:

   * Walking man animation
   * Random countdown
5. System stops and returns to IDLE
6. Button press can halt sequence at any time

---

## 🔄 Sequence Overview

```
IDLE → FLASH_RED → SOLID_RED →
(RED_CLEAR → GREEN → YELLOW) × 3 →
WALK_SOLID → WALK_COUNTDOWN → IDLE
```

---

## 🧩 Hardware Used

* Arduino Nano V3.0 (ATmega328P)
* 3.2" TFT LCD ILI9341 Display (SPI, 240x320)
* 3 × WS2812B RGB LED Strips (Red / Yellow / Green)
* Momentary Push Button
* 5V 3–5A Power Supply
* 3 × 330Ω resistors
* 1 × 1000µF capacitor

Full details in: `hardware/BOM.md`

---

## 🔌 Pin Mapping (Summary)

| Component             | Nano Pin |
| --------------------- | -------- |
| Red LED Strip Data    | D4       |
| Yellow LED Strip Data | D5       |
| Green LED Strip Data  | D6       |
| Button                | D2       |
| TFT CS                | D10      |
| TFT DC                | D9       |
| TFT RST               | D8       |
| TFT MOSI              | D11      |
| TFT MISO              | D12      |
| TFT SCK               | D13      |

Full wiring details: `docs/wiring-notes.md`

---

## 📟 Display

The TFT shows:

* Traffic state text
* Animated walking man
* Large pedestrian countdown timer

Uses Adafruit libraries:

* Adafruit_GFX
* Adafruit_ILI9341

---

## 📁 Repository Structure

```
/traffic-signal-project
│
├── traffic_ped_signal.ino
├── README.md
├── hardware/
│   └── BOM.md
├── docs/
│   ├── wiring-notes.md
│   ├── timing-diagram.md
│   ├── troubleshooting.md
│   └── references.md
└── images/
    └── wiring-diagram.png
```

---

## 🚀 Getting Started

1. Install required libraries via Arduino IDE Library Manager:

   * FastLED
   * OneButton
   * Adafruit GFX Library
   * Adafruit ILI9341

2. Wire components according to `docs/wiring-notes.md`

3. Upload `traffic_ped_signal.ino` to Arduino Nano

4. Power system with 5V PSU

5. Press button to begin

---

## ⚠️ Power Warning

Do NOT power LED strips directly from Nano 5V pin.
Use a dedicated 5V 3–5A supply and connect all grounds together.

---

## 📸 Visuals

See `/images/wiring-diagram.png` for complete connection overview.

---

## 📜 License

MIT License – feel free to use, modify, and distribute.

---

## 👤 Contributing

Pull requests and improvements are welcome!
Consider adding:

* More signal modes
* Audible pedestrian signal
* Multiple intersections

---

## ✅ Status

✔ Fully functional and tested logic design
✔ Consistent documentation
✔ Nano-compatible
✔ Ready for expansion

Enjoy building your smart traffic system 🚦
