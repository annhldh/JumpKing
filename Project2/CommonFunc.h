#pragma once
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "Object.h"
#include <vector>
#include <utility>
#include <iostream>;

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 730

#define MAX_TILES  100
#define BLANK_TILE 0
#define TILE_SIZE  32

#define MAX_MAP_X 40
#define MAX_MAP_Y 300
const int COLOR_KEY_R = 179;
const int COLOR_KEY_G = 179;
const int COLOR_KEY_B = 179;
extern int GRAVITY;
extern int MAX_GRAVITY;
const int SCREEN_BPP = 32;



#define BLANK_TILE 0

#define NUMBER_OF_FRAME 8

#define MAX_JUMP_FORCE 50



 struct Map
{
	// vi tri ria man hinh so voi map 
	int start_x_ = 0;
	int start_y_ =0 ;

	int max_x_ = 0;
	int max_y_ = 0;

	int tile[MAX_MAP_Y][MAX_MAP_X] = {};
	char nam[30] = "";
	char* file_name_ = nam;
	int Timer_map[MAX_MAP_Y][MAX_MAP_X] = {};
	
	std::vector <int> non_collision_block = { 0,4,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,48,49,53,54,55,56,81,82,83,84,85,86,87,88,90,91,92,93};
	bool IsNonCollisionBlock(int val);
	std::vector <int> Collection_block = { 4,25 };
	std::vector<std::pair<int,int>> Ice_block = {};
	std::vector<std::pair<int, int>> Laser_block = {};
	std::vector<std::pair<int,int>> XO_block = {};
	int xo[3][3] = { 9,9,9,9,9,9,9,9,9 };
	int Check_xo();
	void Update_xo(int mode);
	void xo_rival();
	int x_cnt = 0;
	int o_cnt = 0;
};

 void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int x, int y);
 SDL_Surface* getSurfaceFromTexture(SDL_Texture* texture, SDL_Renderer* renderer);

 extern Uint32 loop ;

#endif // !COMMON_FUNCTION_H_
