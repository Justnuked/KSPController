#include "KerbalSimpit.h"
#include <Adafruit_NeoPixel.h>
#include "Resources.h"

#define PIN      6
#define N_LEDS   80
#define resourceSwitchPin 8

// Declare a KerbalSimpit object that will
// communicate using the "Serial" device.
KerbalSimpit mySimpit(Serial);
Resources resourceManager(PIN, N_LEDS, mySimpit);
int resourceSwitchState = 0;

void setup() {
  // Open the serial connection.
  Serial.begin(115200); //115200

  pinMode(resourceSwitchPin, INPUT_PULLUP);
  resourceSwitchState = digitalRead(resourceSwitchPin);
  resourceManager.switchState = resourceSwitchState;
  resourceManager.switchChannels();

  // Set up the build in LED, and turn it on.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  //Handshaking
  while (!mySimpit.init()) {
    delay(100);
  }
  digitalWrite(LED_BUILTIN, LOW);
  mySimpit.printToKSP("Connected", PRINT_TO_SCREEN);
  mySimpit.inboundHandler(messageHandler);
  mySimpit.registerChannel(MONO_MESSAGE);
}

void loop() {
  resourceSwitchState = digitalRead(resourceSwitchPin);

  if(resourceManager.switchState != resourceSwitchState){
    resourceManager.switchState = !resourceManager.switchState;
    resourceManager.switchChannels();
  }

  mySimpit.update();
}

int calcResourcePercentage(float available, float total){
    float fuelPercentage = 16 * (available / total); // 16 LEDS in NeoPixelstrand
    return (int) fuelPercentage;
}

void messageHandler(byte messageType, byte msg[], byte msgSize) {
  switch(messageType) {
    case LF_MESSAGE:
    case LF_STAGE_MESSAGE:
        if (msgSize == sizeof(resourceMessage)) {
          resourceMessage fuelMsg = parseMessage<resourceMessage>(msg);
          int fuel = calcResourcePercentage(fuelMsg.available, fuelMsg.total);
          resourceManager.handleResource(fuel, 0, 0, 0, 255);
        }     
      break;
    case OX_MESSAGE:
    case OX_STAGE_MESSAGE:
        if (msgSize == sizeof(resourceMessage)) {
          resourceMessage ox = parseMessage<resourceMessage>(msg);
          int fuel = calcResourcePercentage(ox.available, ox.total);
          resourceManager.handleResource(fuel, 16, 255, 255, 255);
        }
      break;
    case SF_MESSAGE:
    case SF_STAGE_MESSAGE:
        if (msgSize == sizeof(resourceMessage)) {
          resourceMessage sf = parseMessage<resourceMessage>(msg);
          int fuel = calcResourcePercentage(sf.available, sf.total);
          resourceManager.handleResource(fuel, 32, 255, 165, 0);
        }
      break;
    case XENON_GAS_MESSAGE:
    case XENON_GAS_STAGE_MESSAGE:
        if (msgSize == sizeof(resourceMessage)) {
          resourceMessage fuelMsg = parseMessage<resourceMessage>(msg);
          int fuel = calcResourcePercentage(fuelMsg.available, fuelMsg.total);
          resourceManager.handleResource(fuel, 48, 148, 0, 211);
        }
      break;
    case MONO_MESSAGE:
        if (msgSize == sizeof(resourceMessage)) {
          resourceMessage fuelMsg = parseMessage<resourceMessage>(msg);
          int fuel = calcResourcePercentage(fuelMsg.available, fuelMsg.total);
          resourceManager.handleResource(fuel, 64, 154, 205, 50);
        }
      break;
  }
}