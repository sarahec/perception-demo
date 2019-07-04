#include <Adafruit_Arcada.h>
// #include <Adafruit_QSPI.h>
// #include <Adafruit_QSPI_Flash.h>
// #include <Adafruit_SPIFlash.h>

Adafruit_Arcada arcada;

uint32_t buttons, last_buttons;
uint32_t response_delay = 0;

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

  buttons = last_buttons = 0;

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

  uint8_t pressed_buttons = arcada.readButtons();
  
  // if (pressed_buttons & ARCADA_BUTTONMASK_A) {
  //   Serial.print("A");
  //   // arcada.drawCircle(145, 100, 10, ARCADA_WHITE);
  // }
  // if (pressed_buttons & ARCADA_BUTTONMASK_B) {
  //   Serial.print("B");
  //   // arcada.drawCircle(120, 100, 10, ARCADA_WHITE);
  // }
  if (pressed_buttons & ARCADA_BUTTONMASK_SELECT) {
    delay(response_delay);
    arcada.pixels.setPixelColor(0, 0x00ffff);
    arcada.pixels.show();
    delay(50);
    arcada.pixels.setPixelColor(0, 0);
    arcada.pixels.show();
    response_delay += 5;
    delay(50);
    // arcada.drawRoundRect(60, 100, 20, 10, 5, ARCADA_WHITE);
  }
  if (pressed_buttons & ARCADA_BUTTONMASK_START) {
    response_delay = response_delay > 25 ? response_delay - 25 : 0;
    delay(response_delay);
    arcada.pixels.setPixelColor(0, 0x00ffff);
    arcada.pixels.show();
    delay(50);
    arcada.pixels.setPixelColor(0, 0);
    arcada.pixels.show();
    delay(50);
  }

  Serial.println();

  last_buttons = buttons;
}
