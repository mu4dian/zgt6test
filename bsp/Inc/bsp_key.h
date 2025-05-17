#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__

#include "main.h"
#include "board_config.h"

// 按键ID枚举
typedef enum {
    KEY0 = 0,
    KEY1,
    KEY2,
    KEY3,
    KEY4,
} KeyName_t;

// 按键状态
typedef enum {
    KEY_RELEASE = 0,
    KEY_PRESS
} KeyStatus_t;

// 按键初始化（占位，CubeMX已自动初始化，可扩展）
void KEY_Init(void);

// 获取某个按键的当前状态
KeyStatus_t KEY_GetStatus(KeyName_t key);

#endif // __BSP_KEY_H__
