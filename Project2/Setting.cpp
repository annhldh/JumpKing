#pragma once
#include "Setting.h"
#include "CommonFunc.h"
#include "King.h"


#include <SDL.h>

void Setting::setting(SDL_Renderer*des,SDL_Event events)
{
	setting_.Render(305, 165, des, NULL);

	if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		std::cout << mouse_x << " " << mouse_y << '\n';

		if (mouse_x >= 365 && mouse_x <= 417 && mouse_y >= 255 && mouse_y <= 297)
		{
			IsSnow = 1 - IsSnow;
			std::cout << "sgfdbmsdfjnbjflsxnjdfxnz fgbl";
		}
		else if (mouse_x >= 365 && mouse_x <= 423 && mouse_y >= 320 && mouse_y <= 370)
		{
			king_tale_color++;
			king_tale_color %= COLOR_COUNT;
			std::cout << "Hhhhhhhhhhhhhhhhhhhhhhhhhhhh";
		}
		else if (mouse_x >= 345 && mouse_x >= 390 && mouse_y >= 175 && mouse_y <= 190)
		{
			sett = false;
		}
	}
	if (IsSnow == true)
	{
		yes_button_.Render(365, 255, des, NULL);
	}
	else no_button_.Render(365, 255, des, NULL);
	tale_color[king_tale_color].Render(365, 325, des, NULL);

	SDL_RenderPresent(des);
	
	
}