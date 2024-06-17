#include <Adafruit_NeoPixel.h>
#define PIN 2
#define NUM_PIX 40
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIX, PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
  strip.begin();
  strip.clear();
  strip.show();

}

void loop() 
{
  warmWhite();
}

void warmWhite(){
  for(int i=0; i<=NUM_PIX; i++){
    pixels.setPixelColor(i, pixels.Color(246,231,210));
  }
  pixels.show();
}
