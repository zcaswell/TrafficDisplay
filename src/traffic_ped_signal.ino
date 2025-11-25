#include <FastLED.h>
#include <OneButton.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// ---------------------- CONFIG ----------------------

// LED strips: one per traffic lamp (red, yellow, green)
#define NUM_LEDS      15     // LEDs per strip

#define RED_PIN       4
#define YELLOW_PIN    5
#define GREEN_PIN     6

// Button
#define BTN_PIN       2      // Momentary button to GND (INPUT_PULLUP)

// ILI9341 TFT (Adafruit 3.2" breakout in SPI mode)
#define TFT_CS        10
#define TFT_DC        9
#define TFT_RST       8

// LED arrays: one per color
CRGB redLeds[NUM_LEDS];
CRGB yellowLeds[NUM_LEDS];
CRGB greenLeds[NUM_LEDS];

// Button handler: active-low, with internal pull-up
OneButton btn(BTN_PIN, true, true);

// TFT display object
Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);

// ---------------------- STATE MACHINE ----------------------

enum SystemState {
  IDLE,
  FLASH_RED,
  SOLID_RED,
  RED_CLEAR,
  GREEN_STATE,
  YELLOW_STATE,
  WALK_SOLID,
  WALK_COUNTDOWN
};

SystemState state = IDLE;

bool running = false;
unsigned long stateStartMillis = 0;
unsigned long lastFlashMillis = 0;
bool flashOn = false;

uint8_t cycleCount = 0;
uint8_t countdownSeconds = 0;
unsigned long lastCountdownTick = 0;

// Walking animation
bool walkFrame = false;
unsigned long lastWalkAnimMillis = 0;

// ---------------------- LED HELPERS ----------------------

void clearAllLamps() {
  fill_solid(redLeds,    NUM_LEDS, CRGB::Black);
  fill_solid(yellowLeds, NUM_LEDS, CRGB::Black);
  fill_solid(greenLeds,  NUM_LEDS, CRGB::Black);
}

void showRedLamp() {
  clearAllLamps();
  fill_solid(redLeds, NUM_LEDS, CRGB::Red);
}

void showYellowLamp() {
  clearAllLamps();
  fill_solid(yellowLeds, NUM_LEDS, CRGB::Yellow);
}

void showGreenLamp() {
  clearAllLamps();
  fill_solid(greenLeds, NUM_LEDS, CRGB::Green);
}

// ---------------------- TFT HELPERS ----------------------

void clearScreen(uint16_t color = ILI9341_BLACK) {
  tft.fillScreen(color);
}

// Draw a simple walking man at (x, y).
void drawWalkingMan(int16_t x, int16_t y, bool frame) {
  // Erase area around sprite to avoid smearing
  tft.fillRect(x - 30, y - 60, 60, 100, ILI9341_BLACK);

  uint16_t col = ILI9341_WHITE;

  // Head
  tft.drawCircle(x, y - 40, 10, col);

  // Body
  tft.drawLine(x, y - 30, x, y + 5, col);

  // Arms
  tft.drawLine(x, y - 25, x - 18, y - 5, col);
  tft.drawLine(x, y - 25, x + 18, y - 5, col);

  // Legs – alternate pattern
  if (!frame) {
    // left forward, right back
    tft.drawLine(x, y + 5, x - 16, y + 35, col);
    tft.drawLine(x, y + 5, x + 8,  y + 30, col);
  } else {
    // right forward, left back
    tft.drawLine(x, y + 5, x + 16, y + 35, col);
    tft.drawLine(x, y + 5, x - 8,  y + 30, col);
  }
}

// Show WALK phase screen (for WALK_SOLID)
void showWalkScreen() {
  clearScreen(ILI9341_BLACK);

  // Title at top
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.print("WALK");

  // Center walking man roughly in the middle
  walkFrame = false;
  drawWalkingMan(120, 160, walkFrame);
  lastWalkAnimMillis = millis();
}

// Show WALK + countdown (for WALK_COUNTDOWN)
void showWalkCountdownScreen(uint8_t seconds) {
  clearScreen(ILI9341_BLACK);

  // Title
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.print("WALK");

  // Big countdown number near bottom
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(4);  // large digits on 240x320
  tft.setCursor(90, 250);
  tft.print(seconds);

  // Walking man in middle
  walkFrame = false;
  drawWalkingMan(120, 160, walkFrame);
  lastWalkAnimMillis = millis();
}

// Update walking animation frame if in a WALK state
void updateWalkAnimation(unsigned long now) {
  if (now - lastWalkAnimMillis >= 250) { // 4 fps
    lastWalkAnimMillis = now;
    walkFrame = !walkFrame;
    drawWalkingMan(120, 160, walkFrame);
  }
}

// ---------------------- STATE HELPERS ----------------------

void gotoState(SystemState newState);

void stopSequence() {
  running = false;
  gotoState(IDLE);
}

void startSequence() {
  running = true;
  cycleCount = 0;
  gotoState(FLASH_RED);
}

// Button callback: toggle run/stop
void handleClick() {
  if (!running) {
    startSequence();
  } else {
    stopSequence();
  }
}

// Change state + entry actions
void gotoState(SystemState newState) {
  state = newState;
  stateStartMillis = millis();

  switch (state) {
    case IDLE:
      clearAllLamps();
      clearScreen(ILI9341_BLACK);
      tft.setTextColor(ILI9341_CYAN);
      tft.setTextSize(2);
      tft.setCursor(10, 150);
      tft.print("Press button to start");
      break;

    case FLASH_RED:
      flashOn = false;
      lastFlashMillis = 0;
      clearAllLamps();
      clearScreen(ILI9341_BLACK);
      tft.setTextColor(ILI9341_RED);
      tft.setTextSize(2);
      tft.setCursor(40, 150);
      tft.print("RED FLASH (6s)");
      break;

    case SOLID_RED:
      showRedLamp();
      clearScreen(ILI9341_BLACK);
      tft.setTextColor(ILI9341_RED);
      tft.setTextSize(4);
      tft.setCursor(80, 140);
      tft.print("RED");
      break;

    case RED_CLEAR:
      showRedLamp();
      clearScreen(ILI9341_BLACK);
      tft.setTextColor(ILI9341_RED);
      tft.setTextSize(2);
      tft.setCursor(40, 150);
      tft.print("RED CLEAR (10s)");
      break;

    case GREEN_STATE:
      showGreenLamp();
      clearScreen(ILI9341_BLACK);
      tft.setTextColor(ILI9341_GREEN);
      tft.setTextSize(3);
      tft.setCursor(60, 140);
      tft.print("GREEN");
      break;

    case YELLOW_STATE:
      showYellowLamp();
      clearScreen(ILI9341_BLACK);
      tft.setTextColor(ILI9341_YELLOW);
      tft.setTextSize(3);
      tft.setCursor(40, 140);
      tft.print("YELLOW");
      break;

    case WALK_SOLID:
      // Vehicles red, walking man animation
      showRedLamp();
      showWalkScreen();
      break;

    case WALK_COUNTDOWN:
      // Vehicles still red, walking man + countdown
      showRedLamp();
      countdownSeconds = random(10, 31);  // 10-30 inclusive
      showWalkCountdownScreen(countdownSeconds);
      lastCountdownTick = millis();
      break;
  }
}

// ---------------------- SETUP / LOOP ----------------------

void setup() {
  // WS2812B LED strips: one per lamp
  FastLED.addLeds<WS2812B, RED_PIN,    GRB>(redLeds,    NUM_LEDS);
  FastLED.addLeds<WS2812B, YELLOW_PIN, GRB>(yellowLeds, NUM_LEDS);
  FastLED.addLeds<WS2812B, GREEN_PIN,  GRB>(greenLeds,  NUM_LEDS);
  FastLED.setBrightness(80);
  clearAllLamps();
  FastLED.show();

  // Button
  pinMode(BTN_PIN, INPUT_PULLUP);
  btn.attachClick(handleClick);

  // ILI9341 TFT
  tft.begin();           // initialize display
  tft.setRotation(0);    // 0 = portrait (240x320)
  clearScreen(ILI9341_BLACK);

  // Random seed for countdown
  randomSeed(analogRead(A0));

  gotoState(IDLE);
}

void loop() {
  unsigned long now = millis();

  // Always process button
  btn.tick();

  switch (state) {
    case IDLE:
      break;

    case FLASH_RED:
      // Flash red for 6 seconds (0.5 s on/off)
      if (now - lastFlashMillis >= 500) {
        lastFlashMillis = now;
        flashOn = !flashOn;
        if (flashOn) {
          showRedLamp();
        } else {
          clearAllLamps();
        }
      }
      if (now - stateStartMillis >= 6000) {
        gotoState(SOLID_RED);
      }
      break;

    case SOLID_RED:
      if (now - stateStartMillis >= 6000) {
        cycleCount = 0;
        gotoState(RED_CLEAR);
      }
      break;

    case RED_CLEAR:
      if (now - stateStartMillis >= 10000) {
        gotoState(GREEN_STATE);
      }
      break;

    case GREEN_STATE:
      if (now - stateStartMillis >= 25000) {
        gotoState(YELLOW_STATE);
      }
      break;

    case YELLOW_STATE:
      if (now - stateStartMillis >= 3000) {
        cycleCount++;
        if (cycleCount >= 3) {
          gotoState(WALK_SOLID);
        } else {
          gotoState(RED_CLEAR);
        }
      }
      break;

    case WALK_SOLID:
      updateWalkAnimation(now);
      if (now - stateStartMillis >= 7000) {
        gotoState(WALK_COUNTDOWN);
      }
      break;

    case WALK_COUNTDOWN:
      updateWalkAnimation(now);
      if (now - lastCountdownTick >= 1000) {
        lastCountdownTick = now;
        if (countdownSeconds > 0) {
          countdownSeconds--;

          // Erase only the number region to reduce flicker
          tft.fillRect(80, 240, 120, 60, ILI9341_BLACK);
          tft.setTextColor(ILI9341_YELLOW);
          tft.setTextSize(4);
          tft.setCursor(90, 250);
          tft.print(countdownSeconds);
        } else {
          // Done: back to idle
          stopSequence();
        }
      }
      break;
  }

  // Push LED data out each loop
  FastLED.show();
}
