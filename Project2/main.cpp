#pragma once
#include "CommonFunc.h"
#include "Object.h"
#include "King.h"
#include "game_map.h"
#include "Sound.h"
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

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());

    }
    TTF_Init();
    return success;
}



void close() {
    SDL_DestroyRenderer(ve);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

Object back_ground_;
King king_;
Object lose_;
Object query_;
Object jump_bar;
Object bar_;



void loadSFX();

void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int x, int y) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect dstRect = { x, y, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, nullptr, &dstRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
void loadJump_bar()
{
    jump_bar.LoadImg("img//f.png", ve);
    bar_.LoadImg("img//bar.png", ve);
    jump_bar.rect_ = { 0,0,0,40 };
    bar_.rect_ = { 0,0,65 * 10 + 10,50 };
}
int main(int argc, char* args[]) {
 
    int swap = 0;

    if (!init()) {
        printf("Failed to initialize!\n");
        return 2;
    }

    TTF_Font* font = TTF_OpenFont("arial.ttf", 24); // Thay đổi path thành đường dẫn của font bạn muốn sử dụng
    SDL_Color textColor = { 255, 255, 25 }; // Màu trắng

   

    // Tạo texture từ surface
 

    
    GameMap game_map;
    char nameMap[]= "map//map01.dat";
    game_map.LoadMap(nameMap);
    game_map.LoadTiles(ve);
    
    loadSFX();
    loadJump_bar();

    king_.loadKingImg(ve);
    king_.LoadImg("img//King//king_run_right.png", ve);
    king_.set_clips();
    lose_.LoadImg("img//rickroll_4k.png", ve);
    query_.LoadImg("img//reborn_query.png", ve);



    display_music_theme(music_theme[1]);

    
   

    bool is_quit = false;
    
    int stage_val = 1;
    back_ground_.LoadImg("img//background1.png", ve);
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
                if (mouse_x >= 205 && mouse_x <= 415 && mouse_y >= 465 && mouse_y <= 540)
                {
                    lose_.Render(100, 100, ve, NULL);
                    SDL_RenderPresent(ve);
                    display_rick(music_rick);
                    king_.Life = 2;
                    display_music_theme(music_theme[king_.stage_]);
                }
                else if (mouse_x >= 524 && mouse_x <= 754 && mouse_y >= 464 && mouse_y <= 539)
                {
                    king_.loadStage(1, game_map, ve, back_ground_);
                    stage_val =1;
                    king_.max_height = 0;
             
                }

            }
        }
        
        if (king_.stage_ > stage_val)
        {
            king_.loadStage(king_.stage_, game_map, ve, back_ground_);
            stage_val++;
        }
        if (king_.Life == 0)
        {
            query_.Render(100, 100, ve, NULL);
            SDL_RenderPresent(ve);
            
        }
        else {
            SDL_RenderClear(ve);
            back_ground_.Render(0, 0, ve, NULL);

            king_.CenterEntityOnMap(game_map);
            king_.MoveAction(game_map.game_map_);

            king_.CenterEntityOnMap(game_map);
            game_map.DrawMap(ve);
            king_.Show_frame(ve);
            bar_.Render(20, 655, ve,NULL);
            jump_bar.rect_.w = 10 * king_.jump_forces;
            jump_bar.Render(25, 660, ve, &jump_bar.rect_);
            
            std::string text = std::to_string (king_.max_height);
            renderText(ve, font, text, textColor, SCREEN_WIDTH - 100, 100);
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


void loadSFX()
{
    fall = Mix_LoadWAV("sound//fall.mp3");
    walking = Mix_LoadWAV("sound//walking.mp3");
    jumping = Mix_LoadWAV("sound//jumping.mp3");
    landing = Mix_LoadWAV("sound//landing.mp3");
    icebreaking = Mix_LoadWAV("sound//icebreaking.mp3");
    music_theme[1] = Mix_LoadMUS("sound//theme1.mp3");
    music_theme[2] = Mix_LoadMUS("sound//theme2.mp3");
    music_rick = Mix_LoadMUS("sound//rick.mp3");

}
