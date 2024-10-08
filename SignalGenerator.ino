#include <AD9833.h>
#include <Rotary.h>
#include <Wire.h>
#include <SPI.h>
#include "Display.h"

// Rotary Encoder Pin Setup
#define SW_PIN D3   // Switch Pin
#define DT_PIN D6   // Data Pin
#define CLK_PIN D1  // Clock Pin

// AD9833 Pin Setup
#define FSYNC_PIN D4
#define MOSI_PIN D7
#define SCLK_PIN D5

// Display Pin Setup
#define SDA D2
#define SCL D1

// Setup instances
AD9833 ad(FSYNC_PIN, MOSI_PIN, SCLK_PIN);
Rotary encoder(CLK_PIN, DT_PIN);
Display display;

// Volatile variables for ISR
volatile bool buttonPressed = false;

void ICACHE_RAM_ATTR isrSwitchChange() {
    buttonPressed = true;
}

void setup() {
    Serial.begin(115200);
    Serial.println("BOOT-SETUP SignalGenerator");

    display.init();

    pinMode(SW_PIN, INPUT_PULLUP);

    // Initialize AD9833
    ad.begin();
    ad.setFrequency(1000000);
    ad.setWave(AD9833_TRIANGLE);

    // Setup interrupt for switch button
    attachInterrupt(digitalPinToInterrupt(SW_PIN), isrSwitchChange, FALLING);  // button isr
}

unsigned long lastDebounceTime = 0;  // Entprellzeit
const unsigned long debounceDelay = 100;

int cnt = 0;

void loop() {

    if (buttonPressed) {
        unsigned long currentTime = millis();
        if ((currentTime - lastDebounceTime) > debounceDelay) {
            Serial.println("Button Pressed!");

            static bool toggle = false;
            if (toggle) {
              cnt++;
                  display.updateDisplay(cnt, 0.5);
            } else {
                
            }
            toggle = !toggle;

            lastDebounceTime = currentTime;  // Update debounce time
        }
        buttonPressed = false;  // Reset flag after handling
    }
}
