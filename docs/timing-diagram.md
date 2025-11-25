# Timing Diagram (Logical Phases)

Sequence timings:

1. **FLASH_RED** – 6 seconds
   - LEDs: red flashing (0.5 s on, 0.5 s off)
   - TFT: "RED FLASH (6s)" text

2. **SOLID_RED** – 6 seconds
   - LEDs: solid red
   - TFT: "RED"

3. **Vehicle cycles** – repeat 3 times:
   - **RED_CLEAR** – 10 s
     - LEDs: solid red
     - TFT: "RED CLEAR (10s)"
   - **GREEN_STATE** – 25 s
     - LEDs: solid green
     - TFT: "GREEN"
   - **YELLOW_STATE** – 3 s
     - LEDs: solid yellow
     - TFT: "YELLOW"

4. **Pedestrian phase**
   - **WALK_SOLID** – 7 s
     - LEDs: solid red
     - TFT: "WALK" + walking man animation
   - **WALK_COUNTDOWN** – random 10–30 s
     - LEDs: solid red
     - TFT: "WALK" + walking man animation + numeric countdown in seconds

5. On completion of countdown:
   - Return to **IDLE**:
     - LEDs: off
     - TFT: "Press button to start"

At **any time**, pressing the button:
- Immediately stops the current phase
- Returns system to **IDLE**
- Pressing the button again from IDLE restarts the entire sequence from FLASH_RED.
