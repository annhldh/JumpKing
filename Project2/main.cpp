#pragma once
#include "CommonFunc.h"
#include "Object.h"
#include "King.h"
#include "game_map.h"


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

int main(int argc, char* args[]) {
 

    if (!init()) {
        printf("Failed to initialize!\n");
        return 2;
    }
    GameMap game_map;
    char  nameMap[] = "map//map01.dat";
    game_map.LoadMap(nameMap);
    game_map.LoadTiles(ve);



    bool is_quit = false;

    back_ground_.LoadImg("img//backgroundDark.png", ve);
    
    while (!is_quit)
    {
  
        
        SDL_Event e;

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                is_quit = true;
            }
            king_.Control(e, ve);
        }
        if (king_.turn == 0) king_.LoadImg("img//King//51.png", ve);
        else king_.LoadImg("img//King//52.png", ve);
        SDL_RenderClear(ve);
        back_ground_.Render(0,0,ve,NULL);
   
        

       
        king_.MoveAction(game_map.game_map_);
        king_.Render(king_.x_pos,king_.y_pos,ve,NULL);
        game_map.DrawMap(ve);
        SDL_RenderPresent(ve);
        

        
    }

    close();
    return 0;
}
