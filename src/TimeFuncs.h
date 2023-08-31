//
// Created by Administrator on 2023/8/30.
//

#ifndef ESP32_TIMEFUNCS_H
#define ESP32_TIMEFUNCS_H

#include "WiFiUdp.h"
#include "NTPClient.h"


class TimeFuncs {
public:
    unsigned long simulatedNtpTime;     // 用来输出
    unsigned long ntpUpdateInterval; // 10分钟的时间间隔

    TimeFuncs();

    void setNtpClientTime();
//    void updateNtpClientTime();
    void runNtpClientTime();
private:
    const char* ntpServer = "ntp.ntsc.ac.cn";
    const long gmtOffset = 8 * 3600;
    WiFiUDP udp;
    NTPClient timeClient;

    unsigned long storedTime;        // 存储的从NTP获取的时间戳
    unsigned long ntpUpdateTime;     // 上次更新NTP时间的时间


};


#endif //ESP32_TIMEFUNCS_H
