#include <Wire.h>
#include <Adafruit_MCP23017.h>

Adafruit_MCP23017 mcp;

// defines variables
int rad;
int kol;
int i;
int j;
int plass;
int sensor[16] = {};
bool sensorDetect = true;
bool firstNo = true;
long prevPrint = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("\nSerial begin");
  for (rad = 0; rad < 7; rad++) {
    mcp.begin(rad);                     // adresses corresponding porter expander
    for (kol = 0; kol < 16; kol++) {
      Serial.print(".");
      mcp.pinMode(kol, INPUT);          // sets pins as INPUT
      mcp.pullUp(kol, HIGH);            // turn on a 100K pullup internally
    }
  }

  Serial.println("\nloop start:");
}


void loop()
{
  for (j = 0; j < 7; j ++) {
    mcp.begin(j);
    for (i = 0; i < 16; i ++) {
      plass = i;
      sensor[plass] = mcp.digitalRead(i);
      if(!sensor[plass]){
        sensorDetect = true;
        firstNo = true;
        Serial.println("rad: " + String(j) + " kol: " + String(i));   // prints number of row and colum of the sensor a magnet has been detected, i.e. sensor[plass] == low
      }
    }
  }

  if (!sensorDetect && (firstNo || (prevPrint + 1000 < millis()))){
    Serial.println("No sensor detect");                               // prints to serial monitor once every second if there is not done any detection on any of the sensor
    prevPrint = millis();
    firstNo = false;
  }

  sensorDetect = false;
}
