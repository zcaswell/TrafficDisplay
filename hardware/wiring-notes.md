# Troubleshooting

This document lists common issues and fixes for the **Traffic + Pedestrian Signal** project based on an Arduino Nano V3.0 and an ILI9341 TFT display.

---

## 1. Display shows a white screen or nothing at all

### Checklist

#### ✅ Wiring

* Nano D13 → TFT **SCK / CLK**
* Nano D11 → TFT **MOSI / DIN / SDI**
* Nano D12 → TFT **MISO / DOUT / SDO**
* Nano D10 → TFT **CS**
* Nano D9  → TFT **DC**
* Nano D8  → TFT **RST**
* TFT **GND** → Nano GND
* TFT **VIN / 5V** → 5 V supply

---

#### ✅ Power

* Measure **5 V** between TFT 5V and GND with a multimeter.
* Backlight should glow faintly when powered.

---

#### ✅ Library and Initialization

* Ensure you are using the **Adafruit ILI9341** library (not generic TFT libraries).
* In code, confirm:

```cpp
Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);
```

And in `setup()`:

```cpp
tft.begin();
tft.setRotation(0);
```

---

#### ✅ Module Type

* You must use a **breakout board with level shifting** (e.g. Adafruit #1743).
* Many cheap bare ILI9341 modules are **3.3 V logic only** and will not work safely with a 5 V Nano without level shifters.

---

#### ✅ Diagnostic Test

Upload the Adafruit example:

```
File → Examples → Adafruit_ILI9341 → graphicstest
```

Use the same pins defined in this project. If this test fails, fix wiring/power before proceeding.

---

## 2. LEDs do not light or show random colors

⚠️ This project now uses **three separate WS2812B LED strips**, each on its own data pin:

* **Red strip → Arduino D4**
* **Yellow strip → Arduino D5**
* **Green strip → Arduino D6**

Each strip represents one traffic lamp. Only one strip should ever be illuminated at a time.

### Checklist

### Checklist

#### ✅ Power

* LED strip **+5V** must connect to the external 5 V PSU (not only the Nano 5V pin).
* LED strip **GND** must connect to Nano GND (common ground).

---

#### ✅ Data Lines (3-strip configuration)

* Red strip: Nano **D4 → 330 Ω resistor → DIN**
* Yellow strip: Nano **D5 → 330 Ω resistor → DIN**
* Green strip: Nano **D6 → 330 Ω resistor → DIN**

Make sure:

* Each strip has its own resistor on the data line.
* You are connected to **DIN**, not **DOUT** (output end).
* Nano **D4 → 330 Ω resistor → DIN** of the first LED strip
* Ensure you are connected to **DIN**, not **DOUT** (output end).

---

#### ✅ FastLED Configuration

Verify the following in code:

```cpp
FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
```

Ensure `NUM_LEDS` matches or is less than the number of physical LEDs.

---

#### ✅ Ground Reference

If Nano is USB-powered and LEDs use a separate PSU:

* Grounds must be connected together.

---

#### ✅ Simple Test

Upload a basic FastLED test sketch to confirm LED health before using the full project.

---

## 3. Nano resets or USB disconnects when LEDs are bright

This is a classic **brown-out or current overload** symptom.

### Causes

* High LED current draw (WS2812B can pull ~50–60 mA per LED at full white).
* USB power alone is insufficient.

### Fixes

* Use a dedicated **5 V 3–5 A PSU** for LEDs and TFT.
* Share ground between all components.
* Reduce brightness in code:

```cpp
FastLED.setBrightness(40);
```

---

## 4. Button does not respond

### Checklist

#### ✅ Wiring

* One leg → Nano **D2**
* Other leg → **GND**

---

#### ✅ Code

Confirm:

```cpp
pinMode(BTN_PIN, INPUT_PULLUP);
OneButton btn(BTN_PIN, true, true);
btn.attachClick(handleClick);
```

And ensure:

```cpp
btn.tick();
```

Appears in the main loop.

---

#### ✅ Hardware

* Test continuity with a multimeter.
* Try another button or breadboard slot.

---

## 5. Animation is slow or flickers

This is usually performance-related.

### Improvements

* Avoid full `fillScreen()` redraws every frame.
* Only update changed areas (current code already does this).
* Keep animation frame rate ≤ 10 FPS on Nano.

---

## 6. Code will not compile

### Common causes

#### Missing Libraries

Install via Arduino Library Manager:

* FastLED
* OneButton
* Adafruit GFX Library
* Adafruit ILI9341

---

#### Wrong Board Selection

In Arduino IDE:

* Tools → Board → Arduino Nano
* Processor → ATmega328P (Old Bootloader) if needed

---

#### Flash Memory Full

If sketch size grows:

* Remove unused libraries
* Avoid large images or fonts

---

## Debug Strategy

When in doubt:

1. Test the TFT alone using Adafruit examples.
2. Test LEDs alone using FastLED examples.
3. Then test the full integrated system.

This step-by-step isolation process greatly simplifies debugging.

---

If a specific issue persists, capture:

* Compiler error message
* Photo of wiring
* Description of behavior

and include them when asking for help or filing a GitHub issue.
