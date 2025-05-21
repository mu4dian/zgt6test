#include "app_imu_pose.h"
#include <math.h>

// 互补滤波参数，建议0.98左右，偏小陀螺易飘，偏大加速度易抖
#define GYRO_RATIO 0.98f

void IMU_Pose_Init(IMU_Pose_t *pose, float dt) {
    pose->roll = pose->pitch = pose->yaw = 0.0f;
    pose->gx_bias = pose->gy_bias = pose->gz_bias = 0.0f;
    pose->dt = dt;
}

// 最简单的互补滤波+陀螺零偏校准（你可以先静止测几百次平均做零偏）
void IMU_Pose_Update(IMU_Pose_t *pose, const MPU6050_HandleTypeDef *mpu) {
    float ax, ay, az, gx, gy, gz;
    MPU6050_GetAccelGyro(mpu, &ax, &ay, &az, &gx, &gy, &gz);

    // 陀螺减去零偏
    gx -= pose->gx_bias;
    gy -= pose->gy_bias;
    gz -= pose->gz_bias;

    // 积分陀螺得到欧拉角（roll, pitch, yaw）
    pose->roll  += gx * pose->dt;  // 单位：度
    pose->pitch += gy * pose->dt;
    pose->yaw   += gz * pose->dt;

    // 用加速度校正roll和pitch
    float roll_acc  = atan2f(ay, az) * 180.0f / 3.1415926f;
    float pitch_acc = atan2f(-ax, sqrtf(ay * ay + az * az)) * 180.0f / 3.1415926f;

    pose->roll  = GYRO_RATIO * pose->roll  + (1.0f - GYRO_RATIO) * roll_acc;
    pose->pitch = GYRO_RATIO * pose->pitch + (1.0f - GYRO_RATIO) * pitch_acc;
    // Yaw只能靠陀螺积分，长期会漂移（除非用磁力计或视觉辅助）
}
