#include "sleepy.h"

int whats_the_time(WiFiClient client){

    const char* url = "http://api.timezonedb.com/v2/get-time-zone?key=" + TIME_API_KEY + "&format=json&by=zone&zone=Australia/Sydney";
    client.print(String("GET ") + url + " HTTP/1.1\n" + "Connection: close\n"); //send req
    delay(500);
    
    // Print Response
    while(client.available()){
        String line = client.readStringUntil('\n');
        Serial.print(line);
    }

    /* plan: extract the "timestamp" header from the time api. Return this, it is the unix epoch.
    Then I can rearrange that using the timelib to get it into AWS's format. */



    return 0;
}

char* construct_aws_request(const char* key, const char* msg){
    //TODO
    char* todo = "todo";
    return todo;
}