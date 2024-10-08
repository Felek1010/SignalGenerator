#ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>
#include <Wire.h>
#include "Icons.h"

class Display {
  private:
    U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2;

  public:
    Display();
    void init();

    enum SignalForm
    {
      SINE,
      TRIANGLE,
      SQUARE
    };

    void write(const char* text, int x, int y);
    void updateDisplay(float frequenz, float amplitude);


};

#endif
