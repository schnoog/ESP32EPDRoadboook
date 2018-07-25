#include <ArduinoJson.h>
#include <cstdlib>
#include <rBase64.h>
#include "include_BITMAPS.h"


String IconDown = "\u004F";
String IconLeft = "\u0050";
String IconRight = "\u0051";
String IconUp   = "\u0052";
String IconOK  = "\u0078";
String IconNOK  = "\u0079";
String IconDetails = "\u00CF";






void ShowEntries(char *filename, int intStartWith , int MaxCount){
    String SCC = sd_getfilecontent(filename);
//    const uint8_t *f = u8g2_font_courB24_tf;
    const uint8_t *f = u8g2_font_fub35_tf;
    const uint8_t *sf = u8g2_font_u8glib_4_tf;
    const uint8_t *iconFont = u8g2_font_open_iconic_all_4x_t;
    const int16_t IconSize = 34;

    String strWork;
    const int16_t yOS = 37; //Single Line OffSet
    const int16_t ItemOffSet = 90;
    const int16_t LeftSetOff = 50;
    const int MaxCharsPerLine = 13;
    const int16_t LineSubOffSet = 10;
    int intStringLength = 0;
    int16_t EffTopOffSet = 0;
    int Mcount = 0;
    int retCount = 0;
    int OSC = 0;
    int MOS = 0;
    int16_t SectionEnd = 0;
    int16_t SectionStart = 0;
    int16_t LineSpace = 5;
    display.setRotation(0);
    display.fillScreen(GxEPD_WHITE);
    u8g2_for_adafruit_gfx.setFontMode(1);                   // use u8g2 transparent mode (this is default)
    u8g2_for_adafruit_gfx.setFontDirection(0);              // left to right (this is default)
    u8g2_for_adafruit_gfx.setForegroundColor(GxEPD_BLACK);  // apply Adafruit GFX color
    u8g2_for_adafruit_gfx.setBackgroundColor(GxEPD_WHITE);  // apply Adafruit GFX color
    u8g2_for_adafruit_gfx.setFont(f); // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall


    DynamicJsonBuffer jsonBuffer;
    JsonArray& arr = jsonBuffer.parseArray(SCC);

        for (JsonArray::iterator it=arr.begin(); it!=arr.end(); ++it)
        {
            if (Mcount >= intStartWith){
                if(retCount < MaxCount){
                    String SID = (*it)["id"];
                    String PName = (*it)["name"];
                    if (rbase64.decode(PName) == RBASE64_STATUS_OK ) {
                        PName  = rbase64.result();
                    }  


                    String PDone = (*it)["done"];
                    Serial.println("Eintrag " + (String)Mcount);
                    Serial.println(PName);
                    Serial.println(SID +  "  " + PDone + "  " + PName);
                    String DetFile = "details/" + SID + ".bmp";
                    Serial.println("---------------------------------");

                    intStringLength = PName.length();
                    MOS=0;
                    SectionEnd = (1 + retCount) * ItemOffSet;
                    SectionStart = retCount * ItemOffSet;
                    Serial.println("Section End of Section " + (String)retCount + " at " + (String)SectionEnd);

                    u8g2_for_adafruit_gfx.setFont(sf);
                    u8g2_for_adafruit_gfx.setCursor(0,(SectionEnd + 2));
                    u8g2_for_adafruit_gfx.print("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
                    for (int16_t Scount = SectionStart; Scount < SectionEnd; Scount = Scount + 4 ){
                          u8g2_for_adafruit_gfx.setCursor(LeftSetOff - 4,Scount);
                          u8g2_for_adafruit_gfx.print("X");  
                    }
                    u8g2_for_adafruit_gfx.setFont(iconFont);
                    int16_t ButOffSet = 0;
                    ButOffSet = SectionStart;
                    ButOffSet = ButOffSet + IconSize;
                    if (SD.exists(string2char(DetFile))){
                     
                        u8g2_for_adafruit_gfx.setCursor(4,ButOffSet);
                        u8g2_for_adafruit_gfx.print(IconDetails);
                        
                    }
                    ButOffSet = ButOffSet + IconSize;
                    u8g2_for_adafruit_gfx.setCursor(4,ButOffSet);
                    u8g2_for_adafruit_gfx.print(IconOK);
                    u8g2_for_adafruit_gfx.setFont(f);





                    if(intStringLength >  MaxCharsPerLine){
                        while((MOS * MaxCharsPerLine) < intStringLength){
                            strWork = PName.substring(MOS * MaxCharsPerLine,MOS * MaxCharsPerLine + MaxCharsPerLine);    
                            EffTopOffSet = SectionStart + (yOS * (1 + (int16_t)MOS));
                            EffTopOffSet = EffTopOffSet  + LineSpace;
                         //   EffTopOffSet = EffTopOffSet + (MOS * LineSubOffSet);
                        //    EffTopOffSet = EffTopOffSet + (LineSubOffSet * (retCount + 1));
                        Serial.println("Printing multi Line " + strWork + " at " + (String)EffTopOffSet);
                            u8g2_for_adafruit_gfx.setCursor(LeftSetOff, EffTopOffSet);
                            u8g2_for_adafruit_gfx.print(strWork);
                            MOS++;
                        }

                    }else{
//                        EffTopOffSet = SectionEnd - (ItemOffSet / (int16_t)2);
//                        EffTopOffSet = EffTopOffSet + (yOS / 2);
                        EffTopOffSet = SectionStart + (yOS / 2) + yOS + LineSubOffSet;
                        Serial.println("Printing single Line " + PName + " at " + (String)EffTopOffSet);
                        u8g2_for_adafruit_gfx.setCursor(LeftSetOff, EffTopOffSet);
                        u8g2_for_adafruit_gfx.print(PName);                        
                    }


                Serial.println("-----RAM-----");
                Serial.println(ESP.getFreeHeap());
                Serial.println("-----RAM-----");










                    retCount++;


                }
            }
            Mcount++;
        }




    display.update();
        
Serial.println("Count:" + (String)Mcount);
Serial.println("RetCount:" + (String)retCount);
}