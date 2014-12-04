
//
//// includes
//#include "LPD8806.h"
//#include <SPI.h>
//
//// defines
//#define DF_NUM_LEDS 32
//#define DF_DATA_PIN 2
//#define DF_CLK_PIN 3
//#define DF_WAIT 500
//
//LPD8806 ledStrip = LPD8806(DF_NUM_LEDS, DF_DATA_PIN, DF_CLK_PIN);
//
//// forward declarations
//
//void setup() {
//  ledStrip.begin();
//  Serial.begin(9600);
//  ledStrip.show();
//}
//
//void loop() {
//  for(int i = 0; i < DF_NUM_LEDS; i++)
//  {
//    ledStrip.setPixelColor(i, 127, 0, 0);
//    delay(500);
//  }  
//}
//
////function implementations
#include "LPD8806.h"
#include "SPI.h"
 
/*
 * digitale RGB LED Strips vom Typ LPD8806 steuern
 * Weiterentwicklung des Tutorials von Adafruit
 * Autorin: Silvia Rothen, rothen ecotronics, Bern, Switzerland
 * http://ecotronics.ch.honorius.sui-inter.net/wordpress/category/physical-computing/
*/
 
/*****************************************************************************/
 
// Anzahl RGB LEDs
int nLEDs = 32;
 
// Die zwei Arduino-Pins, mit denen der LED Strip verbunden ist
int dataPin  = 2;
int clockPin = 3;
 
// Den Strip initialisieren
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);
 
void setup() {
  // LED-Strip starten
  strip.begin();
  Serial.begin(9600);
  // Am Anfang sind alle LEDs aus
  strip.show();
}
 
//Hilfsroutine zum Überprüfen des Codes
void printRGB(int i, int j, int r, int g, int b) {
  Serial.print(i);
  Serial.print(" ");
  Serial.print(j);
  Serial.print(" ");
  Serial.print(r);
  Serial.print("/");
  Serial.print(g);
  Serial.print("/");
  Serial.print(b);
  Serial.println();
}
 
//Die LED werden von Links nach Rechts einzeln zugeschaltet,
//wobei die Farben von Blau über Rot und Gelb bis zu Weiss laufen
//Es brennt nur die im Parameter anzahl übergebene Anzahl LEDs gleichzeitig
void hotline(int wait, int anzahl) {
  int i = 0;
  int r = 0;
  int g = 0;
  int b = 127;
  int difference = 13;
  int steps = 11;
  int j = 0;
  for (i = 0; i < strip.numPixels() + anzahl; i++) {
    r = constrain(i * difference, 0, 127);
    if (i > steps) {
      g = constrain((i - steps) * difference, 0, 127);
    } else {
      g = 0;
    }
    if (i < steps) {
      b = constrain(127 - i * difference, 0, 127);
    } else {
      if (i > steps * 2) {
        b = constrain((i - (steps * 2)) * difference, 0, 127);
      } else {
        b = 0;
      }
    }
    strip.setPixelColor(i, strip.Color(r, g, b));
    if (i >= anzahl) {
      strip.setPixelColor((i - anzahl), 0);
    }
    printRGB(i, 0, r, g, b);
    strip.show();
    delay(wait);
  }
}
 
//Farblich das gleiche wie oben,
//aber jetzt werden die LEDs von aussen nach innen eingeschaltet
void getHot(int wait) {
  int i = 0;
  int j = 0;
  int r = 0;
  int g = 0;
  int b = 127;
  int difference = 26;
 
  for (i=0; i < 5; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
    j = strip.numPixels() - 1 - i;
    strip.setPixelColor(j, strip.Color(r, g, b));
    strip.show();
    r = constrain(r + difference, 0, 127);
    b = constrain(b - difference, 0, 127);
    printRGB(i, j, r, g, b);
    delay(wait);
  }
 
  for (i=5; i < 10; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
    j = strip.numPixels() - 1 - i;
    strip.setPixelColor(j, strip.Color(r, g, b));
    strip.show();
    //r = constrain(r - 32, 0, 127);
    g = constrain(g + difference, 0, 127);
    printRGB(i, j, r, g, b);
    delay(wait);
  }
 
  for (i=10; i < 16; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
    j = strip.numPixels() - 1 - i;
    strip.setPixelColor(j, strip.Color(r, g, b));
    strip.show();
    b = constrain(b + difference, 0, 127);
    printRGB(i, j, r, g, b);
    delay(wait);
  }
  strip.show();
}
 
//Hilfsfunktion zum Ausschalten aller LEDs zwischen 2 Mustern
void allOut() {
  int i = 0;
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);
  delay(1000);
}

//überladene Methode, damit die alte Schnittstelle noch gültig ist
void colorWipe(uint32_t c, uint8_t wait) {
  colorWipe(c, wait, false);
}
 
// Fill the dots progressively along the strip.
// Der Parameter backwards ermöglicht,
// dass die LEDs in beide Richtungen laufen
void colorWipe(uint32_t c, uint8_t wait, boolean backwards) {
  int i;
  int pos; //pos ersetzt i für beidseitige Lauflichter
 
  for (i=0; i < strip.numPixels(); i++) {
    //in welche Richtung laufen die Lichter
    if (backwards) {
      pos = strip.numPixels() - i - 1;
    } else {
      pos = i;
    }
    strip.setPixelColor(pos, c);
    strip.show();
    delay(wait);
  }
}

void loop() {
  colorWipe(strip.Color(127,   0,   0), 50);  // Red
  //dank überladener Methode benötigt nur jeder 2. Aufruf den 3. Parameter
  colorWipe(strip.Color(  0, 127,   0), 50, true);  // Green
  colorWipe(strip.Color(  0,   0, 127), 50);  // Blue
  colorWipe(strip.Color(  127, 127,   0), 50, true);  // Yellow
}
