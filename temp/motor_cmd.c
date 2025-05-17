// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "cmsis_os.h"
// #include "task_motor.h"
// #include "motor_test.h"
// #include "bsp_usart.h"
// #include "usart.h"
//
// #define MAX_CMD_LENGTH 64
//
// // 解析命令的函数
// void ParseCommand(char *cmd)
// {
//     char *token;
//     char *rest = cmd;
//
//     // 获取第一个令牌（命令名称）
//     token = strtok_r(rest, " ", &rest);
//
//     // 如果没有命令，返回
//     if (!token)
//     {
//         return;
//     }
//
//     // 处理不同的命令
//     if (strcmp(token, "speed") == 0)
//     {
//         // 设置速度命令: speed <value>
//         token = strtok_r(rest, " ", &rest);
//         if (token)
//         {
//             float speed = atof(token);
//             Chassis_Motor_SetSpeed(speed);
//         }
//         else
//         {
//             printf("Usage: speed <value>\r\n");
//         }
//     }
//     else if (strcmp(token, "stop") == 0)
//     {
//         // 停止电机
//         Chassis_Motor_Stop();
//     }
//     else if (strcmp(token, "pid") == 0)
//     {
//         // 设置PID参数: pid <kp> <ki> <kd>
//         float kp, ki, kd;
//         token = strtok_r(rest, " ", &rest);
//         if (token)
//         {
//             kp = atof(token);
//             token = strtok_r(rest, " ", &rest);
//             if (token)
//             {
//                 ki = atof(token);
//                 token = strtok_r(rest, " ", &rest);
//                 if (token)
//                 {
//                     kd = atof(token);
//                     Motor_AdjustPIDParams(kp, ki, kd);
//                 }
//                 else
//                 {
//                     printf("Usage: pid <kp> <ki> <kd>\r\n");
//                 }
//             }
//             else
//             {
//                 printf("Usage: pid <kp> <ki> <kd>\r\n");
//             }
//         }
//         else
//         {
//             printf("Usage: pid <kp> <ki> <kd>\r\n");
//         }
//     }
//     else if (strcmp(token, "step") == 0)
//     {
//         // 阶跃响应测试: step <start_speed> <target_speed> <duration_ms>
//         float start_speed, target_speed;
//         uint32_t duration;
//
//         token = strtok_r(rest, " ", &rest);
//         if (token)
//         {
//             start_speed = atof(token);
//             token = strtok_r(rest, " ", &rest);
//             if (token)
//             {
//                 target_speed = atof(token);
//                 token = strtok_r(rest, " ", &rest);
//                 if (token)
//                 {
//                     duration = (uint32_t)atoi(token);
//                     Motor_StepResponseTest(start_speed, target_speed, duration);
//                 }
//                 else
//                 {
//                     printf("Usage: step <start_speed> <target_speed> <duration_ms>\r\n");
//                 }
//             }
//             else
//             {
//                 printf("Usage: step <start_speed> <target_speed> <duration_ms>\r\n");
//             }
//         }
//         else
//         {
//             printf("Usage: step <start_speed> <target_speed> <duration_ms>\r\n");
//         }
//     }
//     else if (strcmp(token, "sweep") == 0)
//     {
//         // 速度扫描测试: sweep <min_speed> <max_speed> <step> <step_duration>
//         float min_speed, max_speed, step;
//         uint32_t step_duration;
//
//         token = strtok_r(rest, " ", &rest);
//         if (token)
//         {
//             min_speed = atof(token);
//             token = strtok_r(rest, " ", &rest);
//             if (token)
//             {
//                 max_speed = atof(token);
//                 token = strtok_r(rest, " ", &rest);
//                 if (token)
//                 {
//                     step = atof(token);
//                     token = strtok_r(rest, " ", &rest);
//                     if (token)
//                     {
//                         step_duration = (uint32_t)atoi(token);
//                         Motor_SpeedSweepTest(min_speed, max_speed, step, step_duration);
//                     }
//                     else
//                     {
//                         printf("Usage: sweep <min_speed> <max_speed> <step> <step_duration>\r\n");
//                     }
//                 }
//                 else
//                 {
//                     printf("Usage: sweep <min_speed> <max_speed> <step> <step_duration>\r\n");
//                 }
//             }
//             else
//             {
//                 printf("Usage: sweep <min_speed> <max_speed> <step> <step_duration>\r\n");
//             }
//         }
//         else
//         {
//             printf("Usage: sweep <min_speed> <max_speed> <step> <step_duration>\r\n");
//         }
//     }
//     else if (strcmp(token, "disturb") == 0)
//     {
//         // 干扰测试: disturb <base_speed> <duration_ms>
//         float base_speed;
//         uint32_t duration;
//
//         token = strtok_r(rest, " ", &rest);
//         if (token)
//         {
//             base_speed = atof(token);
//             token = strtok_r(rest, " ", &rest);
//             if (token)
//             {
//                 duration = (uint32_t)atoi(token);
//                 Motor_DisturbanceTest(base_speed, duration);
//             }
//             else
//             {
//                 printf("Usage: disturb <base_speed> <duration_ms>\r\n");
//             }
//         }
//         else
//         {
//             printf("Usage: disturb <base_speed> <duration_ms>\r\n");
//         }
//     }
//     else if (strcmp(token, "status") == 0)
//     {
//         // 打印当前状态
//         printf("Current Status:\r\n");
//         printf("- Target Speed: %.2f\r\n", wheelController.target_speed);
//         printf("- Current Speed: %.2f\r\n", wheelController.current_speed);
//         printf("- PID Output: %.2f\r\n", wheelController.pid.output);
//         printf("- PID Parameters: Kp=%.2f, Ki=%.2f, Kd=%.2f\r\n",
//                wheelController.pid.kp, wheelController.pid.ki, wheelController.pid.kd);
//     }
//     else if (strcmp(token, "lowspeed") == 0)
//     {
//         // 运行低速测试
//         printf("Running low speed test...\r\n");
//         Motor_LowSpeedTest();
//     }
//     else if (strcmp(token, "speedrange") == 0)
//     {
//         // 运行全速度范围测试
//         printf("Running speed range test...\r\n");
//         Motor_SpeedRangeTest();
//     }
//     else if (strcmp(token, "pidopt") == 0)
//     {
//         // 运行PID参数优化测试
//         printf("Running PID optimization test...\r\n");
//         Motor_PIDOptimizationTest();
//     }
//     else if (strcmp(token, "bidirect") == 0)
//     {
//         // 运行双向低速对比测试
//         printf("Running bidirectional low speed test...\r\n");
//         Motor_LowSpeedBidirectionalTest();
//     }
//     else if (strcmp(token, "motordir") == 0)
//     {
//         // 设置电机方向: motordir <1|-1>
//         token = strtok_r(rest, " ", &rest);
//         if (token)
//         {
//             int dir = atoi(token);
//             if (dir == 1 || dir == -1)
//             {
//                 WheelSpeed_SetMotorDirection(dir);
//                 printf("Motor direction set to: %d\r\n", dir);
//             }
//             else
//             {
//                 printf("Invalid direction. Use 1 for normal or -1 for reversed\r\n");
//             }
//         }
//         else
//         {
//             // 显示当前方向
//             int8_t current_dir = WheelSpeed_GetMotorDirection();
//             printf("Current motor direction: %d\r\n", current_dir);
//             printf("Usage: motordir <1|-1>\r\n");
//         }
//     }
//     else if (strcmp(token, "encoderdir") == 0)
//     {
//         // 设置编码器方向: encoderdir <1|-1>
//         token = strtok_r(rest, " ", &rest);
//         if (token)
//         {
//             int dir = atoi(token);
//             if (dir == 1 || dir == -1)
//             {
//                 WheelSpeed_SetEncoderDirection(dir);
//                 printf("Encoder direction set to: %d\r\n", dir);
//             }
//             else
//             {
//                 printf("Invalid direction. Use 1 for normal or -1 for reversed\r\n");
//             }
//         }
//         else
//         {
//             // 显示当前方向
//             int8_t current_dir = WheelSpeed_GetEncoderDirection();
//             printf("Current encoder direction: %d\r\n", current_dir);
//             printf("Usage: encoderdir <1|-1>\r\n");
//         }
//     }
//     else if (strcmp(token, "help") == 0)
//     {
//         // 显示帮助信息
//         printf("Available commands:\r\n");
//         printf("- speed <value> : Set motor speed\r\n");
//         printf("- stop : Stop the motor\r\n");
//         printf("- pid <kp> <ki> <kd> : Set PID parameters\r\n");
//         printf("- step <start_speed> <target_speed> <duration_ms> : Run step response test\r\n");
//         printf("- sweep <min_speed> <max_speed> <step> <step_duration> : Run speed sweep test\r\n");
//         printf("- disturb <base_speed> <duration_ms> : Run disturbance rejection test\r\n");
//         printf("- lowspeed : Run low speed stability test\r\n");
//         printf("- speedrange : Run full speed range test\r\n");
//         printf("- pidopt : Run PID parameter optimization test\r\n");
//         printf("- bidirect : Run bidirectional low speed comparison test\r\n");
//         printf("- motordir <1|-1> : Set/get motor direction (1=normal, -1=reversed)\r\n");
//         printf("- encoderdir <1|-1> : Set/get encoder direction (1=normal, -1=reversed)\r\n");
//         printf("- status : Show current motor status\r\n");
//         printf("- help : Show this help message\r\n");
//     }
//     else
//     {
//         printf("Unknown command: %s\r\n", token);
//         printf("Type 'help' for available commands\r\n");
//     }
// }
//
// // 串口命令处理任务
// void UartCommandTask(void *argument)
// {
//     char cmd_buffer[MAX_CMD_LENGTH];
//     uint16_t index = 0;
//     char received_char;
//
//     // 初始化电机PID控制
//     Chassis_Motor_PIDControl_Init();
//
//     // 显示欢迎信息
//     printf("\r\n============================\r\n");
//     printf("Motor PID Control Interface\r\n");
//     printf("Type 'help' for available commands\r\n");
//     printf("============================\r\n");
//
//     // 主循环
//     for (;;)
//     {
//         // 从串口接收一个字符
//         if (HAL_UART_Receive(&huart1, (uint8_t *)&received_char, 1, 10) == HAL_OK)
//         {
//             // 回显字符
//             HAL_UART_Transmit(&huart1, (uint8_t *)&received_char, 1, 10);
//
//             // 处理退格键
//             if (received_char == '\b' || received_char == 127)
//             {
//                 if (index > 0)
//                 {
//                     index--;
//                     // 擦除字符（退格，空格，再退格）
//                     HAL_UART_Transmit(&huart1, (uint8_t *)"\b \b", 3, 10);
//                 }
//             }
//             // 处理回车键
//             else if (received_char == '\r' || received_char == '\n')
//             {
//                 // 添加字符串结束符
//                 cmd_buffer[index] = '\0';
//
//                 // 输出新行
//                 printf("\r\n");
//
//                 // 处理命令
//                 if (index > 0)
//                 {
//                     ParseCommand(cmd_buffer);
//                 }
//
//                 // 重置缓冲区
//                 index = 0;
//
//                 // 显示新的命令提示符
//                 printf("\r\n> ");
//             }
//             // 其他普通字符
//             else if (index < MAX_CMD_LENGTH - 1)
//             {
//                 cmd_buffer[index++] = received_char;
//             }
//         }
//
//         // 让出CPU时间
//         osDelay(1);
//     }
// }
//
// // 创建命令行任务
// void StartCommandInterface(void)
// {
//     // 创建命令行任务
//     osThreadAttr_t cmdTaskAttr = {
//         .name = "UartCmd",
//         .stack_size = 1024,
//         .priority = (osPriority_t)osPriorityNormal,
//     };
//     osThreadNew(UartCommandTask, NULL, &cmdTaskAttr);
//
//     printf("Command interface started\r\n");
// }
