#include "bsp_buzzer.h"

// 外部声明定时器
extern TIM_HandleTypeDef BUZZER_TIM;

// 初始化函数（CubeMX已经生成PWM相关，不用多管）
void Buzzer_Init(void) {
    // 如果CubeMX里没Start PWM，可以加这句
    HAL_TIM_PWM_Start(&BUZZER_TIM, BUZZER_CHANNEL);
}

// 设置蜂鸣器输出频率
void Buzzer_On(uint32_t freq_hz) {
    // 根据目标频率，计算ARR和PSC
    uint32_t tim_clk = HAL_RCC_GetPCLK1Freq(); // TIM2一般挂在APB1
    uint32_t psc = 0, arr = 0;
    // 计算arr和psc（简易版，细节可优化）
    arr = tim_clk / (freq_hz * 100) - 1;
    psc = 99;
    BUZZER_TIM.Instance->PSC = psc;
    BUZZER_TIM.Instance->ARR = arr;
    BUZZER_TIM.Instance->CCR1 = (arr + 1) / 2;  // 50%占空比

    // 更新
    HAL_TIM_PWM_Start(&BUZZER_TIM, BUZZER_CHANNEL);
}

// 关闭蜂鸣器（PWM输出0%）
void Buzzer_Off(void) {
    __HAL_TIM_SET_COMPARE(&BUZZER_TIM, BUZZER_CHANNEL, 0); // 占空比0
    HAL_TIM_PWM_Stop(&BUZZER_TIM, BUZZER_CHANNEL); // 如需完全关断
}
