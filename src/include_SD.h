#include "SdFat.h"
const uint8_t SOFT_MISO_PIN = 19;
const uint8_t SOFT_MOSI_PIN = 23;
const uint8_t SOFT_SCK_PIN  = 18;
const uint8_t SD_CHIP_SELECT_PIN = 4;
//uos.sdconfig(uos.SDMODE_SPI, clk=18, mosi=23, miso=19, cs=4)
SdFatSoftSpi<SOFT_MISO_PIN, SOFT_MOSI_PIN, SOFT_SCK_PIN> SD;
File myFile;

// global for card size
uint32_t cardSize;
// global for card erase size
uint32_t eraseSize;






//--------------------------------------------------------------
void ls(char *path) {
  SdBaseFile dir;
  if (!dir.open(path, O_READ) || !dir.isDir()) {
    Serial.println("bad dir");
    return;
  }
  dir.ls(&Serial, LS_R);
}
//-------------------------------------------------------------
void listfiles(){
    SD.ls(&Serial, LS_R);
}
//-------------------------------------------------------------

void sd_init(){
  Serial.print("Initializing SD card...");
  
  if (!SD.begin(SD_CHIP_SELECT_PIN)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  listfiles();
}