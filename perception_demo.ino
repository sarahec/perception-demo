#include <Adafruit_Arcada.h>

#define MIN_DELAY 5
#define START_DELAY 75
#define TARGET_DELAY 175
#define DELAY_INCREMENT 2
#define DELAY_DECREMENT -200

enum Screen
{
  startup,
  reset,
  intro,
  increase,
  maxdelay,
  decrease
};

Adafruit_Arcada arcada;

int32_t  responseDelay = START_DELAY;
Screen currentScreen = startup;

void lightsOn() {
    int32_t timePerLight = (TARGET_DELAY - START_DELAY) / ARCADA_NEOPIXEL_NUM;
    int32_t delayOverMin = (responseDelay >= START_DELAY) ? responseDelay - START_DELAY : 0;
    int32_t numLights = (delayOverMin / timePerLight) +1;
    uint32_t color = responseDelay < TARGET_DELAY ? 0x804040 : 0x00ff00;
    arcada.pixels.fill(color, 0,  numLights);
    arcada.pixels.show();
}

void lightsOff() {
    arcada.pixels.fill();
    arcada.pixels.show();
}


bool processButton(uint8_t buttonmask, int32_t timeChange) {
  if (!(buttonmask & arcada.readButtons()))
    return false;
  // We have the button
  responseDelay += timeChange;
  if (responseDelay > TARGET_DELAY)
      responseDelay = TARGET_DELAY;
  if (responseDelay < MIN_DELAY)
    responseDelay = MIN_DELAY;
  if (responseDelay > 0) 
  delay(responseDelay);
  lightsOn();
  do {
    delay(50);
  } while (buttonmask & arcada.readButtons());
  lightsOff();
  return true;
}

void animateLights() {
  int i;
  int ms = 50;

  for (i = 1; i < ARCADA_NEOPIXEL_NUM; i++)
  {
    delay(ms);
    arcada.pixels.fill(0xCCCCCC, 0, i);
    arcada.pixels.show();
  }
  for (i = ARCADA_NEOPIXEL_NUM-1; i > 0; i--) {
    delay(ms);
    arcada.pixels.fill();
    arcada.pixels.fill(0xCCCCCC, 0, i);
    arcada.pixels.show();
  }
  delay(ms);
  arcada.pixels.fill();
  arcada.pixels.show();
}

void showScreen(Screen screen) {
  if (screen == currentScreen)
    return;

  currentScreen = screen;
  
  // erase and reset
  arcada.fillScreen(ARCADA_BLACK);
  arcada.setCursor(0, 0);
  arcada.setTextWrap(true);
  
  switch (screen)
  {
  case reset:
    arcada.println("Resetting...");
    responseDelay = START_DELAY;
    animateLights();
    showScreen(intro);
    break;

  case intro:
    arcada.println("100ms perception demo");
    arcada.println();
    arcada.println("Press the yellow button to");
    arcada.println("light a LED.");
    arcada.println();
    arcada.println("Each press will have a");
    arcada.print("+");
    arcada.print(DELAY_INCREMENT);
    arcada.println("ms longer delay before");
    arcada.println("turning on the light.");
    arcada.println();
    arcada.println("Try it now");
    break;

  case increase:
    arcada.println("Keep pressing repeatedly");
    arcada.println("until the bar fills in.");
    arcada.println();
    arcada.println("Stop when the lights turn");
    arcada.println();
    arcada.println("Make sure to watch the");
    arcada.println("lights as you do this.");
    break;

  case maxdelay:
    arcada.println("Now pause for a moment.");
    arcada.println();
    arcada.print("The delay is ");
    arcada.print(TARGET_DELAY);
    arcada.print("ms.");
    arcada.println();
    arcada.println("When you're ready, we'll");
    arcada.println("take away the delay");
    arcada.println();
    arcada.println("Watch the lights and");
    arcada.println("quickly tap the grey");
    arcada.println("button.");
    break;

  case decrease:
    arcada.println("Did you see it?");
    arcada.println();
    arcada.println("It may look like the");
    arcada.println("light went off before");
    arcada.println("you lifted your finger.");
    arcada.println();
    arcada.println("How many tries before");
    arcada.println("the effect stops?");
    arcada.println();
    arcada.println("When done, press the red");
    arcada.println("button to reset");
    break;
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

  arcada.fillScreen(ARCADA_LIGHTGREY);
  for (int i=0; i<250; i++) {
    arcada.setBacklight(i);
    delay(1);
  }

  delay(10);

  showScreen(reset);
}

void loop() {
  delay(5);

  if (arcada.readButtons() & ARCADA_BUTTONMASK_A)
  {
    showScreen(reset);
  }

  // Run the up button as many times as needed
  if (processButton(ARCADA_BUTTONMASK_SELECT, DELAY_INCREMENT) & currentScreen < maxdelay)
  {
    if (responseDelay < TARGET_DELAY)
    {
      showScreen(increase);
    } else {
      showScreen(maxdelay);
    }
  }


  // Run the down button as many times as needed
  if (processButton(ARCADA_BUTTONMASK_START, DELAY_DECREMENT) & currentScreen >= maxdelay) 
  {
    showScreen(decrease);
  }
}
