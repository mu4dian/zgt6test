#ifndef __BSP_IMU_MPU6050_H__
#define __BSP_IMU_MPU6050_H__

#include "main.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        I2C_HandleTypeDef *hi2c;   // 指向CubeMX生成的I2C句柄
        uint8_t           addr;    // 器件I2C地址（一般0x68）
        int16_t           accel[3];// x/y/z加速度原始值
        int16_t           gyro[3]; // x/y/z角速度原始值
        int16_t           temp_raw;// 温度原始值
        float             temp_deg;// 温度（摄氏度）
    } MPU6050_HandleTypeDef;

    // 初始化MPU6050
    uint8_t MPU6050_Init(MPU6050_HandleTypeDef *mpu);
    // 读取原始数据
    uint8_t MPU6050_ReadRaw(MPU6050_HandleTypeDef *mpu);
    // 读取加速度（g）和角速度（deg/s）
    void    MPU6050_GetAccelGyro(const MPU6050_HandleTypeDef *mpu, float *ax, float *ay, float *az, float *gx, float *gy, float *gz);

#ifdef __cplusplus
}
#endif

#endif // __BSP_IMU_MPU6050_H__
