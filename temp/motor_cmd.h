#ifndef __MOTOR_CMD_H__
#define __MOTOR_CMD_H__

#ifdef __cplusplus
extern "C"
{
#endif

    // 启动命令界面
    void StartCommandInterface(void);

    // 解析命令
    void ParseCommand(char *cmd);

#ifdef __cplusplus
}
#endif

#endif // __MOTOR_CMD_H__
