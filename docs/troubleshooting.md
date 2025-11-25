# Troubleshooting

This document lists common issues and fixes for the traffic + pedestrian signal project.

---

## 1. Display shows a white screen or nothing at all

### Checklist

1. **Wiring**
   - Confirm SPI pins:
     - Nano D13 → TFT SCK
     - Nano D11 → TFT MOSI (often labeled DIN or SDI)
     - Nano D12 → TFT MISO (often labeled DOUT or SDO)
     - Nano D10 → TFT CS
     - Nano D9  → TFT DC
     - Nano D8  → TFT RST
   - TFT GND → Nano GND
   - TFT VIN / 5V → 5 V supply

2. **Power**
   - Measure 5 V between TFT 5V and GND.
   - Backlight should glow faintly when powered.

3. **Library & ctor**
   - Make sure you’re using the **Adafruit ILI9341** library.
   - Constructor in code:
     ```cpp
     Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);
     ```
   - Call `tft.begin()` in `setup()` and optionally `tft.setRotation(0);`.

4. **Module type**
   - Ensure you’re using the **Adafruit 3.2" ILI9341 breakout (PID 1743)** or another 5 V **breakout** with level shifting.
   - Many **bare 2.4"/2.8" ILI9341 modules** are strictly 3.3 V logic and require level shifters.   

5. **Test with Adafruit example**
   - Load `File → Examples → Adafruit_ILI9341 → graphicstest`.
   - Use the same pins defined in this project.
   - If the example doesn’t work, debug the display wiring first.

---

## 2. LEDs don’t light, or show random colors

### Checklist

1. **Power**
   - LED strip `+5V` must go to the external 5 V PSU, **not** only the Nano’s 5 V pin.
   - LED strip GND → common ground with Nano and PSU.
   - Check for correct polarity; some strips mark +5V, GND, DIN.

2. **Data line**
   - Arduino D4 → 330 Ω resistor → LED strip DIN.
   - Make sure you didn’t accidentally go into DOUT at the far end.

3. **FastLED configuration**
   - Confirm:
     ```cpp
     FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
     ```
   - `NUM_LEDS` should match the number of LEDs you actually use (or be ≤ that).

4. **Ground reference**
   - If the Nano is USB powered and the LED strip is powered by another 5 V PSU, GND **must** be common between them.   

5. **Test pattern**
   - Temporarily upload a simple FastLED test sketch (e.g. `ColorPalette` example) to validate LEDs before using this full project.

---

## 3. Nano resets, flickers, or USB disconnects when LEDs are bright

Likely a **power or brown-out** issue.

- The LED strips can draw large current at high brightness.  
- If you power everything from USB only, the 5 V rail may sag.

**Fixes:**

- Use a dedicated **5 V 3–5 A** supply for LEDs + TFT.
- Connect Nano 5 V to that same supply or power Nano via USB *plus* common ground.
- Lower brightness in code:
- FastLED.setBrightness(40);  // lower than default 80
  ```cpp
  FastLED.setBrightness(40);  // lower than default 80
