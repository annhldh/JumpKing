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

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 730

#define MAX_TILES  61
#define BLANK_TILE 0
#define TILE_SIZE  32

#define MAX_MAP_X 40
#define MAX_MAP_Y 300
const int COLOR_KEY_R = 180;
const int COLOR_KEY_G = 180;
const int COLOR_KEY_B = 180;

const int SCREEN_BPP = 32;

#define BLANK_TILE 0

#define NUMBER_OF_FRAME 8

struct  pair
{
	int x; int y;
};
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
	
	std::vector <int> non_collision_block = { 0,4,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,53,54,55,56};
	bool IsNonCollisionBlock(int val);
	std::vector<pair> Ice_block = {};
};



#endif // !COMMON_FUNCTION_H_
