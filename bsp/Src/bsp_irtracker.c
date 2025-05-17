#include "bsp_irtracker.h"

// 这里根据你自己的引脚在main.h里定义
#define IR1_GPIO_PORT   GPIOE
#define IR1_GPIO_PIN    GPIO_PIN_0
#define IR2_GPIO_PORT   GPIOE
#define IR2_GPIO_PIN    GPIO_PIN_1
#define IR3_GPIO_PORT   GPIOE
#define IR3_GPIO_PIN    GPIO_PIN_2
#define IR4_GPIO_PORT   GPIOE
#define IR4_GPIO_PIN    GPIO_PIN_3
#define IR5_GPIO_PORT   GPIOE
#define IR5_GPIO_PIN    GPIO_PIN_4
#define IR6_GPIO_PORT   GPIOE
#define IR6_GPIO_PIN    GPIO_PIN_5
#define IR7_GPIO_PORT   GPIOE
#define IR7_GPIO_PIN    GPIO_PIN_6
#define IR8_GPIO_PORT   GPIOC
#define IR8_GPIO_PIN    GPIO_PIN_13

void IRTracker_Init(void)
{
    // CubeMX里配置为GPIO输入即可，这里可以不用写内容
}

void IRTracker_Read(IRTracker_Data_t *data)
{
    data->value[0] = HAL_GPIO_ReadPin(IR1_GPIO_PORT, IR1_GPIO_PIN);
    data->value[1] = HAL_GPIO_ReadPin(IR2_GPIO_PORT, IR2_GPIO_PIN);
    data->value[2] = HAL_GPIO_ReadPin(IR3_GPIO_PORT, IR3_GPIO_PIN);
    data->value[3] = HAL_GPIO_ReadPin(IR4_GPIO_PORT, IR4_GPIO_PIN);
    data->value[4] = HAL_GPIO_ReadPin(IR5_GPIO_PORT, IR5_GPIO_PIN);
    data->value[5] = HAL_GPIO_ReadPin(IR6_GPIO_PORT, IR6_GPIO_PIN);
    data->value[6] = HAL_GPIO_ReadPin(IR7_GPIO_PORT, IR7_GPIO_PIN);
    data->value[7] = HAL_GPIO_ReadPin(IR8_GPIO_PORT, IR8_GPIO_PIN);
}
