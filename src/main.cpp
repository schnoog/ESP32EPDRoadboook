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

#include <SPI.h>
#include "Esp.h"

#include "include_SD.h"
#include "include_EPD.h"
//#include "include_JSON.h"

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
   sd_init();
    init_EPD();
}

void loop() {
        if (Serial.available() > 0) {
            
        }



  myFile = SD.open("json1.json");
  if (myFile) {
    Serial.println("json1.json:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening json1.json");
  }









        showIt();
}

