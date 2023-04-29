#include "KerbalSimpitMessageTypes.h"
#include "Resources.h"
#include <Adafruit_NeoPixel.h>
#include "KerbalSimpit.h"

Resources::Resources(uint8_t pin, uint8_t numOfLeds, KerbalSimpit mySimpit)
    : pin(pin), numOfLeds(numOfLeds), mySimpit(mySimpit), strip(Adafruit_NeoPixel(numOfLeds, pin, NEO_GRB + NEO_KHZ800)){
  strip.begin();
  strip.setBrightness(50);
}

Resources::clearRange(uint8_t start, uint8_t end){
    for(int i = start; i < end; i++){
      strip.setPixelColor(i, strip.Color(0,0,0));
  }
}

Resources::handleResource(uint8_t numOfPixels, uint8_t offset, uint8_t r, uint8_t g, uint8_t b){
    clearRange(offset, offset + 16);

    for (int i=0; i < numOfPixels; i++){
      strip.setPixelColor(i + offset, strip.Color(r,g,b));
    }

    strip.show();
}

Resources::switchChannels(){
  if(switchState == 1){
      mySimpit.deregisterChannel(LF_STAGE_MESSAGE);
      mySimpit.deregisterChannel(OX_STAGE_MESSAGE);
      mySimpit.deregisterChannel(SF_STAGE_MESSAGE);
      mySimpit.deregisterChannel(XENON_GAS_STAGE_MESSAGE);

      mySimpit.registerChannel(LF_MESSAGE);
      mySimpit.registerChannel(OX_MESSAGE);
      mySimpit.registerChannel(SF_MESSAGE);
      mySimpit.registerChannel(XENON_GAS_MESSAGE);
  }else{
      mySimpit.deregisterChannel(LF_MESSAGE);
      mySimpit.deregisterChannel(OX_MESSAGE);
      mySimpit.deregisterChannel(SF_MESSAGE);
      mySimpit.deregisterChannel(XENON_GAS_MESSAGE);

      mySimpit.registerChannel(LF_STAGE_MESSAGE);
      mySimpit.registerChannel(OX_STAGE_MESSAGE);
      mySimpit.registerChannel(SF_STAGE_MESSAGE);
      mySimpit.registerChannel(XENON_GAS_STAGE_MESSAGE);
  }
}