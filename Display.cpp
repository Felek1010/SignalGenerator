#include "Display.h"

// Konstruktor, initialisiert das Display mit den richtigen Pins
Display::Display() 
    : u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE, /* clock=*/SCL, /* data=*/SDA) // Display-Objekt initialisieren
{
}

// Initialisierungsmethode
void Display::init()
{
    u8g2.begin();  // Display initialisieren
}

// Methode zum Schreiben von Text auf das Display
void Display::write(const char* text, int x, int y)
{
    u8g2.setFont(u8g2_font_ncenB10_tr);   // Schriftart setzen
    u8g2.clearBuffer();                    // Puffer löschen
    u8g2.drawStr(x, y, text);             // Text zeichnen
    u8g2.sendBuffer();                     // Puffer an Display senden
}

void Display::updateDisplay(float frequenz, float amplitude)
{
    String message = "Frequenz: " + String(frequenz) + "Hz";
    String message2 = "Amplitude: " + String(amplitude + "mV");

    u8g2.setFont(u8g2_font_ncenB10_tr);   // Schriftart setzen
    u8g2.clearBuffer();                    // Puffer löschen
    u8g2.drawXBMP(52, 0, 24, 24, epd_bitmap_wave_square);
    u8g2.drawStr(0, 40, message.c_str()); 
    u8g2.drawStr(0, 60, message2.c_str());
    u8g2.sendBuffer();   
}
