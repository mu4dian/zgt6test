#ifndef __APP_IMU_POSE_H
#define __APP_IMU_POSE_H

#include "bsp_imu_mpu6050.h"

typedef struct {
    float roll;    // 横滚角
    float pitch;   // 俯仰角
    float yaw;     // 偏航角（仅靠陀螺积分，会漂移）
    float gx_bias, gy_bias, gz_bias; // 陀螺零偏
    float dt;      // 每次调用的周期，单位：秒
} IMU_Pose_t;

// 初始化（传入IMU句柄和dt）
void IMU_Pose_Init(IMU_Pose_t *pose, float dt);

// 传入BSP读好的mpu，输出当前姿态角
void IMU_Pose_Update(IMU_Pose_t *pose, const MPU6050_HandleTypeDef *mpu);

#endif
