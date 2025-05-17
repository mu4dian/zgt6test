//
// Created by mu4di on 25-5-16.
//

#ifndef CHASSIS_H
#define CHASSIS_H
#include "bsp_pid.h"

// PID参数 - 这些值需要根据实际情况调整
#define MOTOR_PID_KP 50.0f  // 比例系数 - 增大比例系数以提高响应速度
#define MOTOR_PID_KI 5.0f  // 积分系数 - 增大积分系数以消除稳态误差
#define MOTOR_PID_KD 0.001f // 微分系数 - 减小微分系数以降低抖动

// 控制周期 (ms)
#define PID_CONTROL_PERIOD 10

// 电机控制相关函数声明
void Chassis_Motor_PIDControl_Init(void);
void Chassis_Motor_SetSpeed(float speed1,float speed2,float speed3,float speed4);
void Chassis_Motor_Stop(void);
float Chassis_Motor_GetCurrentSpeed(void);

// 全局变量声明
extern WheelSpeedController_TypeDef wheelController1;
extern WheelSpeedController_TypeDef wheelController2;
extern WheelSpeedController_TypeDef wheelController3;
extern WheelSpeedController_TypeDef wheelController4;


#endif //CHASSIS_H
