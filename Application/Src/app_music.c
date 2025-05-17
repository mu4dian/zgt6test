#include "app_music.h"
#include "bsp_buzzer.h"
#include "cmsis_os2.h"  // 如果用FreeRTOS延时

// 定义音符频率（C大调）
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

#define NOTE_C4  262  // Do
#define NOTE_D4  294  // Re
#define NOTE_E4  330  // Mi



// 音符结构体
typedef struct {
    uint16_t freq;
    uint16_t duration_ms;
} Note_t;

// So La Xi 音效
Note_t solasi[] = {
    {NOTE_G4, 250},   // So
    {0, 10},          // 短暂停
    {NOTE_B4, 250},   // La
    {0, 10},          // 短暂停
    {NOTE_A4, 300},   // Xi
};

#define SOLASI_LEN (sizeof(solasi)/sizeof(solasi[0]))

// 欢乐颂示例（主旋律）
Note_t song[] = {
    {NOTE_E4, 400}, {NOTE_E4, 400}, {NOTE_F4, 400}, {NOTE_G4, 400},
    {NOTE_G4, 400}, {NOTE_F4, 400}, {NOTE_E4, 400}, {NOTE_D4, 400},
    {NOTE_C4, 800}, {NOTE_C4, 400}, {NOTE_D4, 400}, {NOTE_E4, 400},
    {NOTE_E4, 600}, {NOTE_D4, 200}, {NOTE_D4, 800},
    // 继续写下去，自己DIY
};

#define SONG_LEN  (sizeof(song)/sizeof(song[0]))

// 播放音乐主函数
void Music_Play(void) {
    Buzzer_Init();
    for(uint16_t i = 0; i < SONG_LEN; ++i) {
        if(song[i].freq > 0) {
            Buzzer_On(song[i].freq);
        } else {
            Buzzer_Off();
        }
        osDelay(song[i].duration_ms); // FreeRTOS延时（如裸机可用HAL_Delay）
        Buzzer_Off();
        osDelay(20); // 音符间短暂间隔
    }
}


void Boot_Sound(void) {
    Buzzer_Init();
    for(uint16_t i = 0; i < SOLASI_LEN; ++i) {
        if(solasi[i].freq > 0) {
            Buzzer_On(solasi[i].freq);
        } else {
            Buzzer_Off();
        }
        osDelay(solasi[i].duration_ms); // 或 HAL_Delay
        Buzzer_Off();
    }
}