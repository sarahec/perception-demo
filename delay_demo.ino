#include <Adafruit_Arcada.h>
// #include <Adafruit_QSPI.h>
// #include <Adafruit_QSPI_Flash.h>
// #include <Adafruit_SPIFlash.h>

Adafruit_Arcada arcada;

int32_t  response_delay = 0;

// // Check the timer callback, this function is called every millisecond!
// volatile uint16_t milliseconds = 0;
// void timercallback() {
//   // analogWrite(13, milliseconds);  // pulse the LED
//   if (milliseconds == 0) {
//     milliseconds = 255;
//   } else {
//     milliseconds--;
//   }
// }

void lightsOn() {
    arcada.pixels.setPixelColor(0, 0x00ffff);
    arcada.pixels.show();
    
}

void lightsOff() {
    arcada.pixels.setPixelColor(0, 0);
    arcada.pixels.show();
}


void processButton(uint8_t buttonmask, int32_t timeChange) {
  if (buttonmask & arcada.readButtons()) {
    response_delay += timeChange;
    if (response_delay < 0) response_delay = 0;
    delay(response_delay);
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

  // arcada.timerCallback(1000, timercallback);
}

void loop() {
  delay(5);
  // if (playsound) {
  //   arcada.enableSpeaker(true);
  //   play_tune(audio, sizeof(audio));
  //   arcada.enableSpeaker(false);
  // }
    
 
  // Read battery
  // arcada.setCursor(80, 50);
  // arcada.setTextColor(ARCADA_WHITE);
  // float vbat = arcada.readBatterySensor();
  // Serial.print("Battery: "); Serial.print(vbat); Serial.println("V");
  // arcada.print("Batt: "); arcada.print(vbat); arcada.println("V");

  // Serial.printf("Drawing %d NeoPixels", arcada.pixels.numPixels());  
  // for(int32_t i=0; i< arcada.pixels.numPixels(); i++) {
  //    arcada.pixels.setPixelColor(i, Wheel(((i * 256 / arcada.pixels.numPixels()) + j*5) & 255));
  // }
  // arcada.pixels.show();

  
  // if (pressed_buttons & ARCADA_BUTTONMASK_A) {
  //   Serial.print("A");
  //   // arcada.drawCircle(145, 100, 10, ARCADA_WHITE);
  // }
  // if (pressed_buttons & ARCADA_BUTTONMASK_B) {
  //   Serial.print("B");
  //   // arcada.drawCircle(120, 100, 10, ARCADA_WHITE);
  // }
  processButton(ARCADA_BUTTONMASK_SELECT, 5);
  processButton(ARCADA_BUTTONMASK_START, -75);

}
