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

    // Set scheduler to call my api-time-getting function once a day
    setSyncProvider(get_time_from_api);  
    setSyncInterval(86400);
    Serial.println("The time is " + String(now()));
}


void loop() {

  delay(5000);
  Serial.print("connecting to ");
  Serial.println(host);
  
  // // Use WiFiClient class to create TCP connections
  // WiFiClient client;

  // if (!client.connect(host, httpPort)) {
  //   Serial.println("connection failed");
  //   return;
  // }
  
  // // We now create a URI for the request
  // String url = "/testwifi/index.html";
  // Serial.print("Requesting URL: ");
  // Serial.println(url);
  
  // // This will send the request to the server
  // client.print(String("GET ") + url + " HTTP/1.1\r\n" +
  //              "Host: " + host + "\r\n" + 
  //              "Connection: close\r\n\r\n");
  // delay(500);
  
  // // Read all the lines of the reply from server and print them to Serial
  // while(client.available()){
  //   String line = client.readStringUntil('\r');
  //   Serial.print(line);
  // }
  
  // Serial.println();
  // Serial.println("closing connection");
}
