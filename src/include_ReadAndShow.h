#include <ArduinoJson.h>
#include <cstdlib>
#include <rBase64.h>
#include "include_BITMAPS.h"


String IconDown = "\u0049"; // OK
String IconLeft = "\u004A"; // OK
String IconRight = "\u004B";// OK
String IconUp   = "\u004C"; //OK
String IconOK  = "\u0078"; //OK
String IconNOK  = "\u0079";  //OK
String IconDetails = "\u00CF"; //OK
String IconAntenna = "\u00f7"; //OK
String IconAntennaConnected = "\u00f8"; //OK
String IconSys = "\u0081";  //OK
String IconCase = "\u0064"; //--->Koffer
String IconTool = "\u011a"; //
String IconPower = "\u00AA"; //OK
String IconForward = "\u0042"; //OK
String IconBack = "\u0043"; //OK
String IconLocked = "\u00ca"; //Schloss zu
String IconUnlocked = "\u00cb"; // Schloss offen
String IconHome = "\u00b8"; //Haus
String IconEdit = "\u00e3"; //Stift
String IconList = "\u00c7"; //Liste
String IconSleep = "\u00df"; //Moon


void ShowEntries(char *filename, int intStartWith , int MaxCount){
        ButtonData[0].BComment = string2char("L_Top1");
        ButtonData[1].BComment = string2char("L_Top2");
        ButtonData[2].BComment = string2char("L_Top3");
        ButtonData[3].BComment = string2char("L_Top4");
        ButtonData[4].BComment = string2char("L_Top5");
        ButtonData[5].BComment = string2char("L_Top6");

        ButtonData[6].BComment = string2char("B_Left1");
        ButtonData[7].BComment = string2char("B_Left2");
        ButtonData[8].BComment = string2char("B_Left3");
        ButtonData[9].BComment = string2char("B_Left4");
        ButtonData[10].BComment = string2char("B_Left5");


    String SCC = sd_getfilecontent(filename);
//    const uint8_t *f = u8g2_font_courB24_tf;
    const uint8_t *f = u8g2_font_fub35_tf;
    const uint8_t *sf = u8g2_font_u8glib_4_tf;
    const uint8_t *iconFont = u8g2_font_open_iconic_all_4x_t;
    const uint8_t *ButtonIconFront = u8g2_font_open_iconic_all_2x_t;
    const int16_t IconSize = 34;
    const int16_t displayheight = 300;

    String strWork;
    const int16_t yOS = 37; //Single Line OffSet
    const int16_t ItemOffSet = 90;
    const int16_t LeftSetOff = 50;

    const int MaxCharsPerLine = 14;
    const int16_t LineSubOffSet = 10;
    int intStringLength = 0;
    int16_t EffTopOffSet = 0;
    int Mcount = 0;
    int retCount = 0;
    int MOS = 0;
    int16_t SectionEnd = 0;
    int16_t SectionStart = 0;
    int16_t LineSpace = 5;
    int16_t ButtonOffSetY = displayheight - LineSpace;
    int16_t ButtonHorStep = 80;
    int16_t ButtonHorOffSet = 40;
    int SubCount = 0;
    display.setRotation(0);
    display.fillScreen(GxEPD_WHITE);
    u8g2_for_adafruit_gfx.setFontMode(1);                   // use u8g2 transparent mode (this is default)
    u8g2_for_adafruit_gfx.setFontDirection(0);              // left to right (this is default)
    u8g2_for_adafruit_gfx.setForegroundColor(GxEPD_BLACK);  // apply Adafruit GFX color
    u8g2_for_adafruit_gfx.setBackgroundColor(GxEPD_WHITE);  // apply Adafruit GFX color
    u8g2_for_adafruit_gfx.setFont(f); // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
/*
    for (int ii = 0; ii < 18; ii++){
        ButtonData[ii].BFunction = string2char("");
        ButtonData[ii].BValue = string2char("");
    }
*/
    DynamicJsonBuffer jsonBuffer;
    JsonArray& arr = jsonBuffer.parseArray(SCC);

        for (JsonArray::iterator it=arr.begin(); it!=arr.end(); ++it)
        {
            if (Mcount >= intStartWith){
                //Serial.println("Reporting MCount >= intStartWith");
                if(retCount < MaxCount){
                    String SID = (*it)["id"];
                    String PName = (*it)["name"];
                    if (rbase64.decode(PName) == RBASE64_STATUS_OK ) {
                        PName  = rbase64.result();
                    }  


                    String PDone = (*it)["done"];
                  //  Serial.println("Eintrag " + (String)Mcount);
                  //  Serial.println(PName);
                  //  Serial.println(SID +  "  " + PDone + "  " + PName);
                    String DetFile = "details/" + SID + ".bmp";
                  //  Serial.println("---------------------------------");
                    if(PDone.equals((String)"0")){
                                        SubCount++;
                                        intStringLength = PName.length();
                                        MOS=0;
                                        SectionEnd = (1 + retCount) * ItemOffSet;
                                        SectionStart = retCount * ItemOffSet;
                                        u8g2_for_adafruit_gfx.setFont(sf);
                                        u8g2_for_adafruit_gfx.setCursor(0,(SectionEnd + 2));
                                        u8g2_for_adafruit_gfx.print("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
                                        for (int16_t Scount = SectionStart; Scount < SectionEnd; Scount = Scount + 4 ){
                                            u8g2_for_adafruit_gfx.setCursor(LeftSetOff - 4,Scount);
                                            u8g2_for_adafruit_gfx.print("X");  
                                        }
                                        u8g2_for_adafruit_gfx.setFont(iconFont);
                                        int16_t ButOffSet = 0;
                                        ButOffSet = SectionStart + 10 ;
                                        ButOffSet = ButOffSet + IconSize;

                                        ButtonData[SubCount].BFunction = string2char("OpenDetails");
                                        ButtonData[SubCount].BValue = string2char("0");

                                        if (SD.exists(string2char(DetFile))){

                                            ButtonData[SubCount].BValue = string2char(SID);

                                            u8g2_for_adafruit_gfx.setCursor(4,ButOffSet);
                                            u8g2_for_adafruit_gfx.print(IconDetails);
                                        }
                                        SubCount++;
                                        
                                        ButtonData[SubCount].BFunction = string2char("MarkDone");
                                        ButtonData[SubCount].BValue = string2char(SID);                                    

                                        ButOffSet = ButOffSet + IconSize;
                                        u8g2_for_adafruit_gfx.setCursor(4,ButOffSet);
                                        u8g2_for_adafruit_gfx.print(IconOK);
                                        u8g2_for_adafruit_gfx.setFont(f);
                                        if(intStringLength >  MaxCharsPerLine){
                                            while((MOS * MaxCharsPerLine) < intStringLength){
                                                strWork = PName.substring(MOS * MaxCharsPerLine,MOS * MaxCharsPerLine + MaxCharsPerLine);    
                                                EffTopOffSet = SectionStart + (yOS * (1 + (int16_t)MOS));
                                                EffTopOffSet = EffTopOffSet  + LineSpace;
                                                u8g2_for_adafruit_gfx.setCursor(LeftSetOff, EffTopOffSet);
                                                u8g2_for_adafruit_gfx.print(strWork);
                                                MOS++;
                                            }
                                        }else{
                                            EffTopOffSet = SectionStart + (yOS / 2) + yOS + LineSubOffSet;
                                            u8g2_for_adafruit_gfx.setCursor(LeftSetOff, EffTopOffSet);
                                            u8g2_for_adafruit_gfx.print(PName);                        
                                        }
                                        retCount++;
                    }

                }
            }else{
                 //               Serial.println("Skipping  MCount < intStartWith");
            }
            Mcount++;
    //arr.printTo()
        }
/* BUTTONS */
//Button Buttons - 
//Back/Exit - UP - DOWN - SYSTEM - Power (DeepSleep)
        u8g2_for_adafruit_gfx.setFont(ButtonIconFront);

        u8g2_for_adafruit_gfx.setCursor(ButtonHorOffSet,ButtonOffSetY);
        u8g2_for_adafruit_gfx.print(IconDown);
/*
        SubCount++;
        ButtonData[SubCount].BFunction = (String)"MoveForward";
        ButtonData[SubCount].BValue = (String)intStartWith;        
*/

        ButtonHorOffSet = ButtonHorOffSet + ButtonHorStep;
        u8g2_for_adafruit_gfx.setCursor(ButtonHorOffSet,ButtonOffSetY);
        u8g2_for_adafruit_gfx.print(IconUp);
        SubCount++;
/*
        ButtonData[SubCount].BFunction = (String)"MoveBackward";
        ButtonData[SubCount].BValue = (String)intStartWith;        
*/
        ButtonHorOffSet = ButtonHorOffSet + ButtonHorStep;
        u8g2_for_adafruit_gfx.setCursor(ButtonHorOffSet,ButtonOffSetY);
        u8g2_for_adafruit_gfx.print(IconBack);
        SubCount++;
/*
        ButtonData[SubCount].BFunction = (String)"MenuBack";
        ButtonData[SubCount].BValue = (String)intStartWith;        
*/

        ButtonHorOffSet = ButtonHorOffSet + ButtonHorStep;
        u8g2_for_adafruit_gfx.setCursor(ButtonHorOffSet,ButtonOffSetY);
        u8g2_for_adafruit_gfx.print(IconForward);
        SubCount++;
/*
        ButtonData[SubCount].BFunction = (String)"MoveForward";
        ButtonData[SubCount].BValue = (String)intStartWith;        
*/

        ButtonHorOffSet = ButtonHorOffSet + ButtonHorStep;
        u8g2_for_adafruit_gfx.setCursor(ButtonHorOffSet,ButtonOffSetY);
        u8g2_for_adafruit_gfx.print(IconSys);
        SubCount++;
/*
        ButtonData[SubCount].BFunction = (String)"MoveForward";
        ButtonData[SubCount].BValue = (String)intStartWith;        
*/
        u8g2_for_adafruit_gfx.setFont(f);
/* BUTTONS */


    display.update();
        
//Serial.println("Count:" + (String)Mcount);
//Serial.println("RetCount:" + (String)retCount);
}


void UpdateDone(char *filename, int intEntryNum , int DoneValue){
    int Mcount = 0;
    String SCC = sd_getfilecontent(filename);
    DynamicJsonBuffer jsonBuffer;
    JsonArray& arr = jsonBuffer.parseArray(SCC);
        for (JsonArray::iterator it=arr.begin(); it!=arr.end(); ++it)
        {
            if (Mcount == intEntryNum){
                //Serial.println("Reporting MCount >= intStartWith");
                    String SID = (*it)["id"];
                    String PName = (*it)["name"];
                    if (rbase64.decode(PName) == RBASE64_STATUS_OK ) {
                        PName  = rbase64.result();
                    }  
					
                        (*it)["done"] = (String)DoneValue;

                    String PDone = (*it)["done"];
                  //  Serial.println("Eintrag " + (String)Mcount);
                  //  Serial.println(PName);
                  //  Serial.println(SID +  "  " + PDone + "  " + PName);

            }
            Mcount++;
        }

        arr.prettyPrintTo(Serial);
        SD.remove(filename);
        File file = SD.open(filename, FILE_WRITE);
        if (!file) {
            Serial.println(F("Failed to create file"));
            return;
        }
        if (arr.printTo(file) == 0) {
            Serial.println(F("Failed to write to file"));
        }
        file.close();
    
//Serial.println("Count:" + (String)Mcount);
//Serial.println("RetCount:" + (String)retCount);
}
