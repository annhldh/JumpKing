#include "SFX.h"

 Mix_Chunk* fall    = nullptr;
 Mix_Chunk* walking = nullptr;
 Mix_Chunk* jumping = nullptr;
 Mix_Chunk* landing = nullptr;  
 Mix_Chunk* tap = nullptr;
 Mix_Chunk* icebreaking;
 Mix_Chunk* door_open = nullptr;


 Mix_Music* music_theme[4];
 Mix_Music* music_rick;
 int volume = 64;
 int GAME_MODE = 0;
 Object rope ;

 int mouse_x = 0, mouse_y = 0;
 bool is_quit = false;
 bool pause_ = false;
 bool sett = false;
 int king_tale_color = 1;
 bool IsSnow = true;
 bool OnShop_ = false;

 int King_hat = 0;
 Uint32 Achive_ = 10000;
 int footprint_distance = 15;
 int tile_style_ = 0;

 extern int stage_val = 0;