/*
* Note: final step will be to implement long polling:
* https://docs.aws.amazon.com/AWSSimpleQueueService/latest/SQSDeveloperGuide/sqs-long-polling.html
https://docs.aws.amazon.com/AWSSimpleQueueService/latest/APIReference/API_ReceiveMessage.html and ctrl f long polling for sample req
*
*/

#include "sleepy.h"

void setup() { 
    extern String TIME_API_KEY;
    Serial.begin(115200);
    delay(100);

    // Connect to WiFi
    Serial.print("\nConnecting to ");
    Serial.print(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(300);
        Serial.print(".");
    }
    Serial.println();

    // Set scheduler to call my api-time-getting function once a day
    setSyncProvider(get_time_from_api);  
    setSyncInterval(86400);
    Serial.println("The time is " + String(now()));

    hashityall();
}


void loop() {

  delay(15000);
  Serial.print("I'm not doing anything... \n");

}
