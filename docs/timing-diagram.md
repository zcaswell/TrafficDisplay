# Traffic + Pedestrian Signal Timing Diagram

This document describes the logical timing sequence implemented by the Arduino Nano controller.

---

## Overall Sequence

The system starts and stops via a single momentary push button.

### Button Behaviour

* Press when IDLE → Start full sequence
* Press while running → Immediately stop and return to IDLE
* Press again → Restart sequence from beginning

---

## Phase Timing Overview

### 1. FLASH_RED – 6 seconds

* Red LED strip: flashing (0.5 s ON / 0.5 s OFF)
* Yellow strip: OFF
* Green strip: OFF
* TFT: "RED FLASH"

---

### 2. SOLID_RED – 6 seconds

* Red strip: ON
* Yellow strip: OFF
* Green strip: OFF
* TFT: "RED"

---

## Vehicle Cycle (3 repetitions)

The following sequence runs three times before pedestrian phase begins:

### 3. RED_CLEAR – 10 seconds

* Red strip: ON
* Yellow strip: OFF
* Green strip: OFF
* TFT: "RED CLEAR"

### 4. GREEN_STATE – 25 seconds

* Red strip: OFF
* Yellow strip: OFF
* Green strip: ON
* TFT: "GREEN"

### 5. YELLOW_STATE – 3 seconds

* Red strip: OFF
* Yellow strip: ON
* Green strip: OFF
* TFT: "YELLOW"

---

## Pedestrian Phase

### 6. WALK_SOLID – 7 seconds

* Red strip: ON (vehicles stopped)
* Yellow strip: OFF
* Green strip: OFF
* TFT: Walking man animation + "WALK"

### 7. WALK_COUNTDOWN – Random 10–30 seconds

* Red strip: ON
* Yellow strip: OFF
* Green strip: OFF
* TFT:

  * Walking man animation
  * Large numeric countdown (seconds)

---

## Return to IDLE

After countdown reaches zero:

* All LED strips OFF
* TFT shows "Press button to start"
* System awaits next button press

---

## State Flow Summary

IDLE → FLASH_RED → SOLID_RED →
(RED_CLEAR → GREEN_STATE → YELLOW_STATE) × 3 →
WALK_SOLID → WALK_COUNTDOWN → IDLE

---

## Visual Summary Table

| Phase          | Red Strip | Yellow Strip | Green Strip | Display           |
| -------------- | --------- | ------------ | ----------- | ----------------- |
| FLASH_RED      | Flashing  | Off          | Off         | Red Flash         |
| SOLID_RED      | On        | Off          | Off         | Red               |
| RED_CLEAR      | On        | Off          | Off         | Red Clear         |
| GREEN_STATE    | Off       | Off          | On          | Green             |
| YELLOW_STATE   | Off       | On           | Off         | Yellow            |
| WALK_SOLID     | On        | Off          | Off         | Walk animation    |
| WALK_COUNTDOWN | On        | Off          | Off         | Walk + countdown  |
| IDLE           | Off       | Off          | Off         | Start instruction |
