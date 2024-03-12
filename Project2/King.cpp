#pragma once
#include "King.h"
#include "CommonFunc.h"
#include <iostream>

King::King()
{
	
	x_stand = 608;
	y_stand = 2200;
	delta_x = 0;
	delta_y = 0;
    for ( int i = 0; i < COUNT_ACTION; i++ ) Action[i] = 0;
    on_ground = false;
	turn = RIGHT;
	jump_forces = 0;
	frame_ = 0;
	unframe_ = 0;
	lost_height = 0;
	Life = 2;
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
			Action[FACE_DOWN] = false;

        }


        if (events.key.keysym.sym == SDLK_RIGHT)
        {
       
            Action[RIGHT] = 1;
            Action[LEFT] = 0;
			turn = RIGHT;
			Action[FACE_DOWN] = false;

        }
        else if (events.key.keysym.sym == SDLK_LEFT)
        {
    
            Action[LEFT] = 1;
            Action[RIGHT] = 0;
			turn = LEFT;
			Action[FACE_DOWN] = false;
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
			lost_height = y_stand;
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
			
			
			if (jump_forces >= 50) val = -1;
			else if (jump_forces <= 0) val = 1;
			jump_forces += val;
			
        }
  
    }
	else if (Action[JUMP] == 0 && jump_forces > 0)
	{
		if (jump_forces >= 20)
		{
			delta_y -= 20;
			jump_forces -= 20;
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
		if (turn == RIGHT)	delta_x +=8;
		else delta_x -= 8;
	}
	if (on_ground == true)
	{
		if (Action[LEFT] == 1)
		{
			delta_x -= 6;

		}
		else if (Action[RIGHT] == 1)
		{
			delta_x += 6;
		}
	}

		delta_y += 2;
		if (delta_y >= 10) delta_y = 10;



    CheckMap(map);
	if (Action[JUMP] == true) frame_ = (jump_forces - 1) / (50 / NUMBER_OF_FRAME + 1);
	else
	{
		//tạo độ trễ chuyển frame
		unframe_++;
		frame_ += unframe_ / 6;
		unframe_ %= 6;
	}
	if (frame_ >= NUMBER_OF_FRAME) frame_ = 0;
    delta_x = 0;
 /*   delt_y = 0*/;
}

void King :: CenterEntityOnMap(GameMap& game_map)
{
	game_map.game_map_.start_x_ = x_stand - SCREEN_WIDTH / 2;
    if (x_stand < SCREEN_WIDTH / 2)
    {
        game_map.game_map_.start_x_ = 0;
        x_pos = x_stand;
    }
    else if (x_stand + SCREEN_WIDTH / 2 >= game_map.game_map_.max_x_)
    {
        game_map.game_map_.start_x_ = game_map.game_map_.max_x_ - SCREEN_WIDTH;
		x_pos = x_stand - game_map.game_map_.start_x_;
    }


	game_map.game_map_.start_y_ = y_stand - SCREEN_HEIGHT / 2;
	
    if (y_stand < SCREEN_HEIGHT / 2)
    {
        game_map.game_map_.start_y_ = 0;
        y_pos = y_stand;
    }
    else if (y_stand + SCREEN_HEIGHT / 2 >= game_map.game_map_.max_y_)
    {
        game_map.game_map_.start_y_ = game_map.game_map_.max_y_ - SCREEN_HEIGHT;
		y_pos = y_stand - game_map.game_map_.start_y_;
	}
	
}

void King::CheckMap(Map& map_data)
{
	
	int x1 = 0;
	int x2 = 0;
	int x3 = 0;
	int x4 = 0;

	int y1 = 0;
	int y2 = 0;
	int y3 = 0;
	int y4 = 0;
	//check horizontal
	int height_min = (rect_.h<TILE_SIZE  ? rect_.h: TILE_SIZE);


	x1 = (x_stand + delta_x) / TILE_SIZE;
	x2 = (x_stand + delta_x + rect_.w ) / TILE_SIZE;
	

	y1 = (y_stand) / TILE_SIZE;
	y2 = (y_stand + height_min-1 ) / TILE_SIZE;


	x3 = round(2.00 * x1 + x2) / 3;
	x4 = round(x1 + 2.00 * x2) / 3;
	y3 = round(2.00 * y1 + y2) / 3;
	y4 = round(y1 + 2.00 * y2) / 3;

	

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (delta_x > 0) //main object is moving to right
		{
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];
			int val3 = map_data.tile[y3][x2];
			int val4 = map_data.tile[y4][x2];

			if (val1 == 4 )
			{
				map_data.tile[y1][x2] = BLANK_TILE;
				money_++;
			}
			if (val2 == 4)
			{
				map_data.tile[y2][x2] = 0;
				money_++;
			}

			else if (val1 != BLANK_TILE || val2 != BLANK_TILE || val3 !=BLANK_TILE  || val4 !=BLANK_TILE)
			{
				x_stand = (x2) * TILE_SIZE-rect_.w-8;
				if (on_ground == false)
				{
					turn = 1 - turn;
					jump_forces /= 2.5;
					delta_x = -delta_x / abs(delta_x) * jump_forces/2;
					
				}

			}
		}
		else if (delta_x < 0)
		{		
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];
			int val3 = map_data.tile[y3][x1];
			int val4 = map_data.tile[y4][x1];
			if (map_data.tile[y1][x1] == 4)
			{
				map_data.tile[y1][x1] = BLANK_TILE;
				money_++;
			}
			 if (map_data.tile[y2][x1] == 4)
			{
				map_data.tile[y2][x1] = 0;
				money_++;
			}
			else if (val1 != BLANK_TILE || val2 != BLANK_TILE || val3 !=BLANK_TILE  || val4 !=BLANK_TILE  )
			{
				x_stand = (x1+1 ) * TILE_SIZE+8 ;
				if (on_ground == false)
				{
					turn = 1 - turn;
					jump_forces /= 2.5;
					delta_x =-delta_x/ abs(delta_x) * jump_forces/2;
				
				}
			}
	

		}
	}

	//check vertical

	int width_min = (rect_.w < TILE_SIZE ? rect_.w : TILE_SIZE);
	x1 = (x_stand) ; 
	x2 = (x_stand + rect_.w);

	y1 = (y_stand + delta_y) ;
	y2 = (y_stand + delta_y + rect_.h-1 ) ;
	
	x3 = round(2.00 * x1 + x2) / 3;
	x4 = round(x1 + 2.00 * x2) / 3;
	y3 = round(2.00 * y1 + y2) / 3;
	y4 = round(y1 + 2.00 * y2) / 3;

	x1 /= TILE_SIZE;
	x2 /= TILE_SIZE;
	x3 /= TILE_SIZE;
	x4 /= TILE_SIZE;
	y1 /= TILE_SIZE;
	y2 /= TILE_SIZE;
	y3 /= TILE_SIZE;
	y4 /= TILE_SIZE;


	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (delta_y > 0)
		{
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];
			int val3 = map_data.tile[y2][x3];
			int val4 = map_data.tile[y2][x4];
			
			if (val1== 4)
			{
				map_data.tile[y2][x1] = BLANK_TILE;
				money_++;
			}
			 if (val2 == 4)
			{
				map_data.tile[y2][x2] = 0;
				money_++;
			}
			 else if (val1 != BLANK_TILE || val2 != BLANK_TILE || val3 != BLANK_TILE || val4 != BLANK_TILE)
			 {
				 y_stand = (y2)*TILE_SIZE - rect_.h;
				 delta_y = 0;

				 on_ground = true;
				  lost_height -= y_stand;
				 if (lost_height < -400)
				 {
					 Action[FACE_DOWN] = true; 
					 Life--;
					 std ::cout << Life;
				 }
				 lost_height = y_stand;
				 

			

			 }
		}

		else if (delta_y < 0)
		{
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y1][x1];
			int val3 = map_data.tile[y1][x3];
			int val4 = map_data.tile[y1][x4];

			if (val1 == 4)
			{
				map_data.tile[y1][x2] = BLANK_TILE;
				money_++;
			}
			 if (val2 == 4)
			{
				map_data.tile[y1][x1] = 0;
				money_++;
			}
			if (val1 != BLANK_TILE || val2 != BLANK_TILE || val3 != BLANK_TILE || val4 != BLANK_TILE)
			{
				y_stand = (y1 + 1) * TILE_SIZE;
				delta_y = 0;

			}
		}
	}
	x_stand += delta_x;
	y_stand += delta_y;


}

void King::set_clips()
{
	if (rect_.w> 0 && rect_.h > 0) for (int i = 0; i < NUMBER_OF_FRAME; i++)
	{
		frame_clip_[i].x = i * rect_.w/NUMBER_OF_FRAME;
		frame_clip_[i].y = 0;
		frame_clip_[i].w = rect_.w/NUMBER_OF_FRAME;
		frame_clip_[i].h = rect_.h;
	}
}
void King::Show_frame(SDL_Renderer* des)
{
	if (Action[FACE_DOWN] == true)
	{
		if (turn == LEFT) LoadImg("img//King//face_down_left.png", des);
		else  LoadImg("img//King//face_down_right.png", des);
	}
	else if (Action[JUMP] == true)
	{
		if (turn == LEFT) LoadImg("img//King//king_press_left.png", des);

		else  LoadImg("img//King//king_press_right.png", des);
	}
	else if (on_ground == false && delta_y<=0)
	{
		if (turn == LEFT) LoadImg("img//King//king_jump_left.png", des);

		else  LoadImg("img//King//king_jump_right.png", des);
	}
	else if (on_ground == false && delta_y > 0)
	{
		if (turn == LEFT) LoadImg("img//King//king_fall_left.png", des);

		else  LoadImg("img//King//king_fall_right.png", des);
	}
	
	else if (Action [LEFT] +Action[RIGHT] >0)
	{
		if (turn == LEFT) LoadImg("img//King//king_run_left.png", des);

		else  LoadImg("img//King//king_run_right.png", des);

	}
	else 
	{
		if (turn == LEFT) LoadImg("img//King//king_left.png", des);

		else  LoadImg("img//King//king_right.png", des);
	
	}

	set_clips();


	rect_.w /= NUMBER_OF_FRAME;
	Render(x_pos, y_pos, des, &frame_clip_[frame_]);
}

