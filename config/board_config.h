//
// Created by mu4di on 25-5-17.
//

#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H


// D0~D5 分别为 GPIOD 的 0~5 引脚
#define KEY0_GPIO_Port   GPIOD
#define KEY0_Pin         GPIO_PIN_8

#define KEY1_GPIO_Port   GPIOD
#define KEY1_Pin         GPIO_PIN_5

#define KEY2_GPIO_Port   GPIOD
#define KEY2_Pin         GPIO_PIN_4

#define KEY3_GPIO_Port   GPIOD
#define KEY3_Pin         GPIO_PIN_0

#define KEY4_GPIO_Port   GPIOD
#define KEY4_Pin         GPIO_PIN_1


#define KEY_NUM          5

// 如果你的按键电路为下拉输入，高电平按下，改成 GPIO_PIN_SET
#define KEY_PRESS_LEVEL  GPIO_PIN_RESET  // 通常为低电平按下


#endif //BOARD_CONFIG_H
