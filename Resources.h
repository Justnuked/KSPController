#ifndef Resources_h
#define Resources_h

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "KerbalSimpit.h"

class Resources {
  public:
    Resources(uint8_t pin, uint8_t numOfLeds, KerbalSimpit mySimpit);
    handleResource(uint8_t numOfPixels, uint8_t offset, uint8_t r, uint8_t g, uint8_t b);
    switchChannels();
    
    int switchState;
  private:
    clearRange(uint8_t start, uint8_t end);

    uint8_t pin;
    uint8_t numOfLeds;
    KerbalSimpit mySimpit;
    Adafruit_NeoPixel strip;
};
#endif