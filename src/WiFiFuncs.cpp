//
// Created by Administrator on 2023/8/29.
//

#include "WiFiFuncs.h"
const char* htmlContent = R"html(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 WiFi Setup</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 20px;
            text-align: center;
        }
        h1 {
            margin-top: 20px;
        }
        form {
            display: inline-block;
            text-align: left;
        }

        input[type="text"],
        input[type="password"] {
            width: 100%;
            padding: 10px;
            margin: 5px 0;
            border: 1px solid #ccc;
            border-radius: 5px;
            box-sizing: border-box;
        }

        button {
            background-color: #4CAF50;
            color: white;
            padding: 10px 20px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }
        .button-container {
            display: flex;
            justify-content: space-between;
            margin-top: 10px;
        }
    </style>
    <script>
        function clearForm() {
            document.getElementById("ssid").value = "";
            document.getElementById("password").value = "";
        }
    </script>
</head>
<body>
<h1>WiFi Setup</h1>
<form action="/configure" method="get">
    <label>SSID:</label>
    <input type="text" id="ssid" name="ssid"><br><br>
    <label>Password:</label>
    <input type="password" id="password" name="password"><br><br>
    <div class="button-container">
        <button type="submit">Submit</button>
        <button type="button" onclick="clearForm()">Clear</button>
    </div>
</form>
</body>
</html>
)html";


WiFiFuncs::WiFiFuncs() : server(80) {}


bool WiFiFuncs::isWiFiConfigFlag() {
    return EEPROM.read(WIFI_FLAG_ADDRESS);
}

WiFiConfig WiFiFuncs::readWifiConfigtoEEPROM() {
    WiFiConfig readConfig;
    return EEPROM.get(WIFI_CONFIG_ADDRESS,readConfig);
}

void WiFiFuncs::writeWiFiConfigToEEPROM(const WiFiConfig& writeConfig) {
    EEPROM.put(WIFI_CONFIG_ADDRESS,writeConfig);
    EEPROM.commit();
}

void WiFiFuncs::setWiFiConfigFlag(bool flag) {
    EEPROM.write(WIFI_FLAG_ADDRESS,flag);
    EEPROM.commit();
}

void WiFiFuncs::connectToWiFiAP() {
    WiFi.softAP(_apSSID, _apPASSWORD);
    Serial.println("ESP32 in AP mode");
    Serial.print("AP SSID: ");
    Serial.println(_apSSID);
    Serial.print("AP Password: ");
    Serial.println(_apPASSWORD);
}

void WiFiFuncs::configureAPWebServer() {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", htmlContent);
    });

    server.on("/configure", HTTP_GET, [this](AsyncWebServerRequest *request){
        if (request->hasParam("ssid") && request->hasParam("password")) {
            String ssidValue = request->getParam("ssid")->value();
            String passwordValue = request->getParam("password")->value();

            Serial.println(ssidValue);
            Serial.println(passwordValue);

            WiFiConfig wifiConfig;
            strcpy(wifiConfig.ssid, ssidValue.c_str());
            strcpy(wifiConfig.password, passwordValue.c_str());

            writeWiFiConfigToEEPROM(wifiConfig);
            setWiFiConfigFlag(true);

            request->send(200, "text/plain", "WiFi configuration saved");

            delay(2000);
            ESP.restart();

        } else {
            request->send(400, "text/plain", "Missing parameters");
        }
    });

    server.begin();
}

void WiFiFuncs::connectToWiFiStation() {
    // 判断wifi可用 连接上就Ok
    WiFiConfig readRespons = readWifiConfigtoEEPROM();
    WiFi.begin(readRespons.ssid, readRespons.password);

    int connectionAttempts = 0;
    while (connectionAttempts < 5 && WiFi.status() != WL_CONNECTED) {
        Serial.println("Connecting to WiFi...");
        delay(1000);
        connectionAttempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Connected to WiFi");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());

        // 还要检查可用性

    } else {
        Serial.println("Failed to connect to WiFi");
        setWiFiConfigFlag(false);
        ESP.restart();
    }

}