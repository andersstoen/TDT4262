#include <Wire.h>
#include <Adafruit_MCP23017.h>
Adafruit_MCP23017 mcp;
#include "FastLED.h"
#define NUM_LEDS 40
#define DATA_PIN 6
#define COLOR_ORDER GRB


int fadeAmount = 5;
int brightness = 0;
CRGB leds[NUM_LEDS];

int dv1 = 5;  // Delay for active LEDs.
int dv2 = 20;

int sumofinputs = 0;  // Sum of signals for switch between LED idle and active.

int plassA; // Placeholder in for-loops.
int plassB;

int plass;
int sensor[112] = {};

int hallStateA = 1; // Initial hall sensor status
int hallStateB = 1;


float sensorData[56] = {};

float currentcol[7] = {1, 1, 1, 1, 1, 1, 1};

int rad;
int kol;
int i;
int j;
int l;
int k;
int m;


void setup() {

  Serial.begin(9600);

  FastLED.addLeds<WS2812B, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip ); // LED setup.

  for (rad = 0; rad < 7; rad++) {
    mcp.begin(rad); //creates a Wire object
    for (kol = 0; kol < 16; kol++) {
      mcp.pinMode(kol, INPUT); //definerer alle portexpanderpins som inputs
      mcp.pullUp(kol, HIGH); // turn on a 100K pullup internally
    }
  }
}

void loop() {

  for (j = 0; j < 7; j ++) {
    mcp.begin(j);
    for (i = 0; i < 16; i ++) {
      plass = i + j * 16;
      sensor[plass] = mcp.digitalRead(i); //Lager en 1x112 array med verdier 1 eller 0, der 0 betyr magnet og 1 betyr ikke-magnet
    }
  }

  plassA = 0; //disse holder styr på hvilken plass i arrayen som leses
  plassB = 1;

  for (k = 0; k < 56; k++) { //tolker sensorverdiene fra "sensor" og lager et array på 56 elementer analogt med hvordan brettet vil se ut


    hallStateA = sensor[plassA];
    hallStateB = sensor[plassB];

    if ((hallStateA == 0) & (hallStateB == 0)) {
      sensorData[k] = 8.0;
      sumofinputs += 1;
    }

    else if ((hallStateA == 0) & (hallStateB == 1)) {
      sensorData[k] = 4.0;

      plassA = plassA + 2;
      plassB = plassB + 2;

      k = k + 1;
      sumofinputs += 1;
    }

    else if ((hallStateA == 1) & (hallStateB == 0)) {
      sensorData[k] = 2.0;

      plassA = plassA + 6;
      plassB = plassB + 6;

      k = k + 3;
      sumofinputs += 1;
    }

    else {
      sensorData[k] = 0;
    }

    plassA = plassA + 2;
    plassB = plassB + 2;
  }

  if (sumofinputs == 0) {
    // Idle LED show.
    for (int i = 0; i < NUM_LEDS; i++ ) {
      leds[i].setRGB(0, 255, 250);
      leds[i].fadeLightBy(brightness);
    }
    FastLED.show();
    brightness = brightness + fadeAmount;
    if (brightness == 0 || brightness == 255) {
      fadeAmount = -fadeAmount ;
    }
    delay(9);
  }

  else {
    // Active loop upon detection of signal.
    for (k = 0; k < 8; k++) {

      for (l = 0; l < 7; l++) {
        currentcol[l] = sensorData[k + 8 * l];

        Serial.print(currentcol[l]);
        Serial.print(" ");

      }

      Serial.println(" ");

      FastLED.delay(100);
      leds[k * 5] = CRGB::White;
      FastLED.show();
      FastLED.delay(dv1);
      leds[k * 5 + 1] = CRGB::White;
      FastLED.show();
      FastLED.delay(dv1);
      leds[k * 5 + 2] = CRGB::White;
      FastLED.show();
      FastLED.delay(dv1);
      leds[k * 5 + 3] = CRGB::White;
      FastLED.show();
      FastLED.delay(dv1);
      leds[k * 5 + 4] = CRGB::White;
      FastLED.show();
      FastLED.delay(dv1);

      delay(225); // Trekker fra summen av delays fra LED.
      leds[k * 5] = CRGB::Black;
      FastLED.delay(dv2);
      leds[k * 5 + 1] = CRGB::Black;
      FastLED.delay(dv2);
      leds[k * 5 + 2] = CRGB::Black;
      FastLED.delay(dv2);
      leds[k * 5 + 3] = CRGB::Black;
      FastLED.delay(dv2);
      leds[k * 5 + 4] = CRGB::Black;
      FastLED.delay(dv2);

    }

    sumofinputs = 0;

  }
}






