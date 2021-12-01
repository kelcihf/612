// Example usage for Adafruit_ImageReader library by Adafruit, Brandon Satrom <brandon@particle.io>.

#include "Adafruit_ImageReader.h"

// Initialize objects from the lib
Adafruit_ImageReader adafruit_ImageReader;

void setup() {
    // Call functions on initialized library objects that require hardware
    adafruit_ImageReader.begin();
}

void loop() {
    // Use the library's initialized objects and functions
    adafruit_ImageReader.process();
}
