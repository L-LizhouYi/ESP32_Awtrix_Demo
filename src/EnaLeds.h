//
// Created by Administrator on 2023/8/30.
//

#ifndef ESP32_ENALEDS_H
#define ESP32_ENALEDS_H

#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <map> // 添加这一行


class EnaLeds {
public:
    EnaLeds();
    std::vector<int> generate_number_list(int start_value);
    std::vector<int> generate_led_list(unsigned long now_time);

private:
    std::map<int, std::vector<int>> led_num = {
            {1, {0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1}},
            {2, {1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1}},
            {3, {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1}},
            {4, {1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1}},
            {5, {1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1}},
            {6, {1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1}},
            {7, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1}},
            {8, {1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1}},
            {9, {1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1}},
            {0, {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1}}
    };

};


#endif //ESP32_ENALEDS_H
