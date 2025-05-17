#include "task_motor.h"

#include <stdio.h>

#include "app_music.h"
#include "bsp_imu_mpu6050.h"
#include "bsp_tof.h"
#include "key_test.h"
#include "line_follow.h"
#include "VL53L0X.h"

// 调试计数
uint8_t i = 0;


#include "bsp_imu_mpu6050.h"
extern I2C_HandleTypeDef hi2c1; // 由CubeMX自动生成

MPU6050_HandleTypeDef mpu; // 声明全局/静态变量

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

// VL53L0X_HandleTypedef tof;


void i2c_scan() {
    printf("I2C scan...\r\n");
    for(uint8_t addr = 1; addr < 127; addr++) {
        if(HAL_I2C_IsDeviceReady(&hi2c2, addr << 1, 2, 2) == HAL_OK) {
            printf("Device found at 0x%02X\r\n", addr << 1);
        }
        HAL_Delay(10);
    }
}

extern I2C_HandleTypeDef hi2c2;

// 电机控制任务
void MotorTask(void *argument)
{
    uint16_t dist = 0;

    // VL53L0X初始化，第二个参数为I2C句柄
    if (!initVL53L0X(1, &hi2c2)) { // 1 表示 2V8 模式，大部分VL53L0X模块可用
        printf("VL53L0X 初始化失败！\r\n");
        while (1);
    }
    setTimeout(200); // 设置超时时间200ms（可选）
    printf("VL53L0X 初始化成功，开始测距...\r\n");

    // 初始化电机PID控制
    Chassis_Motor_PIDControl_Init();

    // uint16_t dist = 0;
    // if (VL53L0X_Init(&tof, &hi2c2, 0x52) == 0)
    //     printf("VL53L0X 初始化成功！\r\n");
    // else
    //     printf("VL53L0X 初始化失败\r\n");

    // 设置一个初始测试速度（可以根据需要修改）
    // 比如设置目标速度为100个脉冲每周期
    App_IMU_Init();
    // Boot_Sound();
    uint32_t lastWakeTime = osKernelGetTickCount();
    initVL53L0X(1, &hi2c1);
    // 不设置任何花里胡哨的参数
    setMeasurementTimingBudget(33000);
    HAL_Delay(100);
    // 主循环
    for (;;)
    {
        // uint16_t distance = readRangeSingleMillimeters(NULL);
        // if (timeoutOccurred() || distance > 2000) {  // 大于2米都是异常
        //     printf("测距失败或超出范围\r\n");
        // } else {
        //     printf("距离: %u mm\r\n", distance);
        // }
        HAL_Delay(100);
        // i2c_scan();
        // if (VL53L0X_ReadRangeMM(&tof, &dist) == 0) {
        //     printf("距离: %d mm\r\n", dist);
        // } else {
        //     printf("测距失败\r\n");
        // }
        // HAL_Delay(100);
        // Key_Test_Task();
        HAL_Delay(1); // 10ms轮询，防止刷屏
        // 更新PID控制
        // if (MPU6050_ReadRaw(&mpu) == 0)
        // {
        //     float ax, ay, az, gx, gy, gz;
        //     MPU6050_GetAccelGyro(&mpu, &ax, &ay, &az, &gx, &gy, &gz);
        //     // Vofa+ 格式输出，数值用逗号分隔，一行结尾为 \n
        //     printf("%.3f,%.3f,%.3f,%.2f,%.2f,%.2f,%.2f\n",
        //            ax, ay, az, gx, gy, gz, mpu.temp_deg);
        // }
        // LineFollow_Task();
        osDelay(1); // 20ms扫描一次
        // Chassis_Motor_SetSpeed(10.0f,10.0,10.0f,10.0f);
        // printf("%.2f,%.2f\n",wheelController1.target_speed,wheelController1.current_speed);
        // // 打印调试信息
        // printf("Motor Speed - Target: %.2f, Current: %.2f, Output: %.2f\r\n",
        //        wheelController1.target_speed,
        //        wheelController1.current_speed,
        //        wheelController1.pid.output); // 按照固定周期执行
        osDelay(PID_CONTROL_PERIOD);
    }
}
