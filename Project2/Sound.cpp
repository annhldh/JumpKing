
#include "CommonFunc.h"
#include "Sound.h"
#include"SFX.h";
 void display_sound(Mix_Chunk* music)
{
    if (!music) {
        fprintf(stderr, "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
    }
    // Phát âm thanh
    bool check = Mix_Playing(1);
    if (!check)
    {
        Mix_PlayChannel(1, music, 0);
    }


}
 
 void display_music_theme(Mix_Music* theme)
 {

    
     Mix_PlayMusic(theme,-1);
     Mix_VolumeMusic(volume);


 }
 void display_rick(Mix_Music* rick)
 {
     int st = SDL_GetTicks();
     if (!rick) {
         fprintf(stderr, "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
     
     }

     Mix_PlayMusic(rick, -1);

     while (Mix_PlayingMusic()) {
         SDL_Delay(100); 
         if(SDL_GetTicks()-st >=10000)  Mix_HaltMusic();
     }
     

 }