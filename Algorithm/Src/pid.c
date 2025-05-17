#include "pid.h"

// PID初始化
void PID_Init(PID_TypeDef *pid, float kp, float ki, float kd, float output_max, float output_min, float integral_limit)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->output_max = output_max;
    pid->output_min = output_min;
    pid->integral_limit = integral_limit;

    // 初始化其他参数
    pid->target = 0;
    pid->error = 0;
    pid->last_error = 0;
    pid->error_sum = 0;
    pid->error_delta = 0;
    pid->output = 0;
}

// 设置PID参数
void PID_SetParams(PID_TypeDef *pid, float kp, float ki, float kd)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
}

// 设置PID输出限幅
void PID_SetOutputLimit(PID_TypeDef *pid, float max, float min)
{
    pid->output_max = max;
    pid->output_min = min;
}

// 设置PID积分限幅
void PID_SetIntegralLimit(PID_TypeDef *pid, float limit)
{
    pid->integral_limit = limit;
}

// 设置目标值
void PID_SetTarget(PID_TypeDef *pid, float target)
{
    pid->target = target;
}

// 计算PID输出
float PID_Calculate(PID_TypeDef *pid, float current)
{
    // 计算误差
    pid->error = pid->target - current;

    // 计算误差微分
    pid->error_delta = pid->error - pid->last_error;

    // 计算误差积分并进行积分限幅
    pid->error_sum += pid->error;
    if (pid->error_sum > pid->integral_limit)
    {
        pid->error_sum = pid->integral_limit;
    }
    else if (pid->error_sum < -pid->integral_limit)
    {
        pid->error_sum = -pid->integral_limit;
    }

    // 计算PID输出
    pid->output = pid->kp * pid->error + pid->ki * pid->error_sum + pid->kd * pid->error_delta;

    // 输出限幅
    if (pid->output > pid->output_max)
    {
        pid->output = pid->output_max;
    }
    else if (pid->output < pid->output_min)
    {
        pid->output = pid->output_min;
    }

    // 更新上次误差
    pid->last_error = pid->error;

    return pid->output;
}

// 重置PID状态
void PID_Reset(PID_TypeDef *pid)
{
    pid->error = 0;
    pid->last_error = 0;
    pid->error_sum = 0;
    pid->error_delta = 0;
    pid->output = 0;
}