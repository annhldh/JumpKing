#pragma once
#include "Victory.h"
#include "SFX.h"
void Victory:: Display_Congrats(SDL_Renderer* des)
{
	background_.Render(0, 0, des, NULL);
	Congrats.Render(0, 0, des, &clip[frame_],0,0,&screen);
	if (frame_ < 1899 && loop % 20 == 0) frame_++;
	
	
}

void Victory::back(SDL_Event events)
{
	if (events.type == SDL_MOUSEBUTTONDOWN)  isVictory=false;
}

void Victory::Set_clip(SDL_Renderer* des)
{
	for (int i = 0; i < 1900; i++)
	{
		clip[i].x = 0;
		clip[i].y = i;
		clip[i].w = SCREEN_WIDTH;
		clip[i].h = SCREEN_HEIGHT;
	}
	Congrats.LoadImg("img//Congrats.png",des);
	background_.LoadImg("img//black.png", des);
	std::cout << Congrats.rect_.h;
}