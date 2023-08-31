//
// Created by Administrator on 2023/8/29.
//

#ifndef ESP32_WIFIFUNCS_H
#define ESP32_WIFIFUNCS_H

#include "WiFi.h"
#include "EEPROM.h"
#include "ESPAsyncWebServer.h"

#define EEPROM_SIZE 512
#define WIFI_FLAG_ADDRESS 0
#define WIFI_CONFIG_ADDRESS 1

struct WiFiConfig {
    char ssid[32];
    char password[64];
};

class WiFiFuncs {
public:
    WiFiFuncs();

    bool isWiFiConfigFlag();
    void setWiFiConfigFlag(bool flag);
    WiFiConfig readWifiConfigtoEEPROM();
    void writeWiFiConfigToEEPROM(const WiFiConfig& writeConfig);

    void connectToWiFiAP();
    void connectToWiFiStation();
    void configureAPWebServer();

private:
    const char* _apSSID = "MyESP32_AP";
    const char* _apPASSWORD = "12345678";

    AsyncWebServer server;
};

#endif //ESP32_WIFIFUNCS_H
