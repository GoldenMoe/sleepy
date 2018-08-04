#ifndef __SLEEPY_H__
#define __SLEEPY_H__

// Libraries and Dependencies
#include "secret.h"
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <TimeLib.h> 
#include <string.h>

// GLOBALS
time_t t;
const short int httpPort = 80;

String account_number = "141291046059";
String queueName = String("sleepyQueue");
String service = String("sqs");

String method = String("GET");
String region = String("ap-southeast-2");
String host = String("sqs." + region + ".amazonaws.com");
String endpoint = String("https://" + host + "/" + account_number + "/" + queueName);

// Function Definitions
char* construct_aws_request(const char* key, const char* msg);
time_t get_time_from_api(void);

#endif