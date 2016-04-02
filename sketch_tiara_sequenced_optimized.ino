//Random Flash animation for Neopixel circuits
//by Dano Wall and Becky Stern for Adafruit Industries
//based on the Sparkle Skirt, minus the accelerometer
//
// Sequences and additional color sets added by Rick Johns 2014-09-18

#include <Adafruit_NeoPixel.h>

#define PIN 1

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(7, PIN, NEO_GRB + NEO_KHZ800);

// Here is where you can put in your favorite colors that will appear!
// just add new {nnn, nnn, nnn}, lines. They will be picked out randomly.
// All color sets need to be the same size.
//                          R   G   B
uint8_t colorSet1[][3] = {{232, 100, 255},  // purple
                          {200, 200, 20},   // yellow 
                          {30, 200, 200},   // baby blue
                         };
uint8_t colorSet2[][3] = {{232, 0, 255},   // violet
                          {255, 0, 0},     // red 
                          {0, 0, 255},     // blue
                         };
uint8_t colorSet3[][3] = {{232, 200, 0},   // orange
                          {150, 150, 0},   // yellow 
                          {200, 0, 0},     // red
                         };
uint8_t colorSet4[][3] = {{232, 200, 0},   // orange
                          {0, 150, 0},     // green 
                          {0, 200, 0},     // blue
                         };

#define SETS 4

// don't edit the line below. This is the number of colors in each set.
#define FAVCOLORS sizeof(colorSet1) / 3

void setup() {
  strip.begin();
  strip.setBrightness(40);
  strip.show(); // Initialize all pixels to 'off'
} 

void loop() {
  int s = random(SETS);
  switch (s) {
    case 0:
      flashSideToSide(5, 1, colorSet1);  // first number is 'wait' delay, shorter num == shorter twinkle
      flashSideToSide(5, 0, colorSet1);  
      flashSideToSide(5, 1, colorSet1);
      flashSideToSide(5, 0, colorSet1);  
      break;
  case 1:
      flashSideToSide(5, 1, colorSet2);
      flashSideToSide(5, 0, colorSet2);  
      flashSideToSide(5, 1, colorSet2);
      flashSideToSide(5, 0, colorSet2); 
      break;
  case 2:
      flashSideToSide(5, 1, colorSet3);
      flashSideToSide(5, 0, colorSet3);  
      flashSideToSide(5, 1, colorSet3);
      flashSideToSide(5, 0, colorSet3);  
      break;
    default:
      flashSideToSide(5, 1, colorSet4);
      flashSideToSide(5, 0, colorSet4);  
      flashSideToSide(5, 1, colorSet4);
      flashSideToSide(5, 0, colorSet4);  
  }
  
  s = random(SETS);
  switch (s) {
    case 0:
      flashOutIn(5, colorSet1);  // first number is 'wait' delay, shorter num == shorter twinkle
      flashOutIn(5, colorSet1);  
      flashOutIn(5, colorSet1);
      break;
    case 1:
      flashOutIn(5, colorSet2);
      flashOutIn(5, colorSet2);  
      flashOutIn(5, colorSet2);
      break;
    case 2:
      flashOutIn(5, colorSet3);
      flashOutIn(5, colorSet3);  
      flashOutIn(5, colorSet3);
      break;
    default:
      flashOutIn(5, colorSet4);
      flashOutIn(5, colorSet4);  
      flashOutIn(5, colorSet4);
  }

  s = random(SETS);
    for(uint16_t i=0; i<4; i++) {
      switch (s) {
        case 0:
          flashRandom(5, 1, colorSet1);  // first number is 'wait' delay, shorter num == shorter twinkle
          flashRandom(5, 3, colorSet1);  // second number is how many neopixels to simultaneously light up
          flashRandom(5, 2, colorSet1);
          break;
        case 1:
          flashRandom(5, 1, colorSet2);
          flashRandom(5, 3, colorSet2);
          flashRandom(5, 2, colorSet2);
          break;
        case 2:
          flashRandom(5, 1, colorSet3);
          flashRandom(5, 3, colorSet3);
          flashRandom(5, 2, colorSet3);
          break;
        default:
          flashRandom(5, 1, colorSet4);
          flashRandom(5, 3, colorSet4);
          flashRandom(5, 2, colorSet4);
      }
    }
}

void flashRandom(int wait, uint8_t howmany, uint8_t colorSet[][3]) {
 
  for(uint16_t i=0; i<howmany; i++) {
    // get a random pixel from the list
    int pixel = random(strip.numPixels());
    
    doFades(pixel, -1, wait, colorSet);
  }
}

void flashOutIn(int wait, uint8_t colorSet[][3]) {
 
  // Loop in enough steps to work from the outside in.
  // Assuming 0 is on the right.
  // For example, with 7 pixels, the steps are:
  //   6,0
  //   5,1
  //   4,2
  //   3
  uint16_t oddCount = strip.numPixels() % 2;
  uint16_t numSteps = (strip.numPixels() / 2) + oddCount;
  
  for(uint16_t right=0; right < strip.numPixels(); right++) {
    // See if this is the middle pixel, when there's an odd number.
    int isMiddle = (oddCount && (right == (numSteps - 1)));

    // get the next pixel from the other side
    int left = strip.numPixels() - right;

    if (isMiddle) {
        doFades(left, -1, wait, colorSet);
    }
    else {
        doFades(left, right, wait, colorSet);
    }
  }
}

void doFades(uint16_t pixel1, uint16_t pixel2, int wait, uint8_t colorSet[][3]) {
   // pick a random favorite color!
    int c = random(FAVCOLORS);
    int red = colorSet[c][0];
    int green = colorSet[c][1];
    int blue = colorSet[c][2]; 
 
    // now we will 'fade' them in 5 steps
    for (int x=0; x < 5; x++) {
      int r = red * (x+1); r /= 5;
      int g = green * (x+1); g /= 5;
      int b = blue * (x+1); b /= 5;
      
       strip.setPixelColor(pixel1, strip.Color(r, g, b));
       if (pixel2 >= 0) {
         strip.setPixelColor(pixel2, strip.Color(r, g, b));
       }
       strip.show();
      delay(wait);
    }
    // & fade out in 5 steps
    for (int x=5; x >= 0; x--) {
      int r = red * x; r /= 5;
      int g = green * x; g /= 5;
      int b = blue * x; b /= 5;
      
      strip.setPixelColor(pixel1, strip.Color(r, g, b));
      if (pixel2 >= 0) {
        strip.setPixelColor(pixel2, strip.Color(r, g, b));
      }
      strip.show();
      delay(wait);
    }
}

void flashSideToSide(int wait, int startRight, uint8_t colorSet[][3]) {
 
  // Loop in enough steps to work from the outside in.
  // Assuming 0 is on the right.

  int incr = 1;
  int start = 0;
  if (!startRight) {
    incr = -1;
    start = strip.numPixels() -1;
  }
  
  for(uint16_t pixel=start; pixel < strip.numPixels() && pixel >= 0; pixel+=incr) {
    doFades(pixel, -1, wait, colorSet);
  }
}
