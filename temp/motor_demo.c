#include "task_motor.h"
#include "motor_test.h"
#include "motor_cmd.h"
#include "cmsis_os.h"
#include <stdio.h>

// 底盘PID控制示例演示函数
void Motor_PID_Demo(void)
{
    printf("Starting Motor PID Demo...\r\n"); // 初始化电机PID控制
    Chassis_Motor_PIDControl_Init();

    // 等待系统稳定
    osDelay(1000);

    printf("1. Testing basic motor speed control...\r\n");

    // 设置一个低速
    printf("Setting speed to 50...\r\n");
    Chassis_Motor_SetSpeed(50.0f);
    osDelay(3000); // 运行3秒

    // 设置一个中速
    printf("Setting speed to 200...\r\n");
    Chassis_Motor_SetSpeed(200.0f);
    osDelay(3000); // 运行3秒

    // 设置一个高速
    printf("Setting speed to 500...\r\n");
    Chassis_Motor_SetSpeed(500.0f);
    osDelay(3000); // 运行3秒

    // 停止电机
    printf("Stopping motor...\r\n");
    Chassis_Motor_Stop();
    osDelay(1000);

    printf("2. Running step response test...\r\n");
    // 进行阶跃响应测试 (0->300 单位速度，持续5秒)
    Motor_StepResponseTest(0.0f, 300.0f, 5000);

    // 暂停一下
    osDelay(1000);

    printf("3. Testing PID parameter adjustment...\r\n");
    // 使用不同的PID参数进行测试
    printf("Testing with higher proportional gain (Kp=4.0)...\r\n");
    Motor_AdjustPIDParams(4.0f, 0.5f, 0.1f);
    Motor_StepResponseTest(0.0f, 300.0f, 5000);

    // 暂停一下
    osDelay(1000);

    printf("Testing with higher integral gain (Ki=1.0)...\r\n");
    Motor_AdjustPIDParams(2.0f, 1.0f, 0.1f);
    Motor_StepResponseTest(0.0f, 300.0f, 5000);

    // 暂停一下
    osDelay(1000);

    printf("Testing with higher derivative gain (Kd=0.5)...\r\n");
    Motor_AdjustPIDParams(2.0f, 0.5f, 0.5f);
    Motor_StepResponseTest(0.0f, 300.0f, 5000);

    // 恢复默认PID参数
    Motor_AdjustPIDParams(2.0f, 0.5f, 0.1f);

    printf("4. Starting command interface...\r\n");
    // 启动命令界面，允许通过串口进行交互
    StartCommandInterface();

    printf("Motor PID Demo completed. You can now use the command interface.\r\n");
}

// 示例函数：如何在主程序中调用
void Example_Main_Usage(void)
{
    // 此函数仅用于示范，不需要实际调用

    // 1. 创建电机控制任务
    osThreadAttr_t motorTaskAttrs = {
        .name = "MotorTask",
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 512};

    motorTaskHandle = osThreadNew(MotorTask, NULL, &motorTaskAttrs);

    // 2. 或者，运行演示程序
    // Motor_PID_Demo();
}
