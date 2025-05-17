#ifndef __BSP_TOF_H__
#define __BSP_TOF_H__
#include "main.h"
#include "VL53L0X.h"
#include "stm32f4xx_hal.h"

typedef struct {
    I2C_HandleTypeDef *hi2c;
    uint8_t io_2v8;    // 1: 2V8模式, 0: 1V8模式
    uint8_t is_init;   // 传感器初始化成功标志
} TOF_HandleTypeDef;

// 用户BSP API
uint8_t TOF_Init(TOF_HandleTypeDef *htof, I2C_HandleTypeDef *hi2c, uint8_t io_2v8);
uint16_t TOF_ReadDistance(TOF_HandleTypeDef *htof);
void TOF_SetAccuracy(TOF_HandleTypeDef *htof, uint8_t mode);  // 0-默认，1-高精度，2-高速，3-远距离

#endif
