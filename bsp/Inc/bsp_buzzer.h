#ifndef __BSP_BUZZER_H__
#define __BSP_BUZZER_H__

#include "main.h"

// 定义蜂鸣器PWM输出定时器和通道
#define BUZZER_TIM      htim13           // 例：使用TIM2（CubeMX配置好）
#define BUZZER_CHANNEL  TIM_CHANNEL_1   // 例：CH1输出

void Buzzer_Init(void);
void Buzzer_On(uint32_t freq_hz);    // 以freq_hz频率响
void Buzzer_Off(void);

#endif
