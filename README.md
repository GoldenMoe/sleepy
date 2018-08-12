# sleepy

## Setup

1. Create a separate file named "secret.h" in this directory. There is no EEPROM to store credentials on the ESP8266 so I used a gitignored header file. The `TIME_API_KEY` is obtained from registering a free account on [timezonedb.](https://timezonedb.com/api) The AWS credentials must contain a user with SQS ReceiveMessage permissions.

```
#ifndef __SECRET_H__
#define __SECRET_H__

    const char* ssid = "YourSSID";
    const char* password = "**********";

    // Arduino User assuming SQS roles
    const char* AWS_ACCESS_KEY_ID = "****************";
    const char* AWS_SECRET_ACCESS_KEY = "********************";

    String TIME_API_KEY = "****************"; //timezonedb

#endif
```

2. Setup the ESP8266 to work with the Arduino IDE by following [the guide.](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide)
3. Clone dependencies to ~/Arduino/libraries:
    * [TimeLib](git@github.com:PaulStoffregen/Time.git)
    * A [fork of an old Arduino SHA library](git@github.com:beyondszine/Cryptosuite.git) that modifies to work with ESP8266. Additionally, move the folder "Sha" into Arduino/libraries, otherwise the compiler will not find it.
