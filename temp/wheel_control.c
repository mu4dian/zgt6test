// #include "wheel_control.h"
//
// // 初始化轮子控制器
// void Wheel_Init(WheelController_TypeDef *controller,
//                 Motor_HandleTypeDef *motor,
//                 Encoder_HandleTypeDef *encoder,
//                 float kp, float ki, float kd)
// {
//     // 初始化速度控制器
//     WheelSpeed_Init(&controller->speed_controller, motor, encoder, kp, ki, kd);
//
//     // 设置初始状态和模式
//     controller->state = WHEEL_DISABLED;
//     controller->mode = WHEEL_MODE_SPEED;
// }
//
// // 启用轮子
// void Wheel_Enable(WheelController_TypeDef *controller)
// {
//     controller->state = WHEEL_ENABLED;
//     // 这里可以添加其他启用逻辑，如自检等
// }
//
// // 禁用轮子
// void Wheel_Disable(WheelController_TypeDef *controller)
// {
//     controller->state = WHEEL_DISABLED;
//     Wheel_Stop(controller);
// }
//
// // 设置速度
// void Wheel_SetSpeed(WheelController_TypeDef *controller, float speed)
// {
//     if (controller->state == WHEEL_ENABLED && controller->mode == WHEEL_MODE_SPEED)
//     {
//         WheelSpeed_SetTarget(&controller->speed_controller, speed);
//     }
// }
//
// // 更新轮子控制（需要定期调用）
// void Wheel_Update(WheelController_TypeDef *controller)
// {
//     if (controller->state == WHEEL_ENABLED)
//     {
//         if (controller->mode == WHEEL_MODE_SPEED)
//         {
//             WheelSpeed_Update(&controller->speed_controller);
//         }
//         // 未来可以添加其他模式的更新逻辑
//     }
// }
//
// // 停止轮子
// void Wheel_Stop(WheelController_TypeDef *controller)
// {
//     WheelSpeed_Stop(&controller->speed_controller);
// }
