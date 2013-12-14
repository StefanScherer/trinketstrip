// trinketstrip

#include <avr/power.h>
#include <Adafruit_NeoPixel.h>

#define RED_LED 1                 // pulse 'digital' pin 1 - AKA the built in red LED
#define NUM_OF_PIXELS_IN_STRIP 8
#define STRIP_PIN 0

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_OF_PIXELS_IN_STRIP, STRIP_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // initialize trinket to run at 16MHz
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  
  // initialize the digital pin as an output.
  pinMode(RED_LED, OUTPUT);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
/*
strip.setBrightness(30);
   strip.setPixelColor(0, 0,0,0);
   strip.setPixelColor(1, 0,0,0);
   strip.setPixelColor(2, 0,0,0);
   strip.setPixelColor(3, 0,0,0);
   strip.setPixelColor(4, 0,0,0);
   strip.setPixelColor(5, 0,0,0);
   strip.setPixelColor(6, 0,0,0);
   strip.setPixelColor(7, 0,0,0);
*/
}

void loop() {
  // Some example procedures showing how to display to the pixels:

  for (int i=0; i<256; i++) {
    strip.setPixelColor(0, i,0,0);
    strip.setPixelColor(1, 0,i,0);
    strip.setPixelColor(2, 0,0,i);
    strip.show();
    analogWrite(led, i); // PWM the LED from 0 to 255 (max)
   
    delay(5);
    }

  for (int i=255; i>=0; i--) {
    strip.setPixelColor(0, i,0,0);
    strip.setPixelColor(1, 0,i,0);
    strip.setPixelColor(2, 0,0,i);
    strip.show();
    analogWrite(RED_LED, i); // PWM the LED from 0 to 255 (max)
   
    delay(5);
    }

  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  rainbow(20);
  rainbowCycle(20);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

