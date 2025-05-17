#include "bsp_tof.h"

// 初始化 ToF 传感器
uint8_t TOF_Init(TOF_HandleTypeDef *htof, I2C_HandleTypeDef *hi2c, uint8_t io_2v8)
{
    htof->hi2c = hi2c;
    htof->io_2v8 = io_2v8;
    htof->is_init = 0;

    // 调用VL53L0X库的初始化
    if (initVL53L0X(io_2v8, hi2c)) {
        htof->is_init = 1;
        return 1;
    }
    return 0;
}

// 读取距离（单位mm）
uint16_t TOF_ReadDistance(TOF_HandleTypeDef *htof)
{
    if (!htof->is_init) return 0xFFFF;
    return readRangeSingleMillimeters(NULL);
}

/**
 * 设置测距模式
 * mode: 0-默认，1-高精度，2-高速，3-远距离
 */
void TOF_SetAccuracy(TOF_HandleTypeDef *htof, uint8_t mode)
{
    if (!htof->is_init) return;

    switch(mode) {
        case 1: // 高精度
            setMeasurementTimingBudget(200 * 1000UL); // 200ms
        break;
        case 2: // 高速
            setMeasurementTimingBudget(20 * 1000UL); // 20ms
        break;
        case 3: // 远距离
            setSignalRateLimit(0.1f);
        setVcselPulsePeriod(VcselPeriodPreRange, 18);
        setVcselPulsePeriod(VcselPeriodFinalRange, 14);
        break;
        default: // 默认
            setSignalRateLimit(0.25f);
        setVcselPulsePeriod(VcselPeriodPreRange, 14);
        setVcselPulsePeriod(VcselPeriodFinalRange, 10);
        setMeasurementTimingBudget(33 * 1000UL);
        break;
    }
}
