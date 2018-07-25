#include <ArduinoJson.h>
#include <cstdlib>
#include <rBase64.h>

void ShowEntries(char *filename, int intStartWith , int MaxCount){
    String SCC = sd_getfilecontent(filename);
//    const uint8_t *f = u8g2_font_courB24_tf;
    const uint8_t *f = u8g2_font_fub42_tf;
    const int16_t yOS = 50;
    const int16_t LeftSetOff = 20;

    display.setRotation(0);
    display.fillScreen(GxEPD_WHITE);
    u8g2_for_adafruit_gfx.setFontMode(1);                   // use u8g2 transparent mode (this is default)
    u8g2_for_adafruit_gfx.setFontDirection(0);              // left to right (this is default)
    u8g2_for_adafruit_gfx.setForegroundColor(GxEPD_BLACK);  // apply Adafruit GFX color
    u8g2_for_adafruit_gfx.setBackgroundColor(GxEPD_WHITE);  // apply Adafruit GFX color
    u8g2_for_adafruit_gfx.setFont(f); // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall

    //u8g2_for_adafruit_gfx.println("Umlaut ÄÖÜäéöü");
  
    int16_t EffTopOffSet = 0;
    int Mcount = 0;
    int retCount = 0;
    int OSC = 0;
//    StaticJsonBuffer<1024> jsonBuffer;
    DynamicJsonBuffer jsonBuffer;
    //Serial.println(SCC);
    JsonArray& arr = jsonBuffer.parseArray(SCC);

        for (JsonArray::iterator it=arr.begin(); it!=arr.end(); ++it)
        {
            //Serial.println("Eintrag " + (String)count);
            if (Mcount >= intStartWith){
                if(retCount < MaxCount){
                    OSC++;
                    //Serial.println("LoopOutput") ;
                    String SID = (*it)["id"];
                    String PName = (*it)["name"];
                    if (rbase64.decode(PName) == RBASE64_STATUS_OK ) {
                        //Serial.println("\nConverted the String from Base64 : ");
                        //Serial.println(rbase64.result());
                        PName  = rbase64.result();
                    }  


                    String PDone = (*it)["done"];
                    Serial.println("Eintrag " + (String)Mcount);
                    Serial.println(PName);
                    Serial.println(SID +  "  " + PDone);
                    Serial.println("---------------------------------");
                    EffTopOffSet = (int16_t)OSC * yOS;
                    u8g2_for_adafruit_gfx.setCursor(LeftSetOff, EffTopOffSet);
                    u8g2_for_adafruit_gfx.print(PName);
                    retCount++;
                }
            }
            Mcount++;
        }
    display.update();
        
Serial.println("Count:" + (String)Mcount);
Serial.println("RetCount:" + (String)retCount);
}