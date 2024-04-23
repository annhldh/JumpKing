#pragma once
#ifndef SFX_H_
#define SFX_H_
#include <SDL_mixer.h>
#include "Object.h"


extern Mix_Chunk* fall;
extern Mix_Chunk* walking ;
extern Mix_Chunk* jumping ;
extern Mix_Chunk* landing;
extern Mix_Chunk* icebreaking;
extern Mix_Chunk* tap;
extern Mix_Chunk* door_open;

extern Mix_Music* music_theme[4];
extern Mix_Music* music_rick;

extern int volume;
extern int GAME_MODE;
extern Object rope;

extern int mouse_x , mouse_y ;
extern bool is_quit;
extern bool pause_;
extern bool sett;

extern int king_tale_color;
extern bool IsSnow ;
extern bool OnShop_;
extern Uint32 Achive_;
extern int King_hat;

extern int stage_val;
extern int footprint_distance;
extern int tile_style_;
extern bool isVictory;
extern bool isTutor;
#endif // !SFX_H_
