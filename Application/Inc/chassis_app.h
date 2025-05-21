#ifndef __CHASSIS_APP_H
#define __CHASSIS_APP_H

#include <stdint.h>

// 你的底层实现，输入1-100
void Chassis_Motor_SetSpeed(float lf_speed, float lb_speed, float rf_speed, float rb_speed);

// 画圆，参数：线速度(m/s)，半径(m)
void Chassis_RunCircle(float speed, float radius);

// 原地旋转，参数：目标角度(弧度)，轮速度(m/s)。返回值：0完成，1旋转中
uint8_t Chassis_RotateInPlace(float angle_rad, float rotate_speed);

#endif
