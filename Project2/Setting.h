#pragma once
#ifndef SETTING_H_
#define SETTING_H_

#include "Object.h"
#define COLOR_COUNT 5
struct Setting
{

	Object setting_;
	Object yes_button_;
	Object no_button_;
	Object tale_color[COLOR_COUNT];

	void setting(SDL_Renderer* des, SDL_Event events);

};

#endif // !SETTING_H_
