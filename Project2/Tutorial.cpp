#pragma once
#include "Tutorial.h"

void Tutorial::Display_tutorial(SDL_Renderer* des)
{
	if (isTutor == true)
	{
		tutor[GAME_MODE].Render(0, y_frame_[frame_], des, NULL);
		if ( frame_ < 679)frame_+= frame_val_;
		if (frame_ < 20)
		{
			frame_val_ = 20;
			frame_ = 20;
			isTutor = false;
		}
	}
	else Tutor_button.Render(0, 0, des, NULL);
}

void Tutorial::loadTutor(SDL_Renderer* des)
{
	char nam[] = "img//tutor_n.png";
	for (int i = 0; i < 3; i++)
	{
		nam[11] = i + '0';
		tutor[i].LoadImg(nam, des);
	}
	Tutor_button.LoadImg("img//tutor_button.png", des);

	
	for (int i = 0; i < 700; i++)
	{
		y_frame_[i] = -800 +i;
	}

}

void Tutorial:: Buttton(SDL_Event* event)
{
	if (event->type == SDL_MOUSEBUTTONDOWN )
	{
		if (mouse_x <= 75 && mouse_y <= 75 && isTutor == false) isTutor = true;

	}
	if (isTutor == true && event->type == SDL_KEYDOWN)
	{
		frame_val_ = -20;
		frame_ -= 20;
	}
	

}