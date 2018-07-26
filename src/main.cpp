/*
  SD card read/write

 This example shows how to read and write data to and from an SD card file
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */



//#include <Arduino.h>
#include <SPI.h>
#include "Esp.h"
#include "include_SD.h"
#include "include_EPD.h"
#include "include_UNICODE.h"
#include "include_structs.h"
PositionType PosData; //Actual display position
buttonDataTyp ButtonData[17];
//#include "include_JSON.h"
#include "include_ReadAndShow.h"

int MainDataOffset = 0;
String DataID1 = (String)"" ;
String DataID2 = (String)"" ;
String DataID3 = (String)"" ;


char getout[] = "json1.json";
String tmpS1;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
   sd_init();
    init_EPD();
   // String SCC = sd_getfilecontent(getout);
   // Serial.println("SCC--------------");
   // Serial.println(SCC);
   //  Serial.println("SCC--------------");

//testjson(SCC);//
ShowEntries(getout,2,3);

}

void loop() {
        if (Serial.available() > 0) {
            
        }
        
 
 
 











//        showIt();
}

