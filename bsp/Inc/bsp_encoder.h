/**
* @file    bsp_encoder.h
 * @brief   编码器BSP头文件，支持定时器编码器模式，测速/计数/方向
 */
#ifndef __BSP_ENCODER_H__
#define __BSP_ENCODER_H__

#include "main.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        TIM_HandleTypeDef *htim;   // 定时器句柄
        int32_t           count;   // 当前总计数
        int16_t           last_cnt;// 上一次的原始CNT值
        int16_t           diff;    // 单次采样差值（可用于测速）
        int8_t            dir;     // 方向: 1正转，-1反转，0静止
    } Encoder_HandleTypeDef;

    // 初始化（开启定时器编码器模式）
    void Encoder_Init(Encoder_HandleTypeDef *henc);
    // 采样（建议定时周期调用）
    void Encoder_Update(Encoder_HandleTypeDef *henc);
    // 获取当前总计数
    int32_t Encoder_GetCount(Encoder_HandleTypeDef *henc);
    // 获取速度（返回上次采样到这次采样之间的脉冲数）
    int16_t Encoder_GetSpeed(Encoder_HandleTypeDef *henc);
    // 归零
    void Encoder_Reset(Encoder_HandleTypeDef *henc);

#ifdef __cplusplus
}
#endif

#endif // __BSP_ENCODER_H__
