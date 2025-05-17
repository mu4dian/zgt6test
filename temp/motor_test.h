#ifndef __MOTOR_TEST_H__
#define __MOTOR_TEST_H__

#include "task_motor.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    // PID参数调整函数
    void Motor_AdjustPIDParams(float kp, float ki, float kd);

    // 阶跃响应测试
    void Motor_StepResponseTest(float start_speed, float target_speed, uint32_t duration_ms);

    // 速度扫描测试
    void Motor_SpeedSweepTest(float min_speed, float max_speed, float step, uint32_t step_duration_ms); // 抗干扰能力测试（模拟负载突变）
    void Motor_DisturbanceTest(float base_speed, float disturbance_duration_ms);

    // 低速测试函数
    void Motor_LowSpeedTest(void);

    // 全速度范围测试
    void Motor_SpeedRangeTest(void); // PID参数优化测试
    void Motor_PIDOptimizationTest(void);

    // 低速双向对比测试
    void Motor_LowSpeedBidirectionalTest(void);

#ifdef __cplusplus
}
#endif

#endif // __MOTOR_TEST_H__
