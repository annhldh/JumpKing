#pragma once
#ifndef TUTOTIAL_H_
#define TUTORIAL_H_
#include "Object.h"
#include "CommonFunc.h"
#include "SFX.h"
struct Tutorial
{
	Object tutor[3];
	Object Tutor_button;
	int frame_ = 0;
	int y_frame_[700];

	void Display_tutorial(SDL_Renderer* des);
	void loadTutor(SDL_Renderer* des);
	void Buttton(SDL_Event *event);
};

#endif // !TUTOTIAL_H_
