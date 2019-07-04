#include <Adafruit_Arcada.h>

#define MIN_DELAY 75
#define TARGET_DELAY 150
#define DELAY_INCREMENT 2
#define DELAY_DECREMENT -200

Adafruit_Arcada arcada;

int32_t  responseDelay = MIN_DELAY;

void lightsOn() {
    int32_t timePerLight = (TARGET_DELAY - MIN_DELAY) / ARCADA_NEOPIXEL_NUM;
    int32_t delayOverMin = responseDelay - MIN_DELAY;
    int32_t numLights = (delayOverMin / timePerLight) +1;
    uint32_t color = responseDelay <= TARGET_DELAY ? 0x804040 : 0x00ff00;
    arcada.pixels.fill(color, 0,  numLights);
    arcada.pixels.show();
    
}

void lightsOff() {
    arcada.pixels.fill();
    arcada.pixels.show();
}


void processButton(uint8_t buttonmask, int32_t timeChange) {
  if (buttonmask & arcada.readButtons()) {
    responseDelay += timeChange;
    if (responseDelay < MIN_DELAY) responseDelay = MIN_DELAY;
    if (responseDelay > 0) delay(responseDelay);
    lightsOn();
    do {
      delay(50);
    } while (buttonmask & arcada.readButtons());
    lightsOff();
  }
}

void setup() {
  //while (!Serial);

  Serial.println("Hello! Hand-eye delay demonstration");
  if (!arcada.begin()) {
    Serial.print("Failed to begin");
    while (1);
  }
  arcada.displayBegin();
  Serial.println("Arcada display begin");

  for (int i=0; i<250; i++) {
    arcada.setBacklight(i);
    delay(1);
  }
  arcada.fillScreen(ARCADA_DARKGREY);
  delay(50);

  arcada.setCursor(0, 0);
  arcada.setTextWrap(true);
}

void loop() {
  delay(5);

  processButton(ARCADA_BUTTONMASK_SELECT, DELAY_INCREMENT);
  processButton(ARCADA_BUTTONMASK_START, DELAY_DECREMENT);

}
