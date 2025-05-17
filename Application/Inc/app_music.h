#ifndef __APP_MUSIC_H__
#define __APP_MUSIC_H__

#include <stdint.h>
#ifndef __APP_MUSIC_H__
#define __APP_MUSIC_H__

#include <stdint.h>

// 音符频率定义
#define NOTE_C4  262  // Do
#define NOTE_D4  294  // Re
#define NOTE_E4  330  // Mi
#define NOTE_F4  349  // Fa
#define NOTE_G4  392  // So
#define NOTE_A4  440  // La
#define NOTE_B4  494  // Si
#define NOTE_C5  523  // 高音Do

void Music_Play(const uint16_t* notes, const uint16_t* durations, uint16_t len);

#endif

void Music_Play(void);
void Boot_Sound(void);

#endif
