#include "bsp_encoder.h"

void Encoder_Init(Encoder_HandleTypeDef *henc)
{
    if (!henc || !henc->htim) return;
    // 开启定时器编码器接口
    HAL_TIM_Encoder_Start(henc->htim, TIM_CHANNEL_ALL);
    // 清零
    __HAL_TIM_SET_COUNTER(henc->htim, 0);
    henc->last_cnt = 0;
    henc->count = 0;
    henc->diff = 0;
    henc->dir = 0;
}

// 编码器采样：定时周期调用（如1ms~10ms/FreeRTOS任务/定时中断）
void Encoder_Update(Encoder_HandleTypeDef *henc)
{
    int16_t cnt_now, diff;
    if (!henc || !henc->htim) return;
    cnt_now = (int16_t)__HAL_TIM_GET_COUNTER(henc->htim);

    diff = cnt_now - henc->last_cnt;

    // 溢出处理（正向/反向）
    if (diff > 32768)       // 定时器溢出反转
        diff -= 65536;
    else if (diff < -32768) // 定时器溢出正转
        diff += 65536;

    henc->diff = diff;
    henc->count += diff;
    henc->last_cnt = cnt_now;

    // 方向判断
    if (diff > 0)       henc->dir =  1;
    else if (diff < 0)  henc->dir = -1;
    else                henc->dir =  0;
}

// 获取累计计数
int32_t Encoder_GetCount(Encoder_HandleTypeDef *henc)
{
    return henc ? henc->count : 0;
}

// 获取最近一次采样的速度（脉冲数，可换算转速）
int16_t Encoder_GetSpeed(Encoder_HandleTypeDef *henc)
{
    return henc ? henc->diff : 0;
}

// 编码器归零
void Encoder_Reset(Encoder_HandleTypeDef *henc)
{
    if (!henc || !henc->htim) return;
    __HAL_TIM_SET_COUNTER(henc->htim, 0);
    henc->last_cnt = 0;
    henc->count = 0;
    henc->diff = 0;
    henc->dir = 0;
}
