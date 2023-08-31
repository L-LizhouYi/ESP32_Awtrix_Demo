//
// Created by Administrator on 2023/8/30.
//

#include "EnaLeds.h"

EnaLeds::EnaLeds(){}

std::vector<int> EnaLeds::generate_number_list(int start_value) {
    std::vector<int> nl;
    std::vector<int> nlist = {0, 3, 16};

    for (int i : nlist) {
        int km = start_value + i;
        if (km % 2 == 0) {
            nl.insert(nl.end(), {km, km - 1, km - 2, km - 3, km - 4});
        } else {
            nl.insert(nl.end(), {km, km + 1, km + 2, km + 3, km + 4});
        }
    }

    return nl;
}

std::vector<int> EnaLeds::generate_led_list(unsigned long now_time) {
    struct tm *timeinfo;
    time_t timestamp = static_cast<time_t>(now_time);
    timeinfo = localtime(&timestamp);
    char formatted_dt[15];
    strftime(formatted_dt, sizeof(formatted_dt), "%Y%m%d%H%M%S", timeinfo);
    std::string nowTime = formatted_dt + 8;

    std::vector<int> res;
    int index[] = {30, 62, 110, 142, 190, 222};
    for (int i = 0; i < 6; ++i) {
        std::vector<int> a = generate_number_list(index[i]);

        for (int s = 0; s < 15; ++s) {
            if (led_num[nowTime[i] - '0'][s] != 0) {
                res.push_back(a[s]);
            }
        }
    }
    return res;
}