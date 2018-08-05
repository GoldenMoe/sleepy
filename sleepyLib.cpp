#include "Arduino.h"
#include <ESP8266HTTPClient.h>
#include <TimeLib.h>
#include <sha256.h>


time_t get_time_from_api(void){
    extern String TIME_API_KEY;
    String url = "http://api.timezonedb.com/v2/get-time-zone?key=" + TIME_API_KEY + "&format=json&by=zone&zone=Australia/Sydney";

    HTTPClient http;
    http.begin(url.c_str());
    int httpCode = http.GET();
    Serial.println(String(httpCode));

    if (httpCode == 200){
        String payload = http.getString(); // response body
        http.end();
        
        const char* keyword = "timestamp\":";
        // Parse the json for the unix epoch (I feel dirty)
        return (time_t) payload.substring( payload.indexOf(keyword, 0) + strlen(keyword) ).toInt();
    }
    else { 
        // Error 
        http.end();
        return -1;
    }
}

char* construct_aws_request(const char* key, const char* msg){
    //TODO
    char* todo = "todo";
    //receive message
    //check for "<body>" inside response
    //purge queue (handle the 403 that happens within 60 secs of purges)
    return todo;
}

// %Y%m%dT%H%M%SZ - amz == true
// %Y%m%d         - amz == false
String format_time_for_request(time_t t, bool amz){
    String timeString = String(year(t)) + String(month(t)) + String(day(t));
    if (amz) {
        timeString = timeString + "T" + String(hour(t)) + String(minute(t)) + String(second(t)) + "Z";
    }
    return timeString;
}


uint8_t  hashityall(void){
    uint8_t *hash;
    Sha256.initHmac( (const uint8_t*)"hash key",8); // key, and length of key in bytes
    Sha256.print("This is a message to hash");
    hash = Sha256.resultHmac();
    int i;
    for (i=0; i<32; i++){
        //does it change when I cast to signed or String?
        Serial.print(hash[i], HEX);
    }
    Serial.println();
    //Serial.println((char*)hash);
    return 0;
}