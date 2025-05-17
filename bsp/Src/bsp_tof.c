// #include "bsp_tof.h"
// #include "stm32f4xx_hal.h"
//
// // VL53L0X寄存器
// #define VL53L0X_REG_SYSRANGE_START       0x00
// #define VL53L0X_REG_RESULT_RANGE_STATUS  0x14
// #define VL53L0X_I2C_DEFAULT_ADDR         0x52
//
// // 启动一次单次测距
// static int VL53L0X_SingleShot(VL53L0X_HandleTypedef *dev)
// {
//     uint8_t cmd = 0x01;
//     return HAL_I2C_Mem_Write(dev->hi2c, dev->addr, VL53L0X_REG_SYSRANGE_START, I2C_MEMADD_SIZE_8BIT, &cmd, 1, 10);
// }
//
// // 读取距离，阻塞直到完成（可适当优化超时）
// int VL53L0X_ReadRangeMM(VL53L0X_HandleTypedef *dev, uint16_t *distance)
// {
//     // 启动一次测距
//     if (VL53L0X_SingleShot(dev) != HAL_OK) return 1;
//     HAL_Delay(30); // 测距典型时长（视模块设置可调整）
//
//     // 跳到距离寄存器
//     uint8_t data[2];
//     if (HAL_I2C_Mem_Read(dev->hi2c, dev->addr, 0x1E, I2C_MEMADD_SIZE_8BIT, data, 2, 10) != HAL_OK) return 2;
//     *distance = ((uint16_t)data[0] << 8) | data[1];
//     // 异常距离判别
//     if (*distance == 65535 || *distance == 8191 || *distance == 0) return 3;
//     return 0;
// }
//
// int VL53L0X_Init(VL53L0X_HandleTypedef *dev, I2C_HandleTypeDef *hi2c, uint8_t addr)
// {
//     dev->hi2c = hi2c;
//     dev->addr = addr;
//     // VL53L0X出厂自带基本配置，大多数模块只需要上电即可测距
//     return 0;
// }
