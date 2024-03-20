#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN    7
#define PIXEL_COUNT  90

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB); //create and initialize neopixel strip object

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip.setBrightness(100); //set brightness of neopixel strip
}

int lastValue=0; //initializing value to 0 OUTSIDE OF THE LOOP

void loop() {
  // put your main code here, to run repeatedly:
  lastValue=asyncRainbow(10, lastValue); //sending the last value returned from the function back into the function to resume the loop
  //quasi async function - still uses delay but not constrained by a delay within a for loop
}

int asyncRainbow(int wait, int lastValue){
  long firstPixelHue=(lastValue<5*65536) ? lastValue+256 : 0; //set the current value to incremented previous value or 0 if out of bounds
  Serial.println(firstPixelHue);
  for(int i=0;i<strip.numPixels();i++){ //hue shift the pixels
    int pixelHue = firstPixelHue + (i*65536 / strip.numPixels());
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
  }
  strip.show();
  delay(wait); //set delay
  return firstPixelHue; //return the incremented value back to the function to continue recursive cycle
}