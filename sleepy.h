#ifndef __SLEEPY_H__
#define __SLEEPY_H__

// Libraries and Dependencies
#include "secret.h"
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <TimeLib.h> 
#include <string.h>

// GLOBALS
const short int httpPort = 80;

String account_number = "141291046059";
String queueName = "sleepyQueue";
String service = "sqs";

String method = "GET";
String region = "ap-southeast-2";
String host = "sqs." + region + ".amazonaws.com";
String endpoint = "http://" + host + "/" + account_number + "/" + queueName;

// Function Definitions
void format_time_for_request(char* str, time_t t, bool amz);
time_t get_time_from_api(void);
void sign_hmac_sha256(uint8_t* key, size_t key_size, String msg);

#endif