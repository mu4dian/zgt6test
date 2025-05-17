#ifndef __TASK_MOTOR_H__
#define __TASK_MOTOR_H__

#include "cmsis_os.h"
#include "bsp_pid.h"
#include "chassis.h"

#ifdef __cplusplus
extern "C"
{
#endif

    extern osThreadId_t motorTaskHandle;

    void MotorTask(void *argument);

#ifdef __cplusplus
}
#endif

#endif // __TASK_MOTOR_H__
