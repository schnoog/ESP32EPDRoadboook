//#Native SPI pins are (clk, mosi, miso, cs):
//#VSPI: 18,23,19, 5   <-- sdc
//#HSPI: 14,13,12,15
//#SPI1: 6, 8, 7, 11

//sck = Pin(14)
//miso = Pin(12)
//mosi = Pin(13)
//cs = Pin(15)
//dc = Pin(27)
//rst = Pin(33)
//busy = Pin(21)
#define PIN_SPI_SS    (15)
#define PIN_SPI_MOSI  (13)
#define PIN_SPI_MISO  (12)
#define PIN_SPI_SCK   (14)
// static const uint8_t SCK   = 14;
#include <GxEPD.h>
#include <U8g2_for_Adafruit_GFX.h>
// select the display class to use, only one
//#include <GxGDEP015OC1/GxGDEP015OC1.cpp>    // 1.54" b/w
//#include <GxGDEW0154Z04/GxGDEW0154Z04.cpp>  // 1.54" b/w/r
//#include <GxGDE0213B1/GxGDE0213B1.cpp>      // 2.13" b/w
//#include <GxGDEW0213Z16/GxGDEW0213Z16.cpp>  // 2.13" b/w/r
//#include <GxGDEH029A1/GxGDEH029A1.cpp>      // 2.9" b/w
//#include <GxGDEW029Z10/GxGDEW029Z10.cpp>    // 2.9" b/w/r
//#include <GxGDEW027C44/GxGDEW027C44.cpp>    // 2.7" b/w/r
//#include <GxGDEW027W3/GxGDEW027W3.cpp>      // 2.7" b/w
#include <GxGDEW042T2/GxGDEW042T2.cpp>      // 4.2" b/w
//#include <GxGDEW042Z15/GxGDEW042Z15.cpp>    // 4.2" b/w/r
//#include <GxGDEW0583T7/GxGDEW0583T7.cpp>    // 5.83" b/w
//#include <GxGDEW075T8/GxGDEW075T8.cpp>      // 7.5" b/w
//#include <GxGDEW075Z09/GxGDEW075Z09.cpp>    // 7.5" b/w/r

// FreeFonts from Adafruit_GFX

#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
//#include <Fonts/u8g2_font_helvR14_tf.h>
//#include <Fonts/u8g2_font_profont22_mr.h>
//#include <Fonts/Open_Sans_Bold_12pt.h>


#include <GxIO/GxIO_SPI/GxIO_SPI.cpp>
#include <GxIO/GxIO.cpp>

//sck = Pin(14)
//miso = Pin(12)
//mosi = Pin(13)
//cs = Pin(15)
//dc = Pin(27)
//rst = Pin(33)
//busy = Pin(21)
GxIO_Class io(SPI, /*CS=5*/ 15, /*DC=*/ 27, /*RST=*/ 33); // arbitrary selection of 17, 16
GxEPD_Class display(io, /*RST=*/ 33, /*BUSY=*/ 21); // arbitrary selection of (16), 4
U8G2_FOR_ADAFRUIT_GFX u8g2_for_adafruit_gfx;


void init_EPD(){
    //Serial.println("setup");
    //display.init(115200); // enable diagnostic output on Serial
    display.init();
    u8g2_for_adafruit_gfx.begin(display);
    //Serial.println("setup done");
}

void showFont(const char name[], const uint8_t *f)
{
  display.setRotation(0);
  display.fillScreen(GxEPD_WHITE);
  u8g2_for_adafruit_gfx.setFontMode(1);                   // use u8g2 transparent mode (this is default)
  u8g2_for_adafruit_gfx.setFontDirection(0);              // left to right (this is default)
  u8g2_for_adafruit_gfx.setForegroundColor(GxEPD_BLACK);  // apply Adafruit GFX color
  u8g2_for_adafruit_gfx.setBackgroundColor(GxEPD_WHITE);  // apply Adafruit GFX color
  u8g2_for_adafruit_gfx.setFont(f); // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
  u8g2_for_adafruit_gfx.setCursor(0, 0);
  u8g2_for_adafruit_gfx.println();
  u8g2_for_adafruit_gfx.println(name);
  u8g2_for_adafruit_gfx.println(" !\"#$%&'()*+,-./");
  u8g2_for_adafruit_gfx.println("0123456789:;<=>?");
  u8g2_for_adafruit_gfx.println("@ABCDEFGHIJKLMNO");
  u8g2_for_adafruit_gfx.println("PQRSTUVWXYZ[\\]^_");
  u8g2_for_adafruit_gfx.println("`abcdefghijklmno");
  u8g2_for_adafruit_gfx.println("pqrstuvwxyz{|}~ ");
  u8g2_for_adafruit_gfx.println("Umlaut ÄÖÜäéöü");
  display.update();
}

void showIt(){
   // Serial.println("Call");
    showFont("u8g2_font_helvR14_tf", u8g2_font_helvR14_tf); // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
    delay(5000);
    showFont("u8g2_font_courB24_tf", u8g2_font_courB24_tf); // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
    delay(5000);
}