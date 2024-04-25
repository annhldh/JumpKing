#pragma once
#include "Victory.h"
#include "SFX.h"
void Victory:: Display_Congrats(SDL_Renderer* des)
{
	if (GAME_MODE == 2)
	{
		Medal_.Render(0, 0, des, NULL, 0, 0, &medal_rect[frame_]);
		if (frame_ < 52 && loop%50==0)frame_++;
		is_queue = false;

	}
	else 
	{

		background_.Render(0, 0, des, NULL);
		if (is_queue==true)
		{
			Congrats_scroll.Render(0, 0, des, NULL, 0, 0, &clip0[frame_scroll]);
			if(loop %20==0 && frame_scroll<99)frame_scroll++;
		}
		else if (is_queue == false)
		{
			Congrats.Render(0, 0, des, &clip[frame_], 0, 0, &screen);
			if (frame_ < 1719 && loop % 20 == 0) frame_++;
		}
	}
	
	
}

void Victory::back(SDL_Event events)
{
	if (isVictory==true  && events.type == SDL_MOUSEBUTTONDOWN)
	{
		if (is_queue == true)
		{
			is_queue = false;
		}
		else if(frame_>=1720 || (frame_>=51 && GAME_MODE==2))
		{
			frame_ = 0;
			frame_scroll = 0;
			isVictory = false;
			is_queue = true;
		}
	}
}

void Victory::Set_clip(SDL_Renderer* des)
{
	for (int i = 0; i < 100; i++)
	{
		clip0[i].w = 5 * i;
		clip0[i].h = 5 * i;
		clip0[i].x = SCREEN_WIDTH / 2 - clip0[i].w / 2;
		clip0[i].y = SCREEN_HEIGHT / 2 - clip0[i].h / 2;
	}
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
	Congrats_scroll.LoadImg("img//Victory_scroll.png", des);
	background_.LoadImg("img//black.png", des);
	Medal_.LoadImg("img//end_mode 2.png",des);

}