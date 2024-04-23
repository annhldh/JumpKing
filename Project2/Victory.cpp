#pragma once
#include "Victory.h"
#include "SFX.h"
void Victory:: Display_Congrats(SDL_Renderer* des)
{
	if (GAME_MODE == 2)
	{
		Medal_.Render(0, 0, des, NULL, 0, 0, &medal_rect[frame_]);
		if (frame_ < 52 && loop%50==0)frame_++;
	}
	else
	{
		background_.Render(0, 0, des, NULL);
		Congrats.Render(0, 0, des, &clip[frame_], 0, 0, &screen);
		if (frame_ < 1899 && loop % 20 == 0) frame_++;
	}
	
	
}

void Victory::back(SDL_Event events)
{
	if (isVictory==true && events.type == SDL_MOUSEBUTTONDOWN)
	{
		frame_ = 0;
		isVictory = false;
	}
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
	for (int i = 0; i < 53;i++)
	{
		medal_rect[i].w = 10 * i;
		medal_rect[i].h = 10 * i;
		medal_rect[i].x = SCREEN_WIDTH / 2 - medal_rect[i].w/2;
		medal_rect[i].y = SCREEN_HEIGHT / 2 - medal_rect[i].h/2;
		
	}
	Congrats.LoadImg("img//Congrats.png",des);
	background_.LoadImg("img//black.png", des);
	Medal_.LoadImg("img//end_mode 2.png",des);

}