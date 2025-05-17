#ifndef __PID_H__
#define __PID_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

    // PID控制器结构体
    typedef struct
    {
        float kp; // 比例系数
        float ki; // 积分系数
        float kd; // 微分系数

        float target;      // 目标值
        float error;       // 当前误差
        float last_error;  // 上次误差
        float error_sum;   // 误差积分项
        float error_delta; // 误差微分项

        float output;     // 输出值
        float output_max; // 输出限幅最大值
        float output_min; // 输出限幅最小值

        float integral_limit; // 积分限幅
    } PID_TypeDef;

    // PID初始化
    void PID_Init(PID_TypeDef *pid, float kp, float ki, float kd, float output_max, float output_min, float integral_limit);

    // 设置PID参数
    void PID_SetParams(PID_TypeDef *pid, float kp, float ki, float kd);

    // 设置PID输出限幅
    void PID_SetOutputLimit(PID_TypeDef *pid, float max, float min);

    // 设置PID积分限幅
    void PID_SetIntegralLimit(PID_TypeDef *pid, float limit);

    // 设置目标值
    void PID_SetTarget(PID_TypeDef *pid, float target);

    // 计算PID输出
    float PID_Calculate(PID_TypeDef *pid, float current);

    // 重置PID状态
    void PID_Reset(PID_TypeDef *pid);

#ifdef __cplusplus
}
#endif

#endif // __PID_H__