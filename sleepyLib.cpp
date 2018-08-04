#include "Arduino.h"
#include <ESP8266HTTPClient.h>
#include <aJSON.h>

time_t get_time_from_api(void){
    extern String TIME_API_KEY;
    String url = "http://api.timezonedb.com/v2/get-time-zone?key=" + TIME_API_KEY + "&format=json&by=zone&zone=Australia/Sydney";
    Serial.println(url);

    HTTPClient http;
    http.begin(url.c_str());
    int httpCode = http.GET();
    http.end();

    if(httpCode == 200){
        const int responseBodySize = http.getSize();
        String payload = http.getString(); // response body
        Serial.println(String(httpCode) + payload);
        
        // aJsonObject* jsonObject = aJson.parse( (char*) payload.c_str() );
        // aJsonObject* timestamp = aJson.getObjectItem(jsonObject, "timestamp");
        // Serial.println(timestamp->valuestring);
        // aJson.deleteItem(jsonObject);
    }
    else { return -1; }
    return 0;
}

char* construct_aws_request(const char* key, const char* msg){
    //TODO
    char* todo = "todo";
    //receive message
    //check for "<body>" inside response
    //purge queue (handle the 403 that happens within 60 secs of purges)
    return todo;
}