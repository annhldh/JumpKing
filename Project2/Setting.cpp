#pragma once
#include "Setting.h"
#include "CommonFunc.h"
#include "King.h"



void Setting::setting(SDL_Renderer*des,SDL_Event events)
{
	setting_.Render(230, 165, des, NULL);


	if (events.type == SDL_MOUSEBUTTONDOWN)
	{

		if (mouse_x >= 480 && mouse_x <= 532 && mouse_y >= 255 && mouse_y <= 297)
		{
			IsSnow = 1 - IsSnow;
		}
		else if (mouse_x >= 260 && mouse_x <= 312 && mouse_y >= 170 && mouse_y <= 190)
		{
			sett = false;
		}
		else if (mouse_x >= 285 && mouse_x <= 330 && mouse_y >= 355 && mouse_y <= 405)
		{
			if (footprint_distance >= 10) footprint_distance -= 5;
			else footprint_distance = 5;
		}
		else if (mouse_x >= 603 && mouse_x <= 648 && mouse_y >= 355 && mouse_y <= 405)
		{
			if (footprint_distance <= 45) footprint_distance += 5;
			else footprint_distance = 50;
		}

	}
	footprint_distance_bar.rect_.w = footprint_distance /5 * 240/10;
	footprint_distance_bar.Render(348, 371, des, NULL);
	if (IsSnow == true)
	{
		yes_button_.Render(480, 255, des, NULL);
	}
	else no_button_.Render(480, 255, des, NULL);

	SDL_RenderPresent(des);
	
	
}