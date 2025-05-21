//
// Created by mu4di on 25-5-19.
//

#include "imu_output.h"



void App_IMU_Init(void) {
    mpu.hi2c = &hi2c1;
    // mpu.addr 不用管，Init里自动赋值
    uint8_t ret = MPU6050_Init(&mpu);
    if (ret) {
        // 初始化失败，自己加个报错提示
    }
}

void App_IMU_Update(void) {
    if (MPU6050_ReadRaw(&mpu) == 0) {
        float ax, ay, az, gx, gy, gz;
        MPU6050_GetAccelGyro(&mpu, &ax, &ay, &az, &gx, &gy, &gz);
        // ax,ay,az 单位 g   gx,gy,gz 单位 deg/s
        // mpu.temp_deg 单位 摄氏度
        // 直接用你的数据做姿态解算、运动控制啥的
    }
}