#pragma once
#include "CommonFunc.h"
#include "Object.h"
#include "King.h"
#include "game_map.h"

#include<iostream>

SDL_Renderer* ve = NULL;
SDL_Window* gWindow = NULL;



bool init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            ve = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (ve == NULL) {
                printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
                success = false;
            }
            else {
                SDL_SetRenderDrawColor(ve, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
    }

    return success;
}



void close() {
    SDL_DestroyRenderer(ve);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

Object back_ground_;
King king_;
Object jump_bar;
Object lose_;



int main(int argc, char* args[]) {
 

    if (!init()) {
        printf("Failed to initialize!\n");
        return 2;
    }
    GameMap game_map;
    char  nameMap[] = "map//map03.txt";
    game_map.LoadMap(nameMap);
    game_map.LoadTiles(ve);
    king_.LoadImg("img//King//king_run_right.png", ve);
    king_.set_clips();
    lose_.LoadImg("img//rickroll_4k.png", ve);

    jump_bar.LoadImg("img//f.png", ve);
    jump_bar.rect_.h = 64;
    jump_bar.rect_.x = 0;
    jump_bar.rect_.y = 0;

    bool is_quit = false;
    

    back_ground_.LoadImg("img//backgroundCastle2.png", ve);
    int mouse_x = 0, mouse_y = 0;
    while (!is_quit)
    {
        int start = SDL_GetTicks();
        
        SDL_Event e;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                is_quit = true;
            }
            king_.Control(e, ve);
            if (king_.Life == 0 && e.type == SDL_MOUSEBUTTONDOWN ) {
                if (mouse_x >= 300 && mouse_x <= 600 && mouse_y >= 300 && mouse_y <= 600)
                {
                    king_.Life = 2;
                    king_.LoadImg("img//King//king_run_right.png", ve);
                    king_.set_clips();
                    king_.Action[3] = false;
                    king_.x_stand = 178;
                    king_.y_stand = 2300;

                    king_.on_ground = true;
                    king_.turn = 0;
                }

            }
        }
        if (king_.Life == 0)
        {
            int st = SDL_GetTicks();
            lose_.Render(100, 100, ve,NULL);
            SDL_RenderPresent(ve);
            // Khởi tạo SDL2 và SDL2_mixer
            if (SDL_Init(SDL_INIT_AUDIO) < 0) {
                fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
                return 1;
            }
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                fprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                return 1;
            }

            // Tải tệp MP3
            Mix_Music* music = Mix_LoadMUS("img//rick(2).mp3");
            if (!music) {
                fprintf(stderr, "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
                return 1;
            }

            // Phát âm nhạc
            Mix_PlayMusic(music, -1);

            // Chờ cho đến khi âm nhạc kết thúc
            while (Mix_PlayingMusic()) {
                int en = SDL_GetTicks();
                if (en - st > 10000) {
                    Mix_HaltMusic();

                    break;
                }
                
            }
            Mix_FreeMusic(music);
            Mix_CloseAudio();
            king_.Life = 2;

        }
        else {
            SDL_RenderClear(ve);
            back_ground_.Render(0, 0, ve, NULL);
            king_.CenterEntityOnMap(game_map);
            king_.MoveAction(game_map.game_map_);

            king_.Show_frame(ve);


            king_.CenterEntityOnMap(game_map);
            game_map.DrawMap(ve);
            jump_bar.rect_.w = 10 * king_.jump_forces;
            jump_bar.Render(0, 0, ve, &jump_bar.rect_);
            SDL_RenderPresent(ve);

            int endloop = SDL_GetTicks();
            int timeloop = endloop - start;
            if (timeloop < 1000 / 60)
            {
                SDL_Delay(1000 / 60 - timeloop);
            }
        }
    }

    close();
    return 0;
}

