#ifndef __BSP_IRTRACKER_H__
#define __BSP_IRTRACKER_H__

#include "main.h" // 记得这里要包含HAL头文件

#define IRTRACKER_CHANNEL_NUM 8

typedef struct {
    uint8_t value[IRTRACKER_CHANNEL_NUM]; // 每个红外检测值（0=黑线, 1=白底，反之也行，看电路）
} IRTracker_Data_t;

// 初始化
void IRTracker_Init(void);

// 采集一次红外数据
void IRTracker_Read(IRTracker_Data_t *data);

#endif // __BSP_IRTRACKER_H__
