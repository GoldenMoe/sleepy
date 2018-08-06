#include "Arduino.h"
#include <ESP8266HTTPClient.h>
#include <TimeLib.h>
#include <sha256.h>


time_t get_time_from_api(void){
    extern String TIME_API_KEY;
    String url = "http://api.timezonedb.com/v2/get-time-zone?key=" + TIME_API_KEY + "&format=json&by=zone&zone=UTC";

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

// YYYYMMDD'T'HHMMSS'Z' - amz == true
// YYYYMMDD             - amz == false
void format_time_for_request(char* str, time_t t, bool amz){
    sprintf(str, "%04d%02d%02d", year(t), month(t), day(t));
    if (amz) {
        sprintf(str, "%sT%02d%02d%02dZ", str, hour(t), minute(t), second(t));
    }
    return;
}

// Warning: modifies the contents of key
void sign_hmac_sha256(uint8_t* key, size_t key_size, String msg) {
    Sha256.initHmac( (const uint8_t*)key, key_size);
    Sha256.print(msg.c_str());
    memcpy(key, Sha256.resultHmac(), HASH_LENGTH);
    return;
}