# sleepy

## Setup

1. Create a separate file named "secret.h" in this directory. There is no EEPROM to store credentials on the ESP8266 so I used a gitignored header file.
```
#ifndef __SECRET_H__
#define __SECRET_H__

    const char* ssid = "yourSSID";
    const char* password = "yourPassword";

    // Arduino User assuming SQS roles
    const char* AWS_ACCESS_KEY_ID = "****************";
    const char* AWS_SECRET_ACCESS_KEY = "********************";

    String TIME_API_KEY = "****************"; //timezonedb

#endif
```

2. Setup the ESP8266 to work with the Arduino IDE by following the guide: https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide