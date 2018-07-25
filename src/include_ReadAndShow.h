#include <ArduinoJson.h>
#include <cstdlib>
#include <rBase64.h>



void ShowEntries(char *filename, int intStartWith , int MaxCount){
    String SCC = sd_getfilecontent(filename);
    int Mcount = 0;
    int retCount = 0;
//    StaticJsonBuffer<1024> jsonBuffer;
    DynamicJsonBuffer jsonBuffer;
    //Serial.println(SCC);
    JsonArray& arr = jsonBuffer.parseArray(SCC);

        for (JsonArray::iterator it=arr.begin(); it!=arr.end(); ++it)
        {
            //Serial.println("Eintrag " + (String)count);
            if (Mcount >= intStartWith){
                if(retCount < MaxCount){
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
                    retCount++;
                }
            }
            Mcount++;
        }
Serial.println("Count:" + (String)Mcount);
Serial.println("RetCount:" + (String)retCount);
}