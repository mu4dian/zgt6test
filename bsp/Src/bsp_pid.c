#include "bsp_pid.h"

// 初始化轮子速度控制器
void WheelSpeed_Init(WheelSpeedController_TypeDef *controller,
                     Motor_HandleTypeDef *motor,
                     Encoder_HandleTypeDef *encoder,
                     float kp, float ki, float kd)
{
    controller->motor = motor;
    controller->encoder = encoder;

    // 初始化电机和编码器
    Motor_Init(motor);
    Encoder_Init(encoder);

    // 初始化PID控制器，输出限幅为电机驱动的最大值(-1000到1000)
    PID_Init(&controller->pid, kp, ki, kd, 1000, -1000, 500);

    controller->current_speed = 0;
    controller->target_speed = 0;

    // 初始化方向修正因子（默认值）
    controller->motor_direction = 1;    // 默认电机方向为正向
    controller->encoder_direction = -1; // 默认编码器方向为反向（与之前代码保持一致）
}

// 设置目标速度
void WheelSpeed_SetTarget(WheelSpeedController_TypeDef *controller, float target_speed)
{
    controller->target_speed = target_speed;
    PID_SetTarget(&controller->pid, target_speed);
}

// 电机和编码器方向控制
// 这些变量用于控制电机输出和编码器读数的方向
static int8_t motor_direction = 1;    // 1: 正向, -1: 反向
static int8_t encoder_direction = -1; // 1: 正向, -1: 反向 (默认是-1因为我们已经在WheelSpeed_Update中反转了编码器方向)

// 设置电机方向
void WheelSpeed_SetMotorDirection(int8_t direction)
{
    motor_direction = (direction >= 0) ? 1 : -1;
}

// 设置编码器方向
void WheelSpeed_SetEncoderDirection(int8_t direction)
{
    encoder_direction = (direction >= 0) ? 1 : -1;
}

// 获取当前电机方向
int8_t WheelSpeed_GetMotorDirection(void)
{
    return motor_direction;
}

// 获取当前编码器方向
int8_t WheelSpeed_GetEncoderDirection(void)
{
    return encoder_direction;
}

// 设置控制器特定的电机方向
void WheelSpeed_SetControllerMotorDirection(WheelSpeedController_TypeDef *controller, int8_t direction)
{
    if (controller != NULL)
    {
        controller->motor_direction = (direction >= 0) ? 1 : -1;
    }
}

// 设置控制器特定的编码器方向
void WheelSpeed_SetControllerEncoderDirection(WheelSpeedController_TypeDef *controller, int8_t direction)
{
    if (controller != NULL)
    {
        controller->encoder_direction = (direction >= 0) ? 1 : -1;
    }
}

// 获取控制器特定的电机方向
int8_t WheelSpeed_GetControllerMotorDirection(WheelSpeedController_TypeDef *controller)
{
    return (controller != NULL) ? controller->motor_direction : 0;
}

// 获取控制器特定的编码器方向
int8_t WheelSpeed_GetControllerEncoderDirection(WheelSpeedController_TypeDef *controller)
{
    return (controller != NULL) ? controller->encoder_direction : 0;
}

// 计算并更新电机输出
void WheelSpeed_Update(WheelSpeedController_TypeDef *controller)
{
    // 更新编码器
    Encoder_Update(controller->encoder);

    // 获取当前速度（应用该控制器的编码器方向因子）
    controller->current_speed = controller->encoder_direction * (float)Encoder_GetSpeed(controller->encoder);

    // 计算PID输出
    float output = PID_Calculate(&controller->pid, controller->current_speed);

    // 更新电机输出（应用该控制器的电机方向因子）
    Motor_SetSpeed(controller->motor, (int16_t)(controller->motor_direction * output));
}

// 停止轮子
void WheelSpeed_Stop(WheelSpeedController_TypeDef *controller)
{
    // 停止电机
    Motor_Stop(controller->motor);

    // 复位PID控制器
    PID_Reset(&controller->pid);
    controller->target_speed = 0;
}