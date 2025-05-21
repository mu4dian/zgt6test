//
// Created by mu4di on 25-5-19.
//

#include "tof_output.h"

#include <stdio.h>


void tof_output_init(void)
{
    // char msgBuffer[52];
    // for (uint8_t i = 0; i < 52; i++) {
    //     msgBuffer[i] = ' ';
    // }

    // Initialise the VL53L0X
    // statInfo_t_VL53L0X distanceStr;
    initVL53L0X(1, &hi2c2);

    // Configure the sensor for high accuracy and speed in 20 cm.
    setSignalRateLimit(200);
    setVcselPulsePeriod(VcselPeriodPreRange, 10);
    setVcselPulsePeriod(VcselPeriodFinalRange, 14);
    setMeasurementTimingBudget(300 * 1000UL);

    // 初始化VL53L0X，第二个参数1为2V8模式，大多数模块都支持
}

uint16_t distance;

void tof_output_loop(void)
{
    statInfo_t_VL53L0X distanceStr;
    distance = readRangeSingleMillimeters(&distanceStr);

    if (timeoutOccurred() || distance > 2000) { // 超过2米判异常
        printf("测距失败/超出范围\r\n");
    } else {
        printf("距离: %u mm\r\n", distance);
    }
}

