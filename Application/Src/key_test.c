#include "key_test.h"
#include "bsp_key.h"
#include <stdio.h>

// 实时监测所有按键
void Key_Test_Task(void)
{
    static uint8_t key_last[KEY_NUM] = {0};
    for (int i = 0; i < KEY_NUM; i++) {
        KeyStatus_t curr = KEY_GetStatus((KeyName_t)i);
        if (curr == KEY_PRESS && key_last[i] == 0) {
            printf("KEY%d 按下\r\n", i);
            key_last[i] = 1;
        }
        if (curr == KEY_RELEASE && key_last[i] == 1) {
            printf("KEY%d 松开\r\n", i);
            key_last[i] = 0;
        }
    }
}

// main() while(1)内调用
/*
while (1)
{
    Key_Test_Task();
    HAL_Delay(10); // 10ms轮询，防止刷屏
}
*/
