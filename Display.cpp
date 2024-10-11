
#include "Display.h"

Display::Display() 
    : u8g2(U8G2_R0, U8X8_PIN_NONE, SCL, SDA) 
{
}

void Display::init() {
    u8g2.begin();
}

void Display::updateDisplay(float frequenz, float amplitude, SignalForm waveform) {
    String freqText = "Freq: " + String(frequenz) + "Hz";
    String ampText = "Amp: " + String(amplitude) + "V";

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    // waveform icon
    switch (waveform) {
        case SINE:
            u8g2.drawXBMP(52, 0, 24, 24, epd_bitmap_wave_sine);
            currentSignal = SINE;
            break;
        case TRIANGLE:
            u8g2.drawXBMP(52, 0, 24, 24, epd_bitmap_wave_triangle);
            currentSignal = TRIANGLE;
            break;
        case SQUARE:
            u8g2.drawXBMP(52, 0, 24, 24, epd_bitmap_wave_square);
            currentSignal = SQUARE;
            break;
    }
    u8g2.drawStr(0, 40, freqText.c_str());
    u8g2.drawStr(0, 60, ampText.c_str());
    u8g2.sendBuffer();
}

void Display::setCursor(SelectedItem item)
{
    // delete old cursor
    u8g2.setDrawColor(0);
    switch(lastItem) {
        case SIGNAL:
            u8g2.drawFrame(-1, 0, 130, 24);
            break;
        case FREQUENCY:
            u8g2.drawFrame(-1, 26, 130, 18);
            break;
        case AMPLITUDE:
            u8g2.drawFrame(-1, 46, 130, 18);
            break;
    }
    // add new cursor
    u8g2.setDrawColor(1);
    switch(item) {
        case SIGNAL:
            u8g2.drawFrame(-1, 0, 130, 24); // Halfframe
            break;
        case FREQUENCY:
            u8g2.drawFrame(-1, 26, 130, 18); // Frequenz
            break;
        case AMPLITUDE:
            u8g2.drawFrame(-1, 46, 130, 18); // Amplitude
            break;
    }
    currentItem = item;
    lastItem = item;
    u8g2.sendBuffer();
}

//getter 'n setter
Display::SignalForm Display::getCurrentSignal() const 
{
  return currentSignal;
}

Display::SelectedItem Display::getCurrentItem() const 
{
  return currentItem;
}
