// #include "task_motor.h"
// #include <stdio.h>
//
// // PID参数调整函数
// void Motor_AdjustPIDParams(float kp, float ki, float kd)
// {
//     // 获取当前PID控制器
//     PID_TypeDef *pid = &(wheelController.pid);
//
//     // 更新PID参数
//     PID_SetParams(pid, kp, ki, kd);
//
//     printf("PID Parameters adjusted - Kp: %.2f, Ki: %.2f, Kd: %.2f\r\n", kp, ki, kd);
// }
//
// // 阶跃响应测试
// void Motor_StepResponseTest(float start_speed, float target_speed, uint32_t duration_ms)
// {
//     printf("Starting Step Response Test\r\n");
//     printf("Initial Speed: %.2f, Target Speed: %.2f, Duration: %lu ms\r\n",
//            start_speed, target_speed, duration_ms);
//
//     // 设置初始速度
//     Chassis_Motor_SetSpeed(start_speed);
//
//     // 等待系统稳定
//     osDelay(1000);
//
//     // 记录起始时间
//     uint32_t start_time = osKernelGetTickCount();
//
//     // 设置目标速度（阶跃输入）
//     Chassis_Motor_SetSpeed(target_speed);
//
//     // 监测响应过程
//     while ((osKernelGetTickCount() - start_time) < duration_ms)
//     {
//         // 每100ms记录一次数据
//         printf("Time: %lu ms, Speed: %.2f\r\n",
//                osKernelGetTickCount() - start_time,
//                Chassis_Motor_GetCurrentSpeed());
//
//         osDelay(100);
//     }
//
//     printf("Step Response Test Completed\r\n");
// }
//
// // 速度扫描测试
// void Motor_SpeedSweepTest(float min_speed, float max_speed, float step, uint32_t step_duration_ms)
// {
//     printf("Starting Speed Sweep Test\r\n");
//     printf("Speed Range: %.2f to %.2f, Step: %.2f, Step Duration: %lu ms\r\n",
//            min_speed, max_speed, step, step_duration_ms);
//
//     // 从最小速度开始递增
//     for (float speed = min_speed; speed <= max_speed; speed += step)
//     {
//         // 设置当前测试速度
//         Chassis_Motor_SetSpeed(speed);
//
//         // 等待速度稳定
//         osDelay(step_duration_ms); // 记录数据
//         printf("Target Speed: %.2f, Actual Speed: %.2f\r\n",
//                speed, Chassis_Motor_GetCurrentSpeed());
//     }
//
//     // 测试结束后停止电机
//     Chassis_Motor_Stop();
//     printf("Speed Sweep Test Completed\r\n");
// }
//
// // 抗干扰能力测试（模拟负载突变）
// void Motor_DisturbanceTest(float base_speed, float disturbance_duration_ms)
// {
//     printf("Starting Disturbance Rejection Test\r\n");
//     printf("Base Speed: %.2f, Disturbance Duration: %lu ms\r\n",
//            base_speed, disturbance_duration_ms);
//
//     // 设置基础速度并等待稳定
//     Chassis_Motor_SetSpeed(base_speed);
//     osDelay(1000);
//
//     // 记录测试开始时间
//     uint32_t start_time = osKernelGetTickCount();
//
//     // 获取当前PID输出
//     float normal_output = wheelController.pid.output;
//
//     // 模拟干扰（通过直接修改输出值）
//     printf("Applying disturbance...\r\n");
//     // 获取当前PID输出值并增加干扰（这里增加50%作为示例）
//     float disturbed_output = normal_output * 0.5;
//     Chassis_Motor_SetSpeed(disturbed_output); // 直接影响电机速度
//
//     // 记录干扰期间的响应
//     while ((osKernelGetTickCount() - start_time) < disturbance_duration_ms)
//     {
//         printf("Time: %lu ms, Speed: %.2f, PID Output: %.2f\r\n",
//                osKernelGetTickCount() - start_time, Chassis_Motor_GetCurrentSpeed(),
//                wheelController.pid.output);
//
//         osDelay(100);
//     }
//
//     // 恢复正常控制
//     printf("Removing disturbance...\r\n");
//     Chassis_Motor_SetSpeed(base_speed); // 继续监测系统恢复情况
//     start_time = osKernelGetTickCount();
//     while ((osKernelGetTickCount() - start_time) < 2000)
//     {
//         printf("Recovery Time: %lu ms, Speed: %.2f\r\n",
//                osKernelGetTickCount() - start_time,
//                Chassis_Motor_GetCurrentSpeed());
//
//         osDelay(100);
//     }
//
//     printf("Disturbance Rejection Test Completed\r\n");
// }
//
// // 低速测试函数
// // 测试电机在低速区域的控制表现
// void Motor_LowSpeedTest(void)
// {
//     printf("\r\n==== 开始电机低速区域测试 ====\r\n");
//
//     // 低速测试序列
//     const float lowSpeeds[] = {1.0f, 2.0f, 3.0f, 5.0f, 8.0f, 10.0f, 15.0f, 20.0f, 25.0f, 30.0f};
//     const uint32_t testDuration = 3000; // 每个速度测试3秒
//
//     for (int i = 0; i < sizeof(lowSpeeds) / sizeof(lowSpeeds[0]); i++)
//     {
//         float testSpeed = lowSpeeds[i];
//
//         // 设置测试速度
//         printf("\r\n测试低速: %.1f:\r\n", testSpeed);
//         Chassis_Motor_SetSpeed(testSpeed);
//
//         // 等待稳定时间
//         uint32_t startTime = osKernelGetTickCount();
//         while (osKernelGetTickCount() - startTime < testDuration)
//         {
//             // 每500ms打印一次状态
//             osDelay(500);
//             printf("目标: %.2f, 当前: %.2f, 输出: %.2f, 误差: %.2f\r\n",
//                    wheelController.target_speed,
//                    wheelController.current_speed,
//                    wheelController.pid.output,
//                    wheelController.pid.error);
//         }
//     }
//
//     // 测试结束停止电机
//     Chassis_Motor_Stop();
//     printf("\r\n==== 电机低速测试完成 ====\r\n");
// }
//
// // 低速双向对比测试
// // 专门测试电机在正反方向相同速度情况下的表现
// void Motor_LowSpeedBidirectionalTest(void)
// {
//     printf("\r\n==== 开始电机低速双向对比测试 ====\r\n");
//
//     // 测试速度序列
//     const float speeds[] = {5.0f, 10.0f, 15.0f, 20.0f, 25.0f, 30.0f};
//     const uint32_t testDuration = 2000; // 每个速度测试2秒
//
//     for (int i = 0; i < sizeof(speeds) / sizeof(speeds[0]); i++)
//     {
//         float speed = speeds[i];
//
//         // 测试正向速度
//         printf("\r\n-- 测试正向速度: +%.1f --\r\n", speed);
//         Chassis_Motor_SetSpeed(speed);
//
//         // 等待稳定并记录数据
//         osDelay(500);
//         uint32_t startTime = osKernelGetTickCount();
//         float pos_avg_speed = 0;
//         int pos_samples = 0;
//
//         while (osKernelGetTickCount() - startTime < testDuration)
//         {
//             osDelay(200);
//             printf("正向 T: %.1f, C: %.1f, E: %.1f, O: %.1f\r\n",
//                    wheelController.target_speed,
//                    wheelController.current_speed,
//                    wheelController.pid.error,
//                    wheelController.pid.output);
//
//             pos_avg_speed += wheelController.current_speed;
//             pos_samples++;
//         }
//
//         // 计算平均速度
//         if (pos_samples > 0)
//         {
//             pos_avg_speed /= pos_samples;
//         }
//
//         // 测试反向速度
//         printf("\r\n-- 测试反向速度: -%.1f --\r\n", speed);
//         Chassis_Motor_SetSpeed(-speed);
//
//         // 等待稳定并记录数据
//         osDelay(500);
//         startTime = osKernelGetTickCount();
//         float neg_avg_speed = 0;
//         int neg_samples = 0;
//
//         while (osKernelGetTickCount() - startTime < testDuration)
//         {
//             osDelay(200);
//             printf("反向 T: %.1f, C: %.1f, E: %.1f, O: %.1f\r\n",
//                    wheelController.target_speed,
//                    wheelController.current_speed,
//                    wheelController.pid.error,
//                    wheelController.pid.output);
//
//             neg_avg_speed += wheelController.current_speed;
//             neg_samples++;
//         }
//
//         // 计算平均速度
//         if (neg_samples > 0)
//         {
//             neg_avg_speed /= neg_samples;
//         }
//
//         // 输出对比结果
//         printf("\r\n速度 %.1f 的双向对比:\r\n", speed);
//         printf("- 正向平均速度: %.2f (误差: %.2f%%)\r\n",
//                pos_avg_speed,
//                (speed != 0) ? (100.0f * (speed - pos_avg_speed) / speed) : 0);
//         printf("- 反向平均速度: %.2f (误差: %.2f%%)\r\n",
//                neg_avg_speed,
//                (speed != 0) ? (100.0f * (-speed - neg_avg_speed) / (-speed)) : 0);
//
//         // 停止电机
//         Chassis_Motor_Stop();
//         osDelay(500);
//     }
//
//     printf("\r\n==== 电机低速双向对比测试完成 ====\r\n");
// }
//
// // 全速度范围测试
// // 测试电机在不同速度区间的响应特性
// void Motor_SpeedRangeTest(void)
// {
//     printf("\r\n==== 开始电机速度范围测试 ====\r\n");
//
//     // 速度测试序列（正向和反向）
//     const float speeds[] = {10.0f, 30.0f, 50.0f, 100.0f, 150.0f, 200.0f, 300.0f,
//                             -10.0f, -30.0f, -50.0f, -100.0f, -150.0f, -200.0f, -300.0f};
//     const uint32_t testDuration = 2000; // 每个速度测试2秒
//
//     for (int i = 0; i < sizeof(speeds) / sizeof(speeds[0]); i++)
//     {
//         float testSpeed = speeds[i];
//
//         // 设置测试速度
//         printf("\r\n测试速度: %.1f:\r\n", testSpeed);
//         Chassis_Motor_SetSpeed(testSpeed);
//
//         // 等待稳定时间
//         uint32_t startTime = osKernelGetTickCount();
//         while (osKernelGetTickCount() - startTime < testDuration)
//         {
//             // 每500ms打印一次状态
//             osDelay(500);
//             printf("目标: %.2f, 当前: %.2f, 输出: %.2f, 误差比例: %.2f%%\r\n",
//                    wheelController.target_speed,
//                    wheelController.current_speed,
//                    wheelController.pid.output,
//                    (wheelController.target_speed != 0) ? (100.0f * (wheelController.target_speed - wheelController.current_speed) / wheelController.target_speed) : 0.0f);
//         }
//     }
//
//     // 测试结束停止电机
//     Chassis_Motor_Stop();
//     printf("\r\n==== 电机速度范围测试完成 ====\r\n");
// }
//
// // PID参数优化测试
// // 测试不同的PID参数对电机控制的影响
// void Motor_PIDOptimizationTest(void)
// {
//     printf("\r\n==== 开始PID参数优化测试 ====\r\n");
//
//     // 保存当前PID参数
//     float original_kp = wheelController.pid.kp;
//     float original_ki = wheelController.pid.ki;
//     float original_kd = wheelController.pid.kd;
//
//     // 测试不同的PID参数组合
//     const float test_speeds[] = {10.0f, 50.0f};
//
//     // 不同参数组合
//     const float kp_values[] = {1.5f, 2.5f, 3.5f, 5.0f};
//     const float ki_values[] = {0.2f, 0.5f, 0.8f, 1.2f};
//     const float kd_values[] = {0.02f, 0.05f, 0.1f, 0.2f};
//
//     // 测试不同速度的PID参数调整
//     for (int s = 0; s < sizeof(test_speeds) / sizeof(test_speeds[0]); s++)
//     {
//         float test_speed = test_speeds[s];
//         printf("\r\n===== 测试速度: %.1f =====\r\n", test_speed);
//
//         // 测试不同的Kp值
//         printf("\r\n-- 测试Kp影响 (Ki=%.2f, Kd=%.2f) --\r\n", original_ki, original_kd);
//         for (int p = 0; p < sizeof(kp_values) / sizeof(kp_values[0]); p++)
//         {
//             // 设置参数
//             PID_SetParams(&wheelController.pid, kp_values[p], original_ki, original_kd);
//             printf("设置 Kp=%.2f\r\n", kp_values[p]);
//
//             // 重置PID状态
//             PID_Reset(&wheelController.pid);
//
//             // 设置目标速度
//             Chassis_Motor_SetSpeed(test_speed);
//
//             // 等待稳定
//             osDelay(1000);
//
//             // 测试2秒，记录稳定后的表现
//             uint32_t startTime = osKernelGetTickCount();
//             float avg_error = 0;
//             int samples = 0;
//
//             while (osKernelGetTickCount() - startTime < 2000)
//             {
//                 osDelay(200);
//                 printf("T: %.1f, C: %.1f, E: %.1f, O: %.1f\r\n",
//                        wheelController.target_speed, wheelController.current_speed,
//                        wheelController.pid.error, wheelController.pid.output);
//
//                 // 累计误差（取绝对值）
//                 avg_error += fabsf(wheelController.pid.error);
//                 samples++;
//             }
//
//             // 计算平均误差
//             if (samples > 0)
//             {
//                 avg_error /= samples;
//                 printf("Kp=%.2f 的平均误差: %.2f (%.2f%%)\r\n",
//                        kp_values[p], avg_error,
//                        (test_speed != 0) ? (100.0f * avg_error / test_speed) : 0);
//             }
//
//             // 停止电机
//             Chassis_Motor_Stop();
//             osDelay(500);
//         }
//
//         // 恢复原始参数进行Ki测试
//         PID_SetParams(&wheelController.pid, original_kp, original_ki, original_kd);
//
//         // 测试不同的Ki值
//         printf("\r\n-- 测试Ki影响 (Kp=%.2f, Kd=%.2f) --\r\n", original_kp, original_kd);
//         for (int i = 0; i < sizeof(ki_values) / sizeof(ki_values[0]); i++)
//         {
//             // 设置参数
//             PID_SetParams(&wheelController.pid, original_kp, ki_values[i], original_kd);
//             printf("设置 Ki=%.2f\r\n", ki_values[i]);
//
//             // 重置PID状态
//             PID_Reset(&wheelController.pid);
//
//             // 设置目标速度
//             Chassis_Motor_SetSpeed(test_speed);
//
//             // 等待稳定
//             osDelay(1000);
//
//             // 测试2秒
//             uint32_t startTime = osKernelGetTickCount();
//             while (osKernelGetTickCount() - startTime < 2000)
//             {
//                 osDelay(200);
//                 printf("T: %.1f, C: %.1f, E: %.1f, O: %.1f\r\n",
//                        wheelController.target_speed, wheelController.current_speed,
//                        wheelController.pid.error, wheelController.pid.output);
//             }
//
//             // 停止电机
//             Chassis_Motor_Stop();
//             osDelay(500);
//         }
//     }
//
//     // 测试结束停止电机
//     Chassis_Motor_Stop();
//     printf("\r\n==== PID参数优化测试完成 ====\r\n");
//
//     // 恢复原始PID参数
//     PID_SetParams(&wheelController.pid, original_kp, original_ki, original_kd);
// }
