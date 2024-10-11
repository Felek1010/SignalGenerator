#ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>
#include <Wire.h>
#include "Icons.h"

class Display
{
  public:
    Display();

    enum SignalForm{SINE, TRIANGLE, SQUARE};
    enum SelectedItem{FREQUENCY, SIGNAL, AMPLITUDE};

    void init();
    void setCursor(SelectedItem item);
    void updateDisplay(float frequenz, float amplitude, SignalForm waveform);
    SignalForm getCurrentSignal() const;
    SelectedItem getCurrentItem() const;
  private:
    U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2;
    SignalForm currentSignal;
    SelectedItem currentItem;
    SelectedItem lastItem;

};

#endif
