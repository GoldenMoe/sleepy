#ifndef __SLEEPY_H__
#define __SLEEPY_H__

// Libraries and Dependencies
#include "secret.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <TimeLib.h> 
#include <sha256.h>

// GLOBALS
const char* method = "GET";
const char* service = "sqs";
const char* region = "ap-southeast-2";
const char* account_number = "141291046059";
const char* queueName = "sleepyQueue";
time_t t;
const short int httpPort = 80;

// Function Definitions
char* construct_aws_request(const char* key, const char* msg);
int whats_the_time(void);

#endif