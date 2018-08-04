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
String endpoint = "https://" + host + "/" + account_number + "/" + queueName;

// Function Definitions
char* construct_aws_request(const char* key, const char* msg);
time_t get_time_from_api(void);
String format_time_for_request(time_t t);

#endif