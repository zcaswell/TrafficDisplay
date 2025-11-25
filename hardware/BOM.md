# Bill of Materials (BOM)

This BOM reflects the updated design using **three separate WS2812B LED strips**, each on its own data pin, to accurately model a real traffic signal (Red / Yellow / Green).

---

## Core Electronics

* 1× **Arduino Nano V3.0** (ATmega328P, 5 V, 16 MHz)
* 1× **5 V DC Power Supply**, minimum 3 A (recommended 4–5 A for headroom)
* 1× USB cable (for programming and optional power)

---

## Display System

* 1× **3.2" TFT LCD with Touchscreen Breakout Board – ILI9341**

  * Recommended: Adafruit #1743 or equivalent
  * Requirements:

    * SPI interface
    * 5 V logic compatible (onboard regulator + level shifting)

---

## Traffic Signal LEDs

* 3× **WS2812B Addressable RGB LED Strips**

  * One strip per traffic lamp color:

    * Red
    * Yellow
    * Green
  * Typical length: 10–20 LEDs per strip (adjustable in code)

* 3× **330 Ω resistor** (one per data line)

  * Placed in series between Arduino and LED strip DIN

* 1× **1000 µF electrolytic capacitor**, ≥ 6.3 V

  * Connected across 5 V and GND close to the LED strips

---

## User Input

* 1× **Momentary Push Button**, Normally Open (NO)

  * Used to start/stop the traffic cycle

---

## Wiring & Assembly

* Dupont jumper wires / hookup wire
* Breadboard or prototyping PCB
* Optional:

  * Screw terminals for power distribution
  * Enclosure or mounting hardware
  * Heat shrink tubing

---

## Notes

* Total LED current can exceed 2 A at full brightness. Do NOT power LED strips from the Nano 5 V pin.
* All components **must share a common ground**.
* Ensure display module explicitly supports 5 V logic levels before direct connection to Nano.
