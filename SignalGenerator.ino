#include <AD9833.h>
#include <Rotary.h>
#include <Wire.h>
#include <SPI.h>
#include <U8g2lib.h>

//rotary pin setup
#define SW_PIN D3 // switch?
#define DT_PIN D6
#define CLK_PIN D1

//ad9833 pin setup
#define FSYNC_PIN D4
#define MOSI_PIN D7
#define SCLK_PIN D5

//display pin setup
#define SDA D2
#define SCL D1

//setup instances
AD9833 ad(FSYNC_PIN, MOSI_PIN, SCLK_PIN);
Rotary encoder(CLK_PIN, DT_PIN);
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE, /* clock=*/SCL, /* data=*/SDA);

void setup() {
  Serial.begin(115200);
  Serial.println("BOOT-SETUP SignalGenerator");

  u8g2.begin();

  //pin setup
  pinMode(SW_PIN, INPUT_PULLUP);

 ad.begin();
ad.setFrequency(1000000);
  ad.setWave(AD9833_TRIANGLE);
}

void loop() {
    u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(0,20,"Hello World!");
  } while ( u8g2.nextPage() );
  delay(1000);
}
