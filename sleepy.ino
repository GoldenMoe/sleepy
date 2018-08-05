/*
* Note: final step will be to implement long polling:
* https://docs.aws.amazon.com/AWSSimpleQueueService/latest/SQSDeveloperGuide/sqs-long-polling.html
https://docs.aws.amazon.com/AWSSimpleQueueService/latest/APIReference/API_ReceiveMessage.html and ctrl f long polling for sample req
*
*/

#include "sleepy.h"
#include <sha256.h>

void setup() { 
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
}


void loop() {
    time_t t = now();
    char amz_date[17];
    char datestamp[9];
    format_time_for_request(amz_date, t, true); // will edit first argument
    format_time_for_request(datestamp, t, false); // pass str by reference
    
    char* signed_headers = "host";
    char* algorithm = "AWS4-HMAC-SHA256";
    char canonical_uri = '/';  
    String canonical_headers = "host:" + host + '\n';
    String credential_scope = String(datestamp) + '/' + region + '/' + service + '/' + "aws4_request";
    String  amz_credential = String(AWS_ACCESS_KEY_ID) + '/' + credential_scope;
            amz_credential.replace("/", "%2f"); // url encode

    
    String canonical_querystring = "Action=ReceiveMessage";
    canonical_querystring += "&Version=2012-11-05";
    canonical_querystring += "&X-Amz-Algorithm=" + String(algorithm);
    canonical_querystring += "&X-Amz-Credential=" + amz_credential;
    canonical_querystring += "&X-Amz-Date=" + String(amz_date);
    canonical_querystring += "&X-Amz-Expires=30";
    canonical_querystring += "&X-Amz-SignedHeaders=" + String(signed_headers);
    Serial.println("querystring: " + canonical_querystring);

    // For GET requests, the payload is an empty string. This is hardcoded hash because the payload never changes.
    char* payload_hash = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";
    
    String canonical_request = method + '\n' + account_number + '/' + queueName + '\n' + canonical_querystring + '\n' + canonical_headers + '\n' + signed_headers + '\n' + String(payload_hash);
    Sha256.init();
    Sha256.print(canonical_request);
    uint8_t* hash_of_canonical_request = Sha256.result();

    // Manually iterate ahead of pointer to create hexdigest as char array
    char hexdigest[65];
    short int i;
    for (i = 0; i < HASH_LENGTH; i++){
        sprintf(hexdigest + sizeof(hexdigest[0])*2*i, "%02x", hash_of_canonical_request[i]);
    }
    
    String string_to_sign = String(algorithm) + '\n' +  String(amz_date) + '\n' +  credential_scope + '\n' +  String(hexdigest);
    Serial.println("stringtosign: " + string_to_sign);

    char initial_key[45] = "AWS4";
    uint8_t signing_key[HASH_LENGTH];
    strcat(initial_key, AWS_SECRET_ACCESS_KEY);
    
    Sha256.initHmac( (const uint8_t*)initial_key, strlen(initial_key));
    Sha256.print(datestamp);
    memcpy(signing_key, Sha256.resultHmac(), HASH_LENGTH);
    // signing_key modified by reference each call
    sign_hmac_sha256(signing_key, HASH_LENGTH, region);
    sign_hmac_sha256(signing_key, HASH_LENGTH, service);
    sign_hmac_sha256(signing_key, HASH_LENGTH, "aws4_request");
    
    delay(15000);
}
