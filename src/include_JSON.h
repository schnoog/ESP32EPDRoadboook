
//String JsonString = '{"1":"\u00c4bersold","2":"Blasiwald","3":"\u00b5PythonLand"}';

#include <ArduinoJson.h>
#include <cstdlib>
#include <rBase64.h>


void testjson(String JSONString){
Serial.println("testjson mit string:" + JSONString);
    //DynamicJsonBuffer jsonBuffer;
    StaticJsonBuffer<1024> jsonBuffer;
    //StaticJsonBuffer<512> jb;
    JsonArray& arr = jsonBuffer.parseArray(JSONString);
    
    //Serial.println(
        Serial.println("JSONArray arr");
        arr.prettyPrintTo(Serial);
    //JsonArray& arr = jsonBuffer.parseArray(string2char(JSONString));
        //JsonObject& root = jb.parseObject(JSONString);

        //Serial.println("JSONObject root");
        //root.prettyPrintTo(Serial);

        for (JsonArray::iterator it=arr.begin(); it!=arr.end(); ++it)
        {
            Serial.println("LoopOutput") ;
            String SID = (*it)["id"];
            String PName = (*it)["name"];
            if (rbase64.decode(PName) == RBASE64_STATUS_OK ) {
                Serial.println("\nConverted the String from Base64 : ");
                Serial.println(rbase64.result());
            PName  = rbase64.result();
            }  


            String PDone = (*it)["done"];
            Serial.println(PName);
            Serial.println(SID +  "  " + PDone);
        } 
}
 