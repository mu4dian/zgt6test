#include "bsp_irtracker.h"
#include "line_follow.h"
#include <stdio.h>

#include "chassis.h"

/**
 * 这里给出一个简单加权平均算法：
 * 传感器排列为  X1 X2 X3 X4 X5 X6 X7 X8  （假设 X1最左，X8最右）
 * 检测到的为黑线（低电平为黑线），用加权平均求出偏移量，调整速度
 */

#define BASE_SPEED  70  // 推荐巡线基础速度百分比
#define TURN_GAIN   60  // 差速调整幅度

void LineFollow_Task(void)
{
    IRTracker_Data_t ir_data;
    int weight[8] = {16, -13, -9, -5, 5, 9, 13, 16};
    int sum = 0, cnt = 0;
    int position = 0; // 负值偏左，正值偏右

    IRTracker_Read(&ir_data);

    for(int i=0; i<8; ++i){
        if(ir_data.value[i] == 0){ // 假定0为黑线（视实际电路反向即可）
            sum += weight[i];
            cnt ++;
        }
    }
    if(cnt == 0){
        // 全部检测不到，说明偏出赛道，紧急停车
        Chassis_Motor_SetSpeed(10, 10, 10, 10);
        return;
    }
    position = sum / cnt;

    // 差速控制
    float left_speed = BASE_SPEED;
    float right_speed = BASE_SPEED;
    if(position < 0){
        // 偏左，右轮加速，左轮减速
        left_speed  -= (-position) * TURN_GAIN / 7.0f;
        right_speed += (-position) * TURN_GAIN / 7.0f;
    }else if(position > 0){
        // 偏右，左轮加速，右轮减速
        left_speed  += position * TURN_GAIN / 7.0f;
        right_speed -= position * TURN_GAIN / 7.0f;
    }

    // 限幅
    if(left_speed > 100) left_speed = 100;
    if(right_speed > 100) right_speed = 100;
    if(left_speed < -100) left_speed = -100;
    if(right_speed < -100) right_speed = -100;

    // 四驱差速
    Chassis_Motor_SetSpeed(left_speed, left_speed, right_speed, right_speed);
}
