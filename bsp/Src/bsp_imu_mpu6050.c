#include "bsp_imu_mpu6050.h"

#define MPU6050_ADDR         (0x68 << 1) // 8位地址（HAL库要左移一位）
#define MPU6050_PWR_MGMT_1   0x6B
#define MPU6050_ACCEL_XOUT_H 0x3B

// 写寄存器
static uint8_t mpu6050_write_reg(MPU6050_HandleTypeDef *mpu, uint8_t reg, uint8_t data) {
    return HAL_I2C_Mem_Write(mpu->hi2c, mpu->addr, reg, 1, &data, 1, 100);
}

// 读寄存器
static uint8_t mpu6050_read_regs(MPU6050_HandleTypeDef *mpu, uint8_t reg, uint8_t *buf, uint8_t len) {
    return HAL_I2C_Mem_Read(mpu->hi2c, mpu->addr, reg, 1, buf, len, 100);
}

// 初始化
uint8_t MPU6050_Init(MPU6050_HandleTypeDef *mpu) {
    if (!mpu || !mpu->hi2c) return 1;
    mpu->addr = MPU6050_ADDR;
    HAL_Delay(50);
    // 唤醒MPU6050
    if (mpu6050_write_reg(mpu, MPU6050_PWR_MGMT_1, 0x00)) return 2;
    HAL_Delay(50);
    // 可根据需求配置量程/滤波等，这里默认
    return 0; // 成功
}

// 读取原始加速度/陀螺仪/温度
uint8_t MPU6050_ReadRaw(MPU6050_HandleTypeDef *mpu) {
    uint8_t buf[14];
    if (!mpu || !mpu->hi2c) return 1;
    if (mpu6050_read_regs(mpu, MPU6050_ACCEL_XOUT_H, buf, 14)) return 2;

    mpu->accel[0] = (int16_t)(buf[0] << 8 | buf[1]);
    mpu->accel[1] = (int16_t)(buf[2] << 8 | buf[3]);
    mpu->accel[2] = (int16_t)(buf[4] << 8 | buf[5]);
    mpu->temp_raw = (int16_t)(buf[6] << 8 | buf[7]);
    mpu->gyro[0]  = (int16_t)(buf[8] << 8 | buf[9]);
    mpu->gyro[1]  = (int16_t)(buf[10] << 8 | buf[11]);
    mpu->gyro[2]  = (int16_t)(buf[12] << 8 | buf[13]);
    mpu->temp_deg = 36.53f + ((float)mpu->temp_raw) / 340.0f;
    return 0;
}

// 换算加速度(g)、角速度(deg/s)
void MPU6050_GetAccelGyro(const MPU6050_HandleTypeDef *mpu, float *ax, float *ay, float *az, float *gx, float *gy, float *gz)
{
    if (mpu == NULL) return;
    if (ax) *ax = (float)mpu->accel[0] / 16384.0f;
    if (ay) *ay = (float)mpu->accel[1] / 16384.0f;
    if (az) *az = (float)mpu->accel[2] / 16384.0f;
    if (gx) *gx = (float)mpu->gyro[0] / 131.0f;
    if (gy) *gy = (float)mpu->gyro[1] / 131.0f;
    if (gz) *gz = (float)mpu->gyro[2] / 131.0f;
}

