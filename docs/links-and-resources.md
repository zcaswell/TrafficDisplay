# Links & Resources

## Core Components (Purchase Links)

> Always verify voltage and logic level compatibility if you use substitutes.

### Arduino Nano V3.0 (ATmega328P, 5 V)

- Example (official):  
  - Arduino Nano page  
- Many compatible clones are also available on major marketplaces.

### 3.2" ILI9341 TFT LCD Breakout (Adafruit #1743)

- Adafruit product page:  
  - "3.2\" TFT LCD with Touchscreen Breakout Board w/MicroSD Socket - ILI9341"  
- Distributor examples:  
  - Mouser, Core Electronics, etc.

Key properties:
- 3.2" diagonal, 240 x 320 pixels (RGB)  
- On-board 3.3 V regulator and level shifting → 3–5 V logic compatible  
- SPI or 8-bit parallel modes  

Reference: Adafruit breakout guide (v2)   

### WS2812B Addressable LED Strip

- Typical 5 V WS2812B strip (30/60 LEDs per meter):  
  - Adafruit, Pololu, generic vendors, etc.

Power guidance:
- Each LED can draw up to ~50–60 mA at full white.
- Example: 30 LEDs ≈ 1.5 A at 5 V.   

Good tutorials:
- Random Nerd Tutorials – WS2812B Arduino guide   
- LastMinuteEngineers – WS2812B with Arduino   

### Button and Miscellaneous

- Any standard NO momentary pushbutton, rated for low voltage/current.
- 330 Ω resistor (SMD or THT)
- 1000 µF electrolytic capacitor (≥ 6.3 V), for LED strip decoupling.

---

## Arduino Libraries

Install these from **Arduino Library Manager**:

- **FastLED** – control WS2812B LED strips   
- **OneButton** – simple button handling with debouncing
- **Adafruit GFX Library** – core graphics primitives
- **Adafruit ILI9341** – driver for ILI9341 TFT breakout

ILI9341 examples (for reference):
- Electronoobs – ILI9341 TFT display example with Arduino   
- Various Uno/Nano tutorials online use the same wiring style.
