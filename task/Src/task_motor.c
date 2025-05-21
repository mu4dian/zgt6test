#include "task_motor.h"

#include <i2c.h>
#include <stdio.h>
#include <usart.h>

#include "app_imu_pose.h"
#include "app_music.h"
#include "bsp_imu_mpu6050.h"
#include "bsp_tof.h"
#include "chassis_app.h"
#include "key_test.h"
#include "line_follow.h"
#include "tof_output.h"
#include "VL53L0X.h"
#include "app_imu_pose.h"
#include "imu_output.h"
IMU_Pose_t car_pose;
// 调试计数
uint8_t i = 0;


#include "bsp_imu_mpu6050.h"


// VL53L0X_HandleTypedef tof;


// void i2c_scan() {
//     printf("I2C scan...\r\n");
//     for(uint8_t addr = 1; addr < 127; addr++) {
//         if(HAL_I2C_IsDeviceReady(&hi2c2, addr << 1, 2, 2) == HAL_OK) {
//             printf("Device found at 0x%02X\r\n", addr << 1);
//         }
//         HAL_Delay(10);
//     }
// }
extern MPU6050_HandleTypeDef mpu;


// 电机控制任务
void MotorTask(void *argument)
{

    Chassis_Motor_PIDControl_Init();
    // Chassis_RunCircle(0.5f, 0.1f);
    App_IMU_Init();

    // Boot_Sound();

    // tof_output_init();
    // if (!initVL53L0X(1, &hi2c2)) {
    //     printf("VL53L0X初始化失败\r\n");
    //
    // }
    // printf("VL53L0X初始化成功\r\n");
    //
    // setMeasurementTimingBudget(33000); // 33ms标准测距
    //
    // uint16_t distance;
    // // 主循环
    for (;;)
    {
        MPU6050_ReadRaw(&mpu);
        IMU_Pose_Update(&car_pose, &mpu);

        // 现在car_pose.roll/pitch/yaw即为实时姿态角，单位°
        // 打印测试
        printf("roll: %.2f, pitch: %.2f, yaw: %.2f\r\n", car_pose.roll, car_pose.pitch, car_pose.yaw);

        // tof_output_loop();
        // uint16_t distance = readRangeSingleMillimeters(NULL);
        // if (timeoutOccurred() || distance > 2000) {  // 大于2米都是异常
        //     printf("测距失败或超出范围\r\n");
        // } else {
        //     printf("距离: %u mm\r\n", distance);
        // }
        // HAL_Delay(100);
        // i2c_scan();
        // if (VL53L0X_ReadRangeMM(&tof, &dist) == 0) {
        //     printf("距离: %d mm\r\n", dist);
        // } else {
        //     printf("测距失败\r\n");
        // }
        // HAL_Delay(100);
        // Key_Test_Task();
        // HAL_Delay(1); // 10ms轮询，防止刷屏
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
        // Music_Play();
        osDelay(1); // 20ms扫描一次
        // Chassis_Motor_SetSpeed(0.0f,0.0,0.0f,0.0f);
        // printf("%.2f,%.2f\n",wheelController1.target_speed,wheelController1.current_speed);
        // // 打印调试信息
        // printf("Motor Speed - Target: %.2f, Current: %.2f, Output: %.2f\r\n",
        //        wheelController1.target_speed,
        //        wheelController1.current_speed,
        //        wheelController1.pid.output); // 按照固定周期执行
        osDelay(PID_CONTROL_PERIOD);
    }
}
