# Traffic + Pedestrian Signal Demo (Arduino Nano, WS2812B, ILI9341 TFT)

This project implements a **traffic and pedestrian signal** on an Arduino Nano, with:

- 3× WS2812B RGB LED strips for red / yellow / green traffic signals
- A **3.2" ILI9341 TFT** display showing a *walking man animation* and countdown
- A single **momentary push button** to start/stop the sequence

It’s designed as a teaching / demo tool for state machines, timing, and simple graphics on small microcontrollers.

---

## Features

- One-button control:
  - Press from idle → run full traffic + pedestrian cycle
  - Press while running → abort and return to idle
- Traffic sequence:
  1. 6 s **flashing red**
  2. 6 s **solid red**
  3. Three cycles of:
     - 10 s **red clearance**
     - 25 s **green**
     - 3 s **yellow clearance**
- Pedestrian sequence:
  - 7 s **"WALK"** phase with walking man animation
  - Random **countdown 10–30 s** with walking man + big numeric countdown
- Non-blocking timing using `millis()`, so the button remains responsive
- Uses common, well-supported Arduino libraries

---

## Hardware

See **[`hardware/BOM.md`](hardware/BOM.md)** for the full bill of materials and **[`hardware/wiring-notes.md`](hardware/wiring-notes.md)** for wiring details.

High-level parts list:

- Arduino Nano V3.0 (ATmega328P, 5 V / 16 MHz)
- 3× WS2812B addressable LED strips
- 3.2" ILI9341 TFT LCD Breakout (SPI, 5 V logic–compatible)
- Momentary push button (NO)
- 5 V / 3–5 A power supply
- Various passives (330 Ω resistor, 1000 µF capacitor) and jumper wires

---

## Software Setup

### Libraries

Install these libraries via **Sketch → Include Library → Manage Libraries…** in the Arduino IDE:

- **FastLED**
- **OneButton**
- **Adafruit GFX Library**
- **Adafruit ILI9341**

Then open `src/traffic_ped_signal.ino`.

### Board & Port

1. In the Arduino IDE, select:
   - Board: `Arduino Nano`
   - Processor: `ATmega328P (Old Bootloader)` or the correct setting for your Nano
2. Select the correct serial port.

### Upload

1. Connect the Nano via USB.
2. Click **Upload**.
3. Open the Serial Monitor if you add debug prints (none by default).

---

## Operation

1. Power the system with the 5 V PSU (and/or via USB for programming).
2. The system starts in **IDLE**:
   - LED strips off
   - TFT shows "Press button to start"
3. Press the button:
   - The sequence starts (FLASH_RED → SOLID_RED → cycles → pedestrian WALK + countdown).
4. Press the button **again at any time**:
   - The sequence stops immediately and returns to IDLE.
5. Press the button again from IDLE to restart the full sequence.

---

## Walking Man Animation

The walking man is a simple stick figure with two frames:

- Frame A: left leg forward, right leg back
- Frame B: right leg forward, left leg back

You can see an example sprite in **[`docs/walking-man-sprite.png`](docs/walking-man-sprite.png)** and tweak the on-screen drawing in `drawWalkingMan()` inside the sketch.

---

## Customization Ideas

- Map each LED strip to a specific signal:
  - Top strip: red
  - Middle strip: yellow
  - Bottom strip: green
- Use the TFT’s touchscreen to start/stop instead of the button.
- Add more animation frames for smoother walking.
- Use the MicroSD socket on the TFT breakout to store bitmaps for more detailed graphics.

---

## License

This project is released under the **MIT License**. See [`LICENSE`](LICENSE) for details.
