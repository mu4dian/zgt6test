#ifndef __BSP_MOTOR_H__
#define __BSP_MOTOR_H__

#include "main.h"
#include <stdint.h>
#include "tim.h"
#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        TIM_HandleTypeDef *htim;
        uint32_t           channel; // 例：TIM_CHANNEL_1
        GPIO_TypeDef      *IN1_Port;
        uint16_t           IN1_Pin;
        GPIO_TypeDef      *IN2_Port;
        uint16_t           IN2_Pin;
        GPIO_TypeDef      *STBY_Port; // 如果不用STBY可为NULL
        uint16_t           STBY_Pin;
        uint32_t           pwm_max;  // PWM最大值（自动推断，也可手动指定）
    } Motor_HandleTypeDef;

    typedef enum {
        MOTOR_STOP = 0,
        MOTOR_FORWARD,
        MOTOR_BACKWARD
    } Motor_Direction_t;

    void Motor_Init(Motor_HandleTypeDef *hmotor);
    void Motor_SetSpeed(Motor_HandleTypeDef *hmotor, int16_t speed); // -1000~1000
    void Motor_Stop(Motor_HandleTypeDef *hmotor);

#ifdef __cplusplus
}
#endif

#endif
