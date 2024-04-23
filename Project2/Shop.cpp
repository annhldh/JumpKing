#pragma once
#include "Shop.h"
#include "CommonFunc.h"

void Shop::display_Shop(SDL_Renderer* des)
{


	back_ground.Render(0, 0, des, NULL);

	for (int i = 0; i < 4; i++)
	{
		choose.Render(85 + 100 * choosed[i], 85 + 100 * i, des, NULL);
	}
	for (int i = 0; i < HAT_COUNT; i++)
	{
		king_hat_display[i].Render(100 + 100 * i, 100, des, NULL);
		if (lock_hat[i] == false)
		{
			lock.Render(100 + 100 * i, 100, des, NULL);
			renderText(des, fonte, std::to_string(hat_cost[i]),color,100+100*i,160);
		}
		
	}
	for (int i = 0; i < COLOR_COUNT; i++)
	{
		king_tale_display[i].Render(100 + 100 * i, 200, des, NULL);
		if (lock_tale[i] == false)
		{
			lock.Render(100 + 100 * i, 200, des, NULL);
			renderText(des, fonte, std::to_string(tale_cost[i]), color, 100 + 100 * i, 260);
		}
	}
	for (int i = 0; i < CURSOR_COUNT; i++)
	{
		cursor_display[i].Render(100 + 100 * i, 300, des, NULL);
		if (lock_cursor[i] == false)
		{
			lock.Render(100 + 100 * i, 300, des, NULL);
			renderText(des, fonte, std::to_string(cursor_cost[i]), color, 100 + 100 * i, 360);
		}
	}
	for (int i = 0; i < 2; i++)
	{
		map_demo_block[i].Render(100 + 100 * i, 400, des, NULL);
		if (lock_map[i] == false)
		{
			lock.Render(100 + 100 * i, 400, des, NULL);
			renderText(des, fonte, std::to_string(map_cost[i]), color, 100 + 100 * i, 474);
		}

	}

	Back.Render(SCREEN_WIDTH - 200, 20, des, NULL);
	display_demo(des);
	exp_str = std::to_string(Achive_);
	exp_icon.Render(30, 40, des, NULL);
	
}


void Shop::Shop_act(SDL_Event* events)
{
	if (events->type = SDL_MOUSEBUTTONDOWN)
	{
		for (int i = 0; i < HAT_COUNT; i++)
		{

			if (mouse_x >= 90 + 100 * i && mouse_x <= 160 + 100 * i && mouse_y >= 100 && mouse_y <= 150)
			{
				if (Achive_ >= hat_cost[i] && lock_hat[i] == false)
				{
					Achive_ -= hat_cost[i];
					lock_hat[i] = true;
				}
				if(lock_hat[i] == true)choosed[0] = i;
				King_hat = i;
			}		
		}
		for (int i = 0; i < COLOR_COUNT; i++)
		{

			if (mouse_x >= 90 + 100 * i && mouse_x <= 160 + 100 * i && mouse_y >= 200 && mouse_y <= 250) 
			{
				if (Achive_ >= tale_cost[i] && lock_tale[i] == false)
				{
					Achive_ -= tale_cost[i];
					lock_tale[i] = true;
				}
				if(lock_tale[i] == true)choosed[1] = i;
				king_tale_color = i;
			}
			

		}
		for (int i = 0; i < CURSOR_COUNT; i++)
		{

			if (mouse_x >= 90 + 100 * i && mouse_x <= 160 + 100 * i && mouse_y >= 300 && mouse_y <= 350) 
			{
				if (Achive_ >= cursor_cost[i] && lock_cursor[i] == false)
				{
					Achive_ -= cursor_cost[i];
					lock_cursor[i] = true;
				}
				if (lock_cursor[i] == true)
				{
					choosed[2] = i;
					SDL_Cursor* cursorr = SDL_CreateColorCursor(cursor[i], 0, 0);
					SDL_SetCursor(cursorr);
				}
			}

		}
		for (int i = 0; i < 2; i++)
		{

			if (mouse_x >= 90 + 100 * i && mouse_x <= 160 + 100 * i && mouse_y >= 390 && mouse_y <= 450) 
			{
				if (Achive_ >= map_cost[i] && lock_map[i] == false)
				{
					Achive_ -= map_cost[i];
					lock_map[i] = true;
				}
				if (lock_map[i] == true)
				{
					choosed[3] = i;
					tile_style_ = i;

				}

			}

		}
		if (mouse_x >= 760 && mouse_x <= 868 && mouse_y >= 20 && mouse_y <= 101)
		{
			OnShop_ = false;
			stage_val = -1;
		}
	}
}

void Shop::load_custom(SDL_Renderer* des)
{

	back_ground.LoadImg("img//Shop//back_ground.jpg", des);
	lock.LoadImg("img//Shop//lock.png", des);
	Back.LoadImg("img//Shop//Back.png", des);
	exp_icon.LoadImg("img//EXP.png",des);
	choose.LoadImg("img//Shop//choose.png", des);
	fonte = TTF_OpenFont("Cutout.ttf", 20);

	char nam[] = "img//Shop//hat_n.png";
	for (int i = 0; i < HAT_COUNT; i++)
	{
		nam[15] = i + '0';
		king_hat_display[i].LoadImg(nam, des);

	}
	char nam2[] = "img//Shop//Cursor_n.png";
	for (int i = 0; i < CURSOR_COUNT ;i++)
	{
		nam2[18] = i + '0';
		cursor_display[i].LoadImg(nam2, des);
		cursor[i]= IMG_Load(nam2);
	}
	char nam3[] = "img//Shop//jump_effect_n.png";
	for (int i = 0; i < COLOR_COUNT; i++)
	{
		nam3[23] = i + '0';
		king_tale_display[i].LoadImg(nam3, des);
		
	}
	char nam4[] = "img//Shop//demo_n.png";
	for (int i = 0; i < HAT_COUNT; i++)
	{
		nam4[16] = i + '0';
		demo[i].LoadImg(nam4, des);
	}
	
	char nam5[] = "img//Shop//demo_block_n.png";
	for (int i = 0; i < 2; i++)
	{
		nam5[22] = i + '0';
		map_demo_block[i].LoadImg(nam5, des);
		
	}
	char nam6[] = "img//Shop//map_demo_n.png";
	for (int i = 0; i < 2; i++)
	{
		nam6[20] = i + '0';
		map_demo[i].LoadImg(nam6, des);
	}

	for (int i = 0; i < 8; i++)
	{
		clip[i].x = 248*i;
		clip[i].y = 0;
		clip[i].w = 248;
		clip[i].h = 288;
	}
	for (int i = 0; i < 7; i++)
	{
		tale_demo_rect[i].w = 140 - 20 * i;
		tale_demo_rect[i].h = 140 - 20 * i;
		tale_demo_rect[i].x = 700 - 100 - i * 110;
		tale_demo_rect[i].y = 300 + 288 - 140 + i * 10;
	}
	for (int i = 0; i < 8; i++)
	{
		map_demo_clip[i].x = i * 16;
		map_demo_clip[i].y = 0;
		map_demo_clip[i].w = 128 * 6;
		map_demo_clip[i].h = 128;
	}

}

void Shop::display_demo(SDL_Renderer* des)
{

	if (choosed[1] > 0)for (int i = 0; i < 7; i++)
	{
		king_tale_display[choosed[1]].Render(500, 500, des, NULL, 0, 0, &tale_demo_rect[i]);
		
	}

	demo_rect.h = demo[choosed[0]].rect_.h;
	demo_rect.y = SCREEN_HEIGHT - 120 - demo[choosed[0]].rect_.h;
	demo[choosed[0]].Render(600, 200, des, &clip[frame_demo],0,0,&demo_rect);
	if (loop % 200 == 0)frame_demo++;
	if (frame_demo >= 8) frame_demo = 0;
	
	
	for (int i = 0; i < 8; i++)
	{
		map_demo[choosed[3]].Render(300, 608, des, &map_demo_clip[frame_demo]);
	}

}