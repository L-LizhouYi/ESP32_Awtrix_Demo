//
// Created by Administrator on 2023/8/30.
//

#include "TimeFuncs.h"
TimeFuncs::TimeFuncs(): timeClient(udp,ntpServer,gmtOffset) {
    storedTime = 0;
    ntpUpdateInterval = 600000;


}

void TimeFuncs::setNtpClientTime(){
    unsigned long requestTime = millis();

    timeClient.begin();
    while (!timeClient.update()){
        Serial.println("Update Error!!!");
    }
    ntpUpdateTime = millis() ;
    storedTime = timeClient.getEpochTime() + ((ntpUpdateTime - requestTime) / 1000) ;


}

void TimeFuncs::runNtpClientTime() {
    unsigned long currentMillis = millis();
    // 计算模拟的NTP时间戳
    simulatedNtpTime = storedTime + ((currentMillis - ntpUpdateTime) / 1000);
    Serial.println(simulatedNtpTime);

    delay(1000); // 延迟1秒
}