#pragma once
#ifndef SHOP_H_
#define SHOP_H_
#include "Object.h"
#include "Setting.h"
#include "King.h"
#include "CommonFunc.h"

class Shop
{
public:

	Object back_ground;
	Object king_hat_display[HAT_COUNT];
	bool lock_hat[HAT_COUNT] = {1,0,0};
	Object king_tale_display[COLOR_COUNT];
	bool lock_tale[COLOR_COUNT] = { 1,0,0,0,0 };
	Object cursor_display[CURSOR_COUNT];
	SDL_Surface* cursor[CURSOR_COUNT];
	bool lock_cursor[CURSOR_COUNT] = { 1,0,0,0,0,0,0 };
	bool lock_map[2] = { 1,0 };
	SDL_Color color = { 234,63,247 };

	int choosed[4] = { 0,0,0,0 };

	int hat_cost[HAT_COUNT] = { 1000,2000,3000 };
	int tale_cost[COLOR_COUNT] = { 2000,2000,2000,3000,3000 };
	int cursor_cost[CURSOR_COUNT] = { 2000,1500,1500,3000,3000,5000,7000 };
	int map_cost[2] = { 0,4000 };

	int frame_demo = 0;
	SDL_Rect clip[8];
	Object demo[HAT_COUNT];
	Object map_demo[2];
	Object map_demo_block[2];
	SDL_Rect tale_demo_rect[7];
	SDL_Rect map_demo_clip[8];

	Object lock;
	Object Back;
	Object choose;

	SDL_Rect demo_rect = { 700,300,248,208 };

	void display_Shop(SDL_Renderer* des);
	void Shop_act(SDL_Event* events);
	void load_custom(SDL_Renderer* des);
	void display_demo(SDL_Renderer* des);
	void LoadShopData();
	void SaveShopData();


	TTF_Font* fonte;
	std::string exp_str;
	Object exp_icon;

	std::ifstream shop_data_in;
	std::ofstream shop_data_out;
};


#endif // !SHOP_H_
