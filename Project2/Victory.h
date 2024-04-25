#pragma once
#ifndef VICTORY_H_
#define VICTORY_H_
#include "Object.h"
#include "CommonFunc.h"

struct Victory
{
	Object Congrats;
	Object Congrats_scroll;
	Object background_;

	Object Medal_;
	void Set_clip(SDL_Renderer* des);
	void Display_Congrats(SDL_Renderer* des);
	void back(SDL_Event event);
	SDL_Rect clip[1900];
	SDL_Rect clip0[101];
	SDL_Rect medal_rect[100];
	SDL_Rect screen = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	int frame_ = 0;
	int frame_scroll = 0;

	bool is_queue = true;
	

};

#endif // !VICTORY_H_
