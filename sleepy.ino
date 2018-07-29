/*
* Note: final step will be to implement long polling:
* https://docs.aws.amazon.com/AWSSimpleQueueService/latest/SQSDeveloperGuide/sqs-long-polling.html
https://docs.aws.amazon.com/AWSSimpleQueueService/latest/APIReference/API_ReceiveMessage.html and ctrl f long polling for sample req
*
* Simple HTTP get webclient test
* This is taken from the sample on the ADAFRUIT website. Going to modify to work for me. 
*/

//TODO NEXT:
//Write a function that syncs up the time with a server
// Only need to call the function every few days. 
// Can use the timeLib to set it up so its called at this interval.
// Having a function to do this will also save memory and compute power.

/*
 setSyncProvider(getTimeFunction);// Set the external time
 // provider
 setSyncInterval(interval); // Set the number of
 // seconds between re-syncs
 */

#include "sleepy.h"

void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  // This function utilises NTP/UDP 
  t = whats_the_time();
  Serial.println("The time is: " + String(t))

}


void loop() {
  // this is how I will sign the request. 
  // uint8_t *hash;
  // Sha256.initHmac("hash key",8); // key, and length of key in bytes
  // Sha256.print("This is a message to hash");
  // hash = Sha256.resultHmac();
  const char* host = service + "." + region + ".amazonaws.com";
  const char* endpoint = "https://" + host + "/" + account_number + "/" + queueName;

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
