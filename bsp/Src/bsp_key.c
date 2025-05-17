#include "bsp_key.h"

// 内部硬件映射表，自动和KEYx关联
static const GPIO_TypeDef* key_ports[KEY_NUM] = {
    KEY0_GPIO_Port, KEY1_GPIO_Port, KEY2_GPIO_Port, KEY3_GPIO_Port, KEY4_GPIO_Port
};
static const uint16_t key_pins[KEY_NUM] = {
    KEY0_Pin, KEY1_Pin, KEY2_Pin, KEY3_Pin, KEY4_Pin
};

void KEY_Init(void)
{
    // CubeMX初始化GPIO，无需手动配置。此处预留接口做兼容
}

KeyStatus_t KEY_GetStatus(KeyName_t key)
{
    if (key < 0 || key >= KEY_NUM) return KEY_RELEASE;
    return (HAL_GPIO_ReadPin((GPIO_TypeDef *)key_ports[key], key_pins[key]) == KEY_PRESS_LEVEL) ? KEY_PRESS : KEY_RELEASE;
}
