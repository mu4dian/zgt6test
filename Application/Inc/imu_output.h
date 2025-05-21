//
// Created by mu4di on 25-5-19.
//

#ifndef IMU_OUTPUT_H
#define IMU_OUTPUT_H
#include "bsp_imu_mpu6050.h"
#include "i2c.h"
extern MPU6050_HandleTypeDef mpu; // 声明全局/静态变量
void App_IMU_Init(void);
void App_IMU_Update(void);
#endif //IMU_OUTPUT_H
