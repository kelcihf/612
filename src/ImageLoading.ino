/*
 * Project Movie Theater WOz
 * Description: Allow TFT screen display to support voice UI
 * Author: for UMSI 612
 * Date: Oct 2020
 */
#include <Adafruit_ST7735.h>      // Hardware-specific library for TFT
#include <SdFat.h>                // SD card & FAT filesystem library
#include <Adafruit_ImageReader.h> // Image-reading functions
#include <string>
using namespace std;

#define SD_CS    D4 // SD card select pin
#define TFT_CS   A2 // TFT select pin
#define TFT_DC   D1 // TFT display/command pin
#define TFT_RST  D0 // Or set to -1 and connect to Arduino RESET pin
#define COLOR_CYAN 0x4F3F

Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_RST);
SdFat sdFat;
Adafruit_ImageReader reader;     // Class w/image-reading functions
Adafruit_Image       img;        // An image loaded into RAM
int32_t              width  = 0, // BMP image dimensions
                     height = 0;
int BlackColor = tft.color565(0, 0, 0);

// setup() runs once, when the device is first turned on.
void setup() {
  tft.initR(BlackColor); // Initialize screen black
  sdFat.begin(SD_CS); //start talking to the SD card

  // Fill screen blue to show that we're communicating with the screen.
  tft.fillScreen(ST7735_BLUE);
  Particle.function("showImage", showImage);
  Particle.function("face", setFace);
  Particle.function("writeMessage", writeMessageTFT);

  Serial.begin(9600); //ADDED THIS LINE FOR DEBUGGING IMAGE ISSUES
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // no loop for you
}


/* ********************************************************************
** We define functions here that we want to call from setup() or loop()
***********************************************************************
*/

//Function to draw a bitmap at (0,0) on the screen
int showImage(String image) {
  ImageReturnCode stat; // Status from image-reading functions
  stat = reader.drawBMP(const_cast<char*>(image.c_str()), tft, sdFat, 0, 0);
  Serial.println(stat);   // for debugging images. 0=OK, 1=FILE not found, 2=unsupported BMP variant, 3=insuffient RAM
  //reader.drawBMP(const_cast<char*>(image.c_str()), tft, sdFat, 0, 0);
  return 0; 

}

int setFace(String face) {
  if(face == "misch") {
    drawMischievousFace();
  } else if (face == "happy"){
    drawHappyFace();
  } else {
    drawHappyFace(); //Default
  }
  return 0; 
}

//function to draw a misch face
void drawMischievousFace() {
  tft.fillScreen(BlackColor);
  tft.fillRoundRect(18,30,40,20,8,COLOR_CYAN);//eye
  tft.fillRoundRect(70,40,40,30,4,COLOR_CYAN);//eye
  tft.fillRoundRect(25,100,75,8,5,COLOR_CYAN);//mouth

}

//function to draw a happy face
void drawHappyFace() {
  tft.fillScreen(BlackColor);
  tft.fillRoundRect(18,30,40,20,8,COLOR_CYAN);//eyes
  tft.fillRoundRect(67,30,40,20,8,COLOR_CYAN);//eyes
  tft.fillCircle(38,59,23,BlackColor);//eyes
  tft.fillCircle(87,59,23,BlackColor);//eyes
  tft.fillRoundRect(25,100,75,8,0,COLOR_CYAN);//mouth
  tft.fillRoundRect(21,93,7,6,0,COLOR_CYAN);//mouth turn up left
  tft.fillRoundRect(98,93,7,6,0,COLOR_CYAN);//mouth turn up right

}

int writeMessageTFT(String message) {
  tft.fillScreen(BlackColor);
  tft.setTextColor(COLOR_CYAN);
  tft.setCursor(5, 5);
  tft.setTextSize(2);
  tft.setTextWrap(true);
  tft.print(message);
  return 0; 

}
