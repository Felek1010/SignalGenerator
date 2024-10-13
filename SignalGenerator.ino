#include <AD9833.h>
#include <Wire.h>
#include <AiEsp32RotaryEncoder.h>
#include "Display.h"
//du Hurensohn!!
// Rotary Encoder Setup
#define SW_PIN D3   // Button Pin
#define DT_PIN D5   // Data Pin
#define CLK_PIN D6  // Clock Pin
#define ROTARY_ENCODER_STEPS 4
#define VCC_PIN -1  // -1 weil Vcc direkt an 3,3V ist!
bool circleValues = false;
const int maxValueEncoder = 2;  // 3 Menue Items

// AD9833 Pin Setup
#define FSYNC_PIN D4
#define MOSI_PIN D7
#define SCLK_PIN D0

// Setup instances
AD9833 ad(FSYNC_PIN, MOSI_PIN, SCLK_PIN);
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(CLK_PIN, DT_PIN, SW_PIN, VCC_PIN, ROTARY_ENCODER_STEPS);
Display display;

void IRAM_ATTR readEncoderISR();

bool inSubMenu = false;

void setup()
{
  Serial.begin(115200);
  Serial.println("++++++++++BOOT-Setup SignalGenerator++++++++++++");

  ad.begin();
  display.init();
  display.updateDisplay(0.0, 0.0, Display::SINE);  //std screen for booting

  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  rotaryEncoder.setBoundaries(0, maxValueEncoder, circleValues);
  //rotaryEncoder.setAcceleration(250);
  display.setCursor(Display::SIGNAL);
}


void loop()
{
  rotaryEncoder.setBoundaries(0, maxValueEncoder, circleValues);
  if (rotaryEncoder.encoderChanged())
  {
    Serial.println("encoderChange");
    Serial.println(display.getCurrentItem());
    switch (rotaryEncoder.readEncoder())
    {
      case 0:
        display.setCursor(Display::SIGNAL);
        break;
      case 1:
        display.setCursor(Display::FREQUENCY);
        break;
      case 2:
        display.setCursor(Display::AMPLITUDE);
        break;
    }
  }
  //buttonklick ->ins untermenu gehen
  if (rotaryEncoder.isEncoderButtonClicked())
  {
    static unsigned long lastTimePressed = 0;
    if (millis() - lastTimePressed < 50)
      return;
    lastTimePressed = millis();
    switch (display.getCurrentItem())
    {
      case Display::SIGNAL:
        Serial.println("Untermenu Signal");
        //todo: signal wechseln (bool für untermenu verwenden oder so)
        break;
      case Display::FREQUENCY:
        changeFrequency();
        Serial.println("Untermenu Frequenz verlassen");
        //todo: frequenz einstellen und ändern
        break;
      case Display::AMPLITUDE:
        Serial.println("Untermenu Amplitude");
        //todo: amplitude einstellen und ändern
        break;
    }
  }
}

//submenu routines
void changeFrequency()
{
  inSubMenu = true;
  rotaryEncoder.setAcceleration(500);
  rotaryEncoder.setBoundaries(0, 10000000, false);
  static unsigned long lastTimeButtonDown = 0;
  static bool wasButtonDown = false;
  const unsigned long longPressAfterMilliseconds = 1000;
  while (inSubMenu)
  {
    if (rotaryEncoder.encoderChanged())
    {
      int val = rotaryEncoder.readEncoder();
      ad.setFrequency(val);
      Serial.println(val);
    }
    bool isEncoderButtonDown = rotaryEncoder.isEncoderButtonDown();
    if (isEncoderButtonDown)
    {
      if (!wasButtonDown)
      {
        lastTimeButtonDown = millis();
      }
      wasButtonDown = true;
    }
    else if (wasButtonDown)
    {
      wasButtonDown = false;
      if (millis() - lastTimeButtonDown >= longPressAfterMilliseconds)
      {
        Serial.println("leaving submenu");
        inSubMenu = false;
      }
    }
    delay(10);
  }
}


//Interrupt Service Routines
void IRAM_ATTR readEncoderISR()
{
  rotaryEncoder.readEncoder_ISR();
}
