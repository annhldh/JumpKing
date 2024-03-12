#pragma once
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include "Object.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 730

#define MAX_TILES  30
#define BLANK_TILE 0
#define TILE_SIZE  32

#define MAX_MAP_X 46
#define MAX_MAP_Y 99
const int COLOR_KEY_R = 180;
const int COLOR_KEY_G = 180;
const int COLOR_KEY_B = 180;

const int SCREEN_BPP = 32;

#define BLANK_TILE 0

#define NUMBER_OF_FRAME 8

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
};

#endif // !COMMON_FUNCTION_H_
