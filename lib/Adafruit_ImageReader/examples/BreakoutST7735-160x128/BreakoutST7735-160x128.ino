// Adafruit_ImageReader test for Adafruit ST7735 TFT Breakout for Arduino.
// Demonstrates loading images to the screen, to RAM, and how to query
// image file dimensions.
// Requires three BMP files in root directory of SD card:
// parrot.bmp, miniwoof.bmp and wales.bmp.
// As written, this uses the microcontroller's SPI interface for the screen
// (not 'bitbang') and must be wired to specific pins (e.g. for Arduino Uno,
// MOSI = pin 11, MISO = 12, SCK = 13). Other pins are configurable below.

#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>         // Core graphics library
#include <Adafruit_ST7735.h>      // Hardware-specific library
#include <Adafruit_ImageReader.h> // Image-reading functions

// TFT display and SD card share the hardware SPI interface, using
// 'select' pins for each to identify the active device on the bus.

#define SD_CS    4 // SD card select pin
#define TFT_CS  10 // TFT select pin
#define TFT_DC   8 // TFT display/command pin
#define TFT_RST  9 // Or set to -1 and connect to Arduino RESET pin

Adafruit_ST7735      tft    = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Adafruit_ImageReader reader;     // Class w/image-reading functions
Adafruit_Image       img;        // An image loaded into RAM
int32_t              width  = 0, // BMP image dimensions
                     height = 0;

void setup(void) {

  ImageReturnCode stat; // Status from image-reading functions

  Serial.begin(9600);
#if !defined(ESP32)
  while(!Serial);       // Wait for Serial Monitor before continuing
#endif

  tft.initR(INITR_GREENTAB); // Initialize screen

  Serial.print(F("Initializing SD card..."));
  if(!SD.begin(SD_CS)) {
    Serial.println(F("failed!"));
    for(;;); // Loop here forever
  }
  Serial.println(F("OK!"));

  // Fill screen blue. Not a required step, this just shows that we're
  // successfully communicating with the screen.
  tft.fillScreen(ST7735_BLUE);

  // Load full-screen BMP file 'parrot.bmp' at position (0,0) (top left).
  // Notice the 'reader' object performs this, with 'tft' as an argument.
  Serial.print(F("Loading parrot.bmp to screen..."));
  stat = reader.drawBMP("/parrot.bmp", tft, 0, 0);
  reader.printStatus(stat);   // How'd we do?

  // Query the dimensions of image 'miniwoof.bmp' WITHOUT loading to screen:
  Serial.print(F("Querying miniwoof.bmp image size..."));
  stat = reader.bmpDimensions("/miniwoof.bmp", &width, &height);
  reader.printStatus(stat);   // How'd we do?
  if(stat == IMAGE_SUCCESS) { // If it worked, print image size...
    Serial.print(F("Image dimensions: "));
    Serial.print(width);
    Serial.write('x');
    Serial.println(height);
  }

  // Load small BMP 'wales.bmp' into a GFX canvas in RAM. This should fail
  // gracefully on Arduino Uno and other small devices, meaning the image
  // will not load, but this won't make the program stop or crash, it just
  // continues on without it. Should work on Arduino Mega, Zero, etc.
  Serial.print(F("Loading wales.bmp to canvas..."));
  stat = reader.loadBMP("/wales.bmp", img);
  reader.printStatus(stat); // How'd we do?

  delay(2000); // Pause 2 seconds before moving on to loop()
}

void loop() {
  for(int r=0; r<4; r++) { // For each of 4 rotations...
    tft.setRotation(r);    // Set rotation
    tft.fillScreen(0);     // and clear screen

    // Load 4 copies of the 'miniwoof.bmp' image to the screen, some
    // partially off screen edges to demonstrate clipping. Globals
    // 'width' and 'height' were set by bmpDimensions() call in setup().
    for(int i=0; i<4; i++) {
      reader.drawBMP("/miniwoof.bmp", tft,
        (tft.width()  * i / 3) - (width  / 2),
        (tft.height() * i / 3) - (height / 2));
    }

    delay(1000); // Pause 1 sec.

    // Draw 50 Welsh dragon flags in random positions. This has no effect
    // on memory-constrained boards like the Arduino Uno, where the image
    // failed to load due to insufficient RAM, but it's NOT fatal.
    for(int i=0; i<50; i++) {
      // Rather than reader.drawBMP() (which works from SD card),
      // a different function is used for RAM-resident images:
      img.draw(tft,                                    // Pass in tft object
        (int16_t)random(-img.width() , tft.width()) ,  // Horiz pos.
        (int16_t)random(-img.height(), tft.height())); // Vert pos
      // Reiterating a prior point: img.draw() does nothing and returns
      // if the image failed to load. It's unfortunate but not disastrous.
    }

    delay(2000); // Pause 2 sec.
  }
}
