#include "chassis_app.h"
#include <math.h>
#include <stdlib.h> // fabsf

// ------- 底盘参数 -------
#define WHEEL_BASE       0.17f     // 轮距(m)
#define DELTA_T          0.02f     // 控制周期(秒)
#define MAX_WHEEL_SPEED  1.0f      // 电机最大线速度(m/s) ← 你要根据电机实测填对！

static float rotate_accumulate = 0.0f;
static float rotate_target = 0.0f;
static float rotate_direction = 1.0f;
static float rotate_wheel_speed = 0.0f;
static uint8_t rotating = 0;

// 归一化，将速度(m/s)转换到1-100范围
static float Speed_Normalize(float speed)
{
    // 限幅
    if (speed >  MAX_WHEEL_SPEED)  speed =  MAX_WHEEL_SPEED;
    if (speed < -MAX_WHEEL_SPEED)  speed = -MAX_WHEEL_SPEED;
    // 映射到[-100, 100]
    return (speed / MAX_WHEEL_SPEED) * 100.0f;
}

void Chassis_RunCircle(float speed, float radius)
{
    float v = speed;
    float w = speed / radius;

    float lf = v - w * (WHEEL_BASE / 2);
    float lb = lf;
    float rf = v + w * (WHEEL_BASE / 2);
    float rb = rf;

    // 输出前归一化
    Chassis_Motor_SetSpeed(
        Speed_Normalize(lf),
        Speed_Normalize(lb),
        Speed_Normalize(rf),
        Speed_Normalize(rb)
    );
}

uint8_t Chassis_RotateInPlace(float angle_rad, float rotate_speed)
{
    if (!rotating) {
        rotate_target = fabsf(angle_rad);
        rotate_direction = (angle_rad >= 0.0f) ? 1.0f : -1.0f;
        rotate_wheel_speed = fabsf(rotate_speed);
        rotate_accumulate = 0.0f;
        rotating = 1;
    }

    if (rotate_accumulate < rotate_target) {
        float v = rotate_wheel_speed * rotate_direction;
        Chassis_Motor_SetSpeed(
            Speed_Normalize(v),
            Speed_Normalize(v),
            Speed_Normalize(-v),
            Speed_Normalize(-v)
        );
        float w = 2.0f * rotate_wheel_speed / WHEEL_BASE;
        rotate_accumulate += fabsf(w) * DELTA_T;
        return 1;
    } else {
        Chassis_Motor_SetSpeed(0, 0, 0, 0);
        rotating = 0;
        return 0;
    }
}
