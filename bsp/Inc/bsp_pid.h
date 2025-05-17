#ifndef __BSP_PID_H__
#define __BSP_PID_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "pid.h"
#include "bsp_encoder.h"
#include "bsp_motor.h" // 速度PID控制器结构体
    typedef struct
    {
        Motor_HandleTypeDef *motor;     // 电机句柄
        Encoder_HandleTypeDef *encoder; // 编码器句柄
        PID_TypeDef pid;                // PID控制器
        float current_speed;            // 当前速度
        float target_speed;             // 目标速度
        int8_t motor_direction;         // 电机方向修正因子 (1: 正向, -1: 反向)
        int8_t encoder_direction;       // 编码器方向修正因子 (1: 正向, -1: 反向)
    } WheelSpeedController_TypeDef;

    // 初始化轮子速度控制器
    void WheelSpeed_Init(WheelSpeedController_TypeDef *controller,
                         Motor_HandleTypeDef *motor,
                         Encoder_HandleTypeDef *encoder,
                         float kp, float ki, float kd);

    // 设置目标速度
    void WheelSpeed_SetTarget(WheelSpeedController_TypeDef *controller, float target_speed);

    // 计算并更新电机输出
    void WheelSpeed_Update(WheelSpeedController_TypeDef *controller); // 停止轮子
    void WheelSpeed_Stop(WheelSpeedController_TypeDef *controller);

    // 设置电机方向
    void WheelSpeed_SetMotorDirection(int8_t direction);

    // 设置编码器方向
    void WheelSpeed_SetEncoderDirection(int8_t direction);

    // 获取当前电机方向
    int8_t WheelSpeed_GetMotorDirection(void); // 获取当前编码器方向
    int8_t WheelSpeed_GetEncoderDirection(void);

    // 设置控制器特定的电机方向
    void WheelSpeed_SetControllerMotorDirection(WheelSpeedController_TypeDef *controller, int8_t direction);

    // 设置控制器特定的编码器方向
    void WheelSpeed_SetControllerEncoderDirection(WheelSpeedController_TypeDef *controller, int8_t direction);

    // 获取控制器特定的电机方向
    int8_t WheelSpeed_GetControllerMotorDirection(WheelSpeedController_TypeDef *controller);

    // 获取控制器特定的编码器方向
    int8_t WheelSpeed_GetControllerEncoderDirection(WheelSpeedController_TypeDef *controller);

#ifdef __cplusplus
}
#endif

#endif // __BSP_PID_H__