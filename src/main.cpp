#include "Arduino.h"
#include "WiFiFuncs.h"
#include "TimeFuncs.h"
#include "EnaLeds.h"
#include "Ticker.h"
#include "FastLED.h"

#define LED_PIN     5
#define NUM_LEDS    256
CRGB leds[NUM_LEDS];



WiFiFuncs myObject;
TimeFuncs myObjTime;
EnaLeds myObjLeds;
Ticker ntpUpdater;
bool readyFlag;


void setNtpClientTime() {
    myObjTime.setNtpClientTime();
}


void setup() {

    Serial.begin(9600);
    EEPROM.begin(EEPROM_SIZE);

    if (myObject.isWiFiConfigFlag()) {
        myObject.connectToWiFiStation();

        myObjTime.setNtpClientTime(); //       更新本地时间
        ntpUpdater.attach_ms(myObjTime.ntpUpdateInterval, setNtpClientTime);
        readyFlag = true;

        FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
        FastLED.clear();
        FastLED.show();

    } else {
        myObject.connectToWiFiAP();
        myObject.configureAPWebServer();
    }
}

void loop() {
    if (readyFlag) {
        myObjTime.runNtpClientTime();
        std::vector<int> res = myObjLeds.generate_led_list(myObjTime.simulatedNtpTime);

        FastLED.clear();
        CRGB warmYellow = CRGB(255, 200, 0);
        FastLED.setBrightness(96);
        for (int value : res) {
            leds[value] = warmYellow;
        }
        leds[91]= warmYellow;
        leds[93]= warmYellow;
        leds[171]= warmYellow;
        leds[173]= warmYellow;
        FastLED.show();
    }
}