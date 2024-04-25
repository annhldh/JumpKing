#pragma once
#include "CommonFunc.h"
#include "Object.h"
#include "King.h"
#include "game_map.h"
#include "Sound.h"
#include "Setting.h"
#include "Shop.h"
#include "Victory.h"
#include "Tutorial.h"
#include < algorithm>




SDL_Renderer* ve = NULL;
SDL_Window* gWindow = NULL;

SDL_Rect b_g = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };


std::string Height_;
Object pause_button;
Object pause_touch;
Shop shop_;
Victory victory_;
Tutorial tutorial_;

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
    else Mix_VolumeMusic(48);
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


TTF_Font* font;
SDL_Color textColor = { 215, 0, 20 };
Object exp_;

Setting Option_;
SDL_Surface* Cursor_d;
std::pair< int, std::string> bo[11];
std::ifstream board;
std::ofstream board2;
std::ifstream money;
std::ofstream money2;


SDL_Rect b_r = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
SDL_Event e;

void mouseEvent();
void loadSFX();
void loadsnow();
void loadLeaderBoard();
void loadSufaceLayerObject( TTF_Font* font);
void BackgroundRender();
void LeaderBoard();
void LoadMoney();
void SaveMoney();


void loadJump_bar()
{
    jump_bar.LoadImg("img//f.png", ve);
    bar_.LoadImg("img//bar.png", ve);
    jump_bar.rect_ = { 0,0,0,40 };
    bar_.rect_ = { 0,0,MAX_JUMP_FORCE * 10 + 10,50 };
}
void LoadImageFile();

void PlayDefault()
{
    char nameMap[] = "map//map00.dat";
    game_map.LoadMap(nameMap);
    game_map.LoadTiles(ve);
    display_music_theme(music_theme[0]);
    LoadMoney();
}


int main(int argc, char* args[]) {
 

    int swap = 0;

    if (!init()) {
        printf("Failed to initialize!\n");
        return 2;
    }
  
    font = TTF_OpenFont("Cutout.ttf", 40);
    loadsnow();
    LoadImageFile();
    loadSFX();
    loadJump_bar();
    loadLeaderBoard();
    PlayDefault();
    shop_.load_custom(ve);
    SDL_Cursor* cursor = SDL_CreateColorCursor(Cursor_d, 0, 0);
    SDL_SetCursor(cursor);
   


    
    while (!is_quit)
    {
        int start = SDL_GetTicks();
        
      
        SDL_GetMouseState(&mouse_x, &mouse_y);
    
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                is_quit = true;
            }
            king_.Control(e, ve,game_map.game_map_);
            if ( e.type == SDL_MOUSEBUTTONDOWN ) 
            {
                mouseEvent();

            }
        }
        
        if (king_.stage_ > stage_val )
        {
            king_.loadStage(king_.stage_, game_map, ve, back_ground_);
            stage_val = king_.stage_;
       
        }

        
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
        else if (OnShop_ == true)
        {
            
            shop_.display_Shop(ve);
            renderText(ve, font, shop_.exp_str, textColor, 100, 50);
            SDL_RenderPresent(ve);
        }
        else if (isVictory == true)
        {
            victory_.Display_Congrats(ve);
            victory_.back(e);
            SDL_RenderPresent(ve);
        }
        else {
            SDL_RenderClear(ve);
            BackgroundRender();

            king_.CenterEntityOnMap(game_map);
            king_.MoveAction(game_map.game_map_);
          
            game_map.DrawMap(ve);
            

            king_.Jump_effect(ve, game_map.game_map_);
            if (king_.connect_rope == true)king_.render_rope(ve, game_map.game_map_);
            king_.Show_frame(ve);
  
            tutorial_.Buttton(&e);
            loadSufaceLayerObject(font);
            if (mouse_x >= 860 && mouse_x <= 931 && mouse_y >= 20 && mouse_y <= 95) pause_touch.Render(SCREEN_WIDTH - 100, 20, ve, NULL);
            
            SDL_RenderPresent(ve);
            
            int endloop = SDL_GetTicks();
            int timeloop = endloop - start;
       
            if (timeloop < 1000 / 60)
            {
                SDL_Delay(1000 / 60 - timeloop);
            }
        }
        loop++;

    }
    

    SaveMoney();
    shop_.SaveShopData();
    close();
    return 0;
}



void LoadImageFile()
{
    //Mix_VolumeMusic(-1);
    icon_ = IMG_Load("img//icon.png");
    SDL_SetWindowIcon(gWindow, icon_);
    king_.loadKingImg(ve);
    king_.set_clips();
    lose_.LoadImg("img//rickroll_4k.png", ve);
    query_.LoadImg("img//reborn_query.png", ve);
    back_ground_.LoadImg("img//background1.png", ve);
    Leaderboard_.LoadImg("img//Leaderboard.png", ve);
    pause_button.LoadImg("img//button//pause.png", ve);
    pause_touch.LoadImg("img//button//pause_touch.png", ve);
    pause.LoadImg("img//pause.png", ve);
    volume_bar.LoadImg("img//volume_bar.png", ve);
    exp_.LoadImg("img//EXP.png", ve);
    rope.LoadImg("img//rope.png", ve);
    Option_.setting_.LoadImg("img//setting.png", ve);
    Option_.yes_button_.LoadImg("img//button//yes.png", ve);
    Option_.no_button_.LoadImg("img//button//no.png", ve);

    Option_.footprint_distance_bar = volume_bar;

    Cursor_d = IMG_Load("img//Cursor_d.png");
    char tale_name[] = "img//button//jump_effect_n.png";
    for (int i = 0; i < COLOR_COUNT; i++)
    {
        tale_name[25] = i + '0';
        Option_.tale_color[i].LoadImg(tale_name, ve);
    }
    victory_.Set_clip(ve);
    tutorial_.loadTutor(ve);
}

void loadSFX()
{
    fall = Mix_LoadWAV("sound//fall.mp3");
    walking = Mix_LoadWAV("sound//walking.mp3");
    jumping = Mix_LoadWAV("sound//jumping.mp3");
    landing = Mix_LoadWAV("sound//landing.mp3");
    icebreaking = Mix_LoadWAV("sound//icebreaking.mp3");
    tap = Mix_LoadWAV ("sound//tap.mp3");
    door_open = Mix_LoadWAV("sound//door_open.mp3");
    bird = Mix_LoadWAV("sound//bird.mp3");

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
    if (!board.is_open()) {

        std::cout << "Unable to open file for writing.." << std::endl;
    }

    char a;
    for (int i = 1; i < 11; i++)
    {

        getline(board, bo[i].second);
        board >> bo[i].first;
        board.ignore();


    }

    board.close();

}

void LoadMoney()
{
    money.open("money.txt");
    int mon;
    money >> mon;
    Achive_ = mon;
    money.close();
}

void SaveMoney()
{
    money2.open("money.txt", std::ios::trunc);
    money2 << Achive_;
    money2.close();
}

void loadSufaceLayerObject(TTF_Font* font)
{
    if (IsSnow== true)
    {
        snow[loop % 200 / 2 + 1].Render(0, 0, ve, NULL);
        
        if (GAME_MODE == 0)
        {
            bar_.Render(20, SCREEN_HEIGHT-80, ve, NULL);
            jump_bar.rect_.w = 10 * king_.jump_forces;
            jump_bar.Render(25, SCREEN_HEIGHT-75, ve, &jump_bar.rect_);
        }
    }
    
    Height_ = std::to_string(king_.max_height);
    exp_.Render(SCREEN_WIDTH - 180, 90, ve, NULL);
    renderText(ve, font, Height_,textColor, SCREEN_WIDTH - 100, 100);
    pause_button.Render(SCREEN_WIDTH - 100, 20, ve, NULL);
    tutorial_.Display_tutorial(ve);
 
   

}
void BackgroundRender()
{
   
     b_r.y = 1.0*game_map.game_map_.start_y_/(game_map.game_map_.max_y_-SCREEN_HEIGHT)*(back_ground_.rect_.h-SCREEN_HEIGHT);

     back_ground_.Render(0, 0, ve, &b_r,0.0,NULL,&b_g);
}



void LeaderBoard()
{

    board2.open("board.txt", std::ios::trunc);
    bo[0].first = king_.score_ + king_.max_height;
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
    board2.close();
}

void mouseEvent()
{
    display_sound(tap);
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
                if (volume >= 16)
                {
                    Mix_VolumeMusic(volume);
                    volume -= 16;


                }
            }
            else if (mouse_x >= 575 && mouse_x <= 620 && mouse_y >= 305 && mouse_y <= 350)
            {
                if (volume < 128)
                {
                    volume += 16;

                    Mix_VolumeMusic(volume);
                }
            }
            else if (mouse_x >= 565 && mouse_x <= 695 && mouse_y >= 390 && mouse_y <= 505)
            {
                LeaderBoard();

            }
            else if (mouse_x >= 315 && mouse_x <= 425 && mouse_y >= 390 && mouse_y <= 505)
            {
                king_.loadStage(stage_val, game_map, ve, back_ground_);

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
            LeaderBoard();
            king_.loadStage(0, game_map, ve, back_ground_);
        }
    }
    if (OnShop_ == true)
    {
        shop_.Shop_act(&e);
    }
}