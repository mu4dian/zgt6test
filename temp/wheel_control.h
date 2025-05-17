// #ifndef __WHEEL_CONTROL_H__
// #define __WHEEL_CONTROL_H__
//
// #ifdef __cplusplus
// extern "C"
// {
// #endif
//
// #include "bsp_pid.h"
//
//     // PID参数 - 这些值需要根据实际情况调整
// #define MOTOR_PID_KP 40.0f  // 比例系数 - 增大比例系数以提高响应速度
// #define MOTOR_PID_KI 2.0f  // 积分系数 - 增大积分系数以消除稳态误差
// #define MOTOR_PID_KD 0.001f // 微分系数 - 减小微分系数以降低抖动
//
//     // 控制周期 (ms)
// #define PID_CONTROL_PERIOD 10
//
//
//     // 可以添加更多高级轮子控制功能，比如位置控制、轮组协调等
//
//     // 轮子启用/禁用状态
//     typedef enum
//     {
//         WHEEL_DISABLED = 0,
//         WHEEL_ENABLED
//     } WheelState_t;
//
//     // 轮子控制模式
//     typedef enum
//     {
//         WHEEL_MODE_SPEED = 0, // 速度控制模式
//         WHEEL_MODE_POSITION   // 位置控制模式（如果实现）
//     } WheelControlMode_t;
//
//     // 轮子控制器结构体
//     typedef struct
//     {
//         WheelSpeedController_TypeDef speed_controller; // 速度控制器
//         WheelState_t state;                            // 启用/禁用状态
//         WheelControlMode_t mode;                       // 控制模式
//     } WheelController_TypeDef;
//
//     // 初始化轮子控制器
//     void Wheel_Init(WheelController_TypeDef *controller,
//                     Motor_HandleTypeDef *motor,
//                     Encoder_HandleTypeDef *encoder,
//                     float kp, float ki, float kd);
//
//     // 启用轮子
//     void Wheel_Enable(WheelController_TypeDef *controller);
//
//     // 禁用轮子
//     void Wheel_Disable(WheelController_TypeDef *controller);
//
//     // 设置速度
//     void Wheel_SetSpeed(WheelController_TypeDef *controller, float speed);
//
//     // 更新轮子控制（需要定期调用）
//     void Wheel_Update(WheelController_TypeDef *controller);
//
//     // 停止轮子
//     void Wheel_Stop(WheelController_TypeDef *controller);
//
// #ifdef __cplusplus
// }
// #endif
//
// #endif // __WHEEL_CONTROL_H__