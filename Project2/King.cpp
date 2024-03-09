#pragma once
#include "King.h"
#include "CommonFunc.h"
#include <iostream>
King::King()
{
	x_stand = 700;
	y_stand = 2000;

	delta_x = 0;
	delta_y = 0;
    for ( int i = 0; i < COUNT_ACTION; i++ ) Action[i] = 0;
    on_ground = false;
	turn = RIGHT;
	jump_forces = 0;
}
King:: ~King()
{
	Free();
}

void King::Control(SDL_Event events, SDL_Renderer* des)
{
    if (events.type == SDL_KEYDOWN && on_ground==true)
    {
        if (events.key.keysym.sym == SDLK_UP)
        {
            Action[JUMP] = 1;
        }


        if (events.key.keysym.sym == SDLK_RIGHT)
        {
       
            Action[RIGHT] = 1;
            Action[LEFT] = 0;
			turn = RIGHT;

        }
        else if (events.key.keysym.sym == SDLK_LEFT)
        {
    
            Action[LEFT] = 1;
            Action[RIGHT] = 0;
			turn = LEFT;
        }

    }
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{

			Action[RIGHT] = 0;
		}
		break;
		case SDLK_LEFT:
		{

			Action[LEFT] = 0;
		}
		break;
		case SDLK_UP:
		{
			Action[JUMP] = 0;


		}
		break;
		}

	}





}


void King::MoveAction(Map &map)
{
   
    if (Action[JUMP] == 1)
    {
        if (on_ground == true)
        {
			jump_forces+=1;
			if (jump_forces >= 50) jump_forces = 50;
        }
  
    }
	else if (Action[JUMP] == 0 && jump_forces > 0)
	{
		if (jump_forces >= 10)
		{
			delta_y -= 10;
			jump_forces -= 10;
		}

		else
		{
			delta_y -= jump_forces;
			jump_forces = 0;

		}
		on_ground = false;
	}
	if (on_ground == false)
	{
		if (turn == RIGHT)	delta_x += 8;
		else delta_x -= 8;
	}
	if (on_ground == true)
	{
		if (Action[LEFT] == 1)
		{
			delta_x -= 8;

		}
		else if (Action[RIGHT] == 1)
		{
			delta_x += 8;
		}
	}



		delta_y += 2;
		if (delta_y >= 15) delta_y = 15;



    CheckMap(map);

    delta_x = 0;
 /*   delta_y = 0*/;
}


void King::CheckMap(Map& map_data)
{
	on_ground = false;
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;
	//check horizontal
	int height_min = (rect_.h < TILE_SIZE ? rect_.h : TILE_SIZE);


	x1 = (x_stand + delta_x) / TILE_SIZE;
	x2 = (x_stand + delta_x + rect_.w - 1) / TILE_SIZE;

	y1 = (y_stand) / TILE_SIZE;
	y2 = (y_stand + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (delta_x > 0) //main object is moving to right
		{
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];


			if (val1 != BLANK_TILE || val2 != BLANK_TILE)
			{
				x_stand = (x2) * TILE_SIZE- 1-rect_.w;
				if (on_ground == false)
				{
					turn = 1 - turn;
					delta_x *= -0.3;
					jump_forces /= 1.5;
				}

			}
		}
		else if (delta_x < 0)
		{			
			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
			{
				x_stand = (x1+1 ) * TILE_SIZE;
				if (on_ground == false)
				{
					turn = 1 - turn;
					delta_x *= -0.3;
					jump_forces /= 1.5;
				}
			}
	

		}
	}

	//check vertical

	int width_min = (rect_.w<TILE_SIZE?  rect_.w: TILE_SIZE);
	x1 = (x_stand) / TILE_SIZE;
	x2 = (x_stand + width_min) / TILE_SIZE;

	y1 = (y_stand + delta_y) / TILE_SIZE;
	y2 = (y_stand + delta_y + rect_.h - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
	{
		if (delta_y > 0)
		{
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];
			if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
			{
				y_stand = (y2)*TILE_SIZE  - rect_.h;			
				delta_y = 0;

				on_ground = true;

			}
		}

		else if (delta_y < 0)
		{
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y1][x1];

			
			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
			{
				y_stand = (y1 + 1) * TILE_SIZE;
				delta_y = 0;

			}
		}
	}
	x_stand += delta_x;
	y_stand += delta_y;


    
}