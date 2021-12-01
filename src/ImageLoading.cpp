/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/rwbre/Desktop/ImageLoading/src/ImageLoading.ino"
/*
 * Project ImageLoading
 * Description:
 * Author:
 * Date:
 */
#include <Adafruit_ST7735.h>      // Hardware-specific library
#include <SdFat.h>                // SD card & FAT filesystem library
#include <Adafruit_ImageReader.h> // Image-reading functions

void setup();
void loop();
#line 11 "c:/Users/rwbre/Desktop/ImageLoading/src/ImageLoading.ino"
#define SD_CS    D4 // SD card select pin
#define TFT_CS   A2 // TFT select pin
#define TFT_DC   D1 // TFT display/command pin
#define TFT_RST  D0 // Or set to -1 and connect to Arduino RESET pin

Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_RST);
SdFat sdFat;
Adafruit_ImageReader reader;     // Class w/image-reading functions
Adafruit_Image       img;        // An image loaded into RAM
int32_t              width  = 0, // BMP image dimensions
                     height = 0;
int BlackColor = tft.color565(0, 0, 0);
char lilyPath[] = "/lily128.bmp";
char darthPath[] = "/darth.bmp";
char batbotPath[] = "/batbot.bmp";
char marioPath[] = "/mario.bmp";

char popcornPath[] = "/popcorn2.bmp";

// setup() runs once, when the device is first turned on.
void setup() {

  Serial.begin(9600);
#if !defined(ESP32)
  while(!Serial);       // Wait for Serial Monitor before continuing
#endif

  tft.initR(BlackColor); // Initialize screen

  Serial.print(F("Initializing SD card..."));
  if(!sdFat.begin(SD_CS)) {
    Serial.println(F("failed!"));
    for(;;); // Loop here forever
  }
  Serial.println(F("OK!"));

  // Fill screen blue. Not a required step, this just shows that we're
  // successfully communicating with the screen.
  tft.fillScreen(ST7735_BLUE);


}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  ImageReturnCode stat; // Status from image-reading functions

  // The core of your code will likely live here.
// Load full-screen BMP file 'lily128.bmp' at position (0,0) (top left).
  // Notice the 'reader' object performs this, with 'tft' as an argument.
  Serial.print(F("Loading lily128.bmp to screen..."));
  stat = reader.drawBMP(lilyPath, tft, sdFat, 0, 0);
  reader.printStatus(stat);   // How'd we do?

  delay(500);

  Serial.print(F("Loading darth.bmp to screen..."));
  stat = reader.drawBMP(darthPath, tft, sdFat, 0, 0);
  reader.printStatus(stat);   // How'd we do?

  delay(500);

  Serial.print(F("Loading batbot.bmp to screen..."));
  stat = reader.drawBMP(batbotPath, tft, sdFat, 0, 0);
  reader.printStatus(stat);   // How'd we do?

  delay(500);

  Serial.print(F("Loading mario.bmp to screen..."));
  stat = reader.drawBMP(marioPath, tft, sdFat, 0, 0);
  reader.printStatus(stat);   // How'd we do?

  delay(500);
}
