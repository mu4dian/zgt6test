#include "bsp_motor.h"

static uint32_t _get_pwm_max(TIM_HandleTypeDef *htim, uint32_t channel)
{
    // 取定时器的ARR最大值，即PWM最大计数
    return __HAL_TIM_GET_AUTORELOAD(htim);
}

void Motor_Init(Motor_HandleTypeDef *hmotor)
{
    // 1. 启动PWM输出
    HAL_TIM_PWM_Start(hmotor->htim, hmotor->channel);
    // 2. 使能STBY
    if (hmotor->STBY_Port != NULL)
        HAL_GPIO_WritePin(hmotor->STBY_Port, hmotor->STBY_Pin, GPIO_PIN_SET);
    // 3. 记录PWM最大值（用于占空比百分比计算）
    hmotor->pwm_max = _get_pwm_max(hmotor->htim, hmotor->channel);
    // 4. 默认停止
    Motor_Stop(hmotor);
}

void Motor_SetSpeed(Motor_HandleTypeDef *hmotor, int16_t speed)
{
    if (!hmotor || !hmotor->htim) return;
    // 安全限幅
    if (speed > 1000)  speed = 1000;
    if (speed < -1000) speed = -1000;

    // 方向控制
    if (speed > 0) {
        HAL_GPIO_WritePin(hmotor->IN1_Port, hmotor->IN1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(hmotor->IN2_Port, hmotor->IN2_Pin, GPIO_PIN_RESET);
    } else if (speed < 0) {
        HAL_GPIO_WritePin(hmotor->IN1_Port, hmotor->IN1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(hmotor->IN2_Port, hmotor->IN2_Pin, GPIO_PIN_SET);
        speed = -speed;
    } else {
        Motor_Stop(hmotor);
        return;
    }

    // 占空比转换（-1000~1000映射到0~pwm_max）
    uint32_t pulse = (hmotor->pwm_max * speed) / 1000;
    __HAL_TIM_SET_COMPARE(hmotor->htim, hmotor->channel, pulse);
}

void Motor_Stop(Motor_HandleTypeDef *hmotor)
{
    // 断开IN1/IN2，停止
    HAL_GPIO_WritePin(hmotor->IN1_Port, hmotor->IN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(hmotor->IN2_Port, hmotor->IN2_Pin, GPIO_PIN_RESET);
    // PWM输出置零
    __HAL_TIM_SET_COMPARE(hmotor->htim, hmotor->channel, 0);
}
