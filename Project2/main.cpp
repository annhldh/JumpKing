#pragma once
#include "CommonFunc.h"
#include "Object.h"
#include "King.h"
#include "game_map.h"
#include "Sound.h"
#include "Setting.h"
#include <fstream>
#include < algorithm>
SDL_Renderer* ve = NULL;
SDL_Window* gWindow = NULL;
std::pair< int, std::string> bo[11];
std::ifstream board;
std::ofstream board2;
SDL_Rect b_g = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

SDL_Color textColor = { 255, 0, 20 };
std::string text;
Object pause_button;
Object pause_touch;


bool init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        gWindow = SDL_CreateWindow("JumpKing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
    else Mix_VolumeMusic(128);
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
Object Leaderboard_;
Object jump_bar;
Object bar_;
SDL_Surface* icon_;
Object snow[101];
GameMap game_map;
Object pause;
Object volume_bar;
Setting Option_;

SDL_Rect b_r = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };


void loadSFX();
void loadsnow();
void loadLeaderBoard();
void loadSufaceLayerObject( TTF_Font* font);
void BackgroundRender();


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
    bar_.rect_ = { 0,0,MAX_JUMP_FORCE * 10 + 10,50 };
}
void LoadImageFile()
{
    Mix_VolumeMusic(-1);
    icon_ = IMG_Load("img//icon.png");
    SDL_SetWindowIcon(gWindow, icon_);
    king_.loadKingImg(ve);
    king_.LoadImg("img//King//king_run_right.png", ve);
    king_.set_clips();
    lose_.LoadImg("img//rickroll_4k.png", ve);
    query_.LoadImg("img//reborn_query.png", ve);
    back_ground_.LoadImg("img//background1.png", ve);
    Leaderboard_.LoadImg("img//Leaderboard.png", ve);
    pause_button.LoadImg("img//button//pause.png",ve);
    pause_touch.LoadImg("img//button//pause_touch.png", ve);
    pause.LoadImg("img//pause.png", ve);
    volume_bar.LoadImg("img//volume_bar.png", ve);
    rope.LoadImg("img//rope.png",ve);
    Option_.setting_. LoadImg("img//setting.png", ve);
    Option_.yes_button_.LoadImg("img//button//yes.png", ve);
    Option_.no_button_.LoadImg("img//button//no.png", ve);
    char tale_name[] = "img//button//jump_effect_n.png";

    for (int i = 0; i < COLOR_COUNT; i++)
    {
        tale_name[25] = i+'0';
        Option_.tale_color[i].LoadImg(tale_name, ve);
    }
}
void PlayDefault()
{
    char nameMap[] = "map//map00.dat";
    game_map.LoadMap(nameMap);
    game_map.LoadTiles(ve);
    display_music_theme(music_theme[0]);
}


int main(int argc, char* args[]) {
 

    int swap = 0;

    if (!init()) {
        printf("Failed to initialize!\n");
        return 2;
    }
  

    TTF_Font* font = TTF_OpenFont("Cutout.ttf", 40);
    loadsnow();
    LoadImageFile();
    loadSFX();
    loadJump_bar();
    loadLeaderBoard();
    PlayDefault();


    
    int stage_val = 0;


    
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
            king_.Control(e, ve,game_map.game_map_);
            if ( e.type == SDL_MOUSEBUTTONDOWN ) {
                if (mouse_x >= 860 && mouse_x <= 931 && mouse_y >= 20 && mouse_y <= 100)
                {
                    pause_ = true;  
                }
                if (pause_ == true)
                {

                    if (mouse_x >= 640 && mouse_x <= 710 && mouse_y >= 115 && mouse_y <= 185)
                    {
                        sett = true;
                    }

                    if (sett == true)
                    {
                        Option_.setting(ve, e);
                    }
                    else
                    {
                        if (mouse_x >= 435 && mouse_x <= 540 && mouse_y >= 495 && mouse_y <= 610)
                        {
                            pause_ = false;
                        }
                        else if (mouse_x >= 420 && mouse_x <= 465 && mouse_y >= 305 && mouse_y <= 350)
                        {
                            if (volume >= 16)   volume -= 16;
                        }
                        else if (mouse_x >= 575 && mouse_x <= 620 && mouse_y >= 305 && mouse_y <= 350)
                        {
                            if (volume < 128) volume += 16;
                        }

                        else if (mouse_x >= 315 && mouse_x <= 695 && mouse_y >= 390 && mouse_y <= 505)
                        {
                            bo[0].first = king_.max_height;
                            bo[0].second = "o N Y";
                            sort(bo, bo + 11);

                            Leaderboard_.Render(40, 35, ve, NULL);
                            for (int i = 10; i > 0; i--) board2 << bo[i].second << '\n' << bo[i].first << '\n';
                            for (int i = 10; i > 0; i--) renderText(ve, font, bo[i].second + " " + std::to_string(bo[i].first), textColor, 400, (10 - i + 8) * 35);
                            SDL_RenderPresent(ve);
                            SDL_Delay(3000);

                            king_.loadStage(0, game_map, ve, back_ground_);
                            stage_val = 0;
                            GAME_MODE = 0;
                            GRAVITY = 2;
                            MAX_GRAVITY = 32;
                            king_.max_height = 0;
                            pause_ = false;
                        }

                    }
                }
                
                if (king_.Life == 0)
                {
                    if (mouse_x >= 205 && mouse_x <= 415 && mouse_y >= 465 && mouse_y <= 540)
                    {

                        king_.Reborn(stage_val, ve, lose_);
                    }
                    else if (mouse_x >= 524 && mouse_x <= 754 && mouse_y >= 464 && mouse_y <= 539)
                    {
                        bo[0].first = king_.max_height;
                        bo[0].second = "Player";
                        sort(bo, bo + 11);

                        Leaderboard_.Render(40, 35, ve, NULL);
                        for (int i = 10; i > 0; i--) board2 << bo[i].second << '\n' << bo[i].first << '\n';
                        for (int i = 10; i > 0; i--) renderText(ve, font, bo[i].second + " " + std::to_string(bo[i].first), textColor, 270, (10 - i + 6) * 40);
                        SDL_RenderPresent(ve);
                        SDL_Delay(3000);

                        king_.loadStage(0, game_map, ve, back_ground_);
                        stage_val = 0;
                        GAME_MODE = 0;
                        GRAVITY = 2;
                        MAX_GRAVITY = 32;
                        king_.max_height = 0;

                    }
                }

            }
        }
        
        if (king_.stage_ > stage_val)
        {
            king_.loadStage(king_.stage_, game_map, ve, back_ground_);
            stage_val = king_.stage_;
       
        }
        Mix_VolumeMusic(volume);
        if (king_.Life == 0)
        {
            query_.Render(100, 100, ve, NULL);
            SDL_RenderPresent(ve);
            
        }
        else if (pause_ == true)
        {
            if (sett == false)
            {
                pause.Render(240, 50, ve, NULL);
                volume_bar.rect_.w = 240 * volume / 128;
                volume_bar.Render(410, 270, ve, NULL);


           
            }
            SDL_RenderPresent(ve);
        }
 
        else {
     
            
            SDL_RenderClear(ve);
            BackgroundRender();

            king_.CenterEntityOnMap(game_map);
            king_.MoveAction(game_map.game_map_);
          
            game_map.DrawMap(ve);
            king_.Jump_effect(ve, game_map.game_map_);
            king_.Show_frame(ve);
  
            if(king_.connect_rope==true)king_.render_rope(ve, game_map.game_map_);
            loadSufaceLayerObject(font);
            if (mouse_x >= 860 && mouse_x <= 931 && mouse_y >= 20 && mouse_y <= 95) pause_touch.Render(SCREEN_WIDTH - 100, 20, ve, NULL);
        

            std::cout << king_tale_color << '\n';
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
    music_theme[0] = Mix_LoadMUS("sound//theme2.mp3");
    music_theme[1] = Mix_LoadMUS("sound//theme2.mp3");
    music_theme[2] = Mix_LoadMUS("sound//theme2.mp3");
    music_theme[3] = Mix_LoadMUS("sound//theme2.mp3");
    music_rick = Mix_LoadMUS("sound//rick.mp3");

}

void loadsnow()
{

    for (int i = 1; i <= 100; i++)
    {
        std::string file_img;
        FILE* fp = NULL;
        std::string a = "";
        if (i < 10) a = "00" + std::to_string(i);
        else if (i < 100) a = "0" + std::to_string(i);
        else a = std::to_string(i);
        file_img = "snow/ezgif-frame-" + a + ".png";
        snow[i].LoadImg(file_img, ve);
    }

}

void loadLeaderBoard()
{

    board.open("board.txt");
    if (board.is_open()) {
    }
    else {
        std::cout << "Unable to open file for writing.." << std::endl;
    }

    char a;
    for (int i = 1; i < 11; i++)
    {

        getline(board, bo[i].second);
        board >> bo[i].first;
        board.ignore();


    }

    board2.open("board.txt", std::ios::trunc);
}

void loadSufaceLayerObject(TTF_Font* font)
{
    if (IsSnow== true)
    {
        snow[loop % 200 / 2 + 1].Render(0, 0, ve, NULL);
        loop++;
        if (GAME_MODE == 0)
        {
            bar_.Render(20, 655, ve, NULL);
            jump_bar.rect_.w = 10 * king_.jump_forces;
            jump_bar.Render(25, 660, ve, &jump_bar.rect_);
        }
    }
    
    text = std::to_string(king_.max_height);
    renderText(ve, font, text, textColor, SCREEN_WIDTH - 100, 100);
    pause_button.Render(SCREEN_WIDTH - 100, 20, ve, NULL);

}
void BackgroundRender()
{
   
     b_r.y = 1.0*game_map.game_map_.start_y_/(game_map.game_map_.max_y_-SCREEN_HEIGHT)*(back_ground_.rect_.h-SCREEN_HEIGHT);

     back_ground_.Render(0, 0, ve, &b_r,0.0,NULL,&b_g);
}


