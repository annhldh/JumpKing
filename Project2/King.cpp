#pragma once
#include "King.h"
#include "CommonFunc.h"
#include "Sound.h"
#include "SFX.h"
#include <iostream>

King::King()
{
	
	x_stand = 608;
	y_stand = 8800;
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
	Timer = 0;
	key_ = 1;
	stage_ = 1;

}
King:: ~King()
{
	Free();
}

void King::Control(SDL_Event events, SDL_Renderer* des)
{
    if (events.type == SDL_KEYDOWN && on_ground==true)
    {
        if (events.key.keysym.sym == SDLK_UP)  if (on_ground == true && delta_y == 0 && delta_x == 0)
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
		case SDLK_UP:if(on_ground==true)
		{
			display_sound(jumping);
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
			if (jump_forces >= 65) val = -1;
			else if (jump_forces <= 0) val = 1;
			jump_forces += val;
	
  
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
	if (on_ground == true && delta_y==0 && Action[JUMP] == 0)
	{
		if (Action[LEFT] == 1)
		{
			delta_x -= 6;
			display_sound(walking);

		}
		else if (Action[RIGHT] == 1)
		{
			delta_x += 6;	
			display_sound(walking);

		}
	}

		delta_y += 2;
		if (delta_y >= 32) delta_y = 32;



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
	y2 = (y_stand + height_min-1) / TILE_SIZE;


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

			else if (!(map_data.IsNonCollisionBlock(val1) && map_data.IsNonCollisionBlock(val2) && map_data.IsNonCollisionBlock(val3) && map_data.IsNonCollisionBlock(val4)))
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
			else if (!(map_data.IsNonCollisionBlock(val1) && map_data.IsNonCollisionBlock(val2) && map_data.IsNonCollisionBlock(val3) && map_data.IsNonCollisionBlock(val4)))
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
			if (val3 == 4)
			{
				map_data.tile[y2][x3] = 0;
				money_++;
			}
			if (val4 == 4)
			{
				map_data.tile[y2][x4] = 0;
				money_++;
			}
			if (val1 == 25)
			{
				map_data.tile[y2][x1] = BLANK_TILE;
				key_++;
			}
			if (val2 == 25)
			{
				map_data.tile[y2][x2] = 0;
				key_++;
			}
			if (val3 == 25)
			{
				map_data.tile[y2][x3] = 0;
				key_++;
			}
			if (val4 == 25)
			{
				map_data.tile[y2][x4] = 0;
				key_++;
			}
			else if (!(map_data.IsNonCollisionBlock(val1) && map_data.IsNonCollisionBlock(val2) && map_data.IsNonCollisionBlock(val3) && map_data.IsNonCollisionBlock(val4)))
			{
				y_stand = (y2)*TILE_SIZE - rect_.h;
				delta_y = 0;
				if (on_ground == false) display_sound(landing);
				on_ground = true;
				lost_height -= y_stand;
				Timer++;
				if (lost_height < -2000)
				{
					Action[FACE_DOWN] = true;
					Life--;
					display_sound(fall);
					std::cout << Life;
				}
				lost_height = y_stand;
				if ((val1 == 11) || (val2 == 11) || (val3 == 11) || (val4 == 11) )
				{
					if (turn == LEFT) delta_x = -3;
					else delta_x = 3;
				}
				if (val1 > 56 && val1<=60)
				{
					display_sound(icebreaking);
					map_data.tile[y2][x1] -= Timer / 60;
					
				}
				if (val2 > 56 && val2 <= 60)
				{
					display_sound(icebreaking);
					map_data.tile[y2][x2] -= Timer / 60;
				}
				if (val3 > 56 && val3 <= 60)
				{
					display_sound(icebreaking);
					map_data.tile[y2][x3] -= Timer / 60;
				
				}
				if (val4 > 56 && val4 <= 60)
				{
					display_sound(icebreaking);
					map_data.tile[y2][x4] -= Timer / 60;
				}
				//if (val1 <= 56 && val1>53) map_data.tile[y2][x1] = 0;
				//if (val2 <= 56 && val2>53) map_data.tile[y2][x2] = 0;
				//if (val3 <= 56 && val3>53) map_data.tile[y2][x3] = 0;
				//if (val4 <= 56 && val4>53) map_data.tile[y2][x4] = 0;

				Timer %= 60;


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
			if (val3 == 4)
			{
				map_data.tile[y1][x3] = 0;
				money_++;
			}
			if (val4 == 4)
			{
				map_data.tile[y1][x4] = 0;
				money_++;
			}
			if (val1 == 25)
			{
				map_data.tile[y1][x2] = BLANK_TILE;
				key_++;
			}
			if (val2 == 25)
			{
				map_data.tile[y1][x1] = 0;
				key_++;
			}
			if (val3 == 25)
			{
				map_data.tile[y1][x3] = 0;
				key_++;
			}
			if (val4 == 25)
			{
				map_data.tile[y1][x4] = 0;
				key_++;
			}

			if (!(map_data.IsNonCollisionBlock(val1) && map_data.IsNonCollisionBlock(val2)&& map_data.IsNonCollisionBlock(val3)&& map_data.IsNonCollisionBlock(val4) ))
			{
				y_stand = (y1 + 1) * TILE_SIZE;
				delta_y = 0;

			}
		}
	}
	x_stand += delta_x;
	y_stand += delta_y;
	Get_max_height();
	if (map_data.tile[y1][x1] >= 26 && map_data.tile[y1][x1] <= 45 && key_ > 0)
	{
		stage_ ++;

	}



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
		if (turn == LEFT)
		{
			mTexture = KingImg[FACE_DOWN_LEFT].mTexture;
			rect_ = KingImg[FACE_DOWN_LEFT].rect_;
		}
		
		else
		{
			mTexture = KingImg[FACE_DOWN_RIGHT].mTexture;
			rect_ = KingImg[FACE_DOWN_RIGHT].rect_;
		}
	}
	else if (Action[JUMP] == true)
	{
		if (turn == LEFT)
		{
			mTexture = KingImg[PRESS_LEFT].mTexture;
			rect_ = KingImg[PRESS_LEFT].rect_;
		}

		else
		{
			mTexture = KingImg[PRESS_RIGHT].mTexture;
			rect_ = KingImg[PRESS_RIGHT].rect_;
		}
	}
	else if (on_ground == false && delta_y<=0)
	{

		if (turn == LEFT)
		{
			mTexture = KingImg[JUMP_LEFT].mTexture;
			rect_ = KingImg[JUMP_LEFT].rect_;
		}

		else
		{
			mTexture = KingImg[JUMP_RIGHT].mTexture;
			rect_ = KingImg[JUMP_RIGHT].rect_;
		}
	}
	else if (on_ground == false && delta_y > 0)
	{
		if (turn == LEFT)
		{
			mTexture = KingImg[FALL_LEFT].mTexture;
			rect_ = KingImg[FALL_LEFT].rect_;
		}

		else
		{
			mTexture = KingImg[FALL_RIGHT].mTexture;
			rect_ = KingImg[FALL_RIGHT].rect_;
		}
	}
	
	else if (Action [LEFT] +Action[RIGHT] >0)
	{
		if (turn == LEFT)
		{
			mTexture = KingImg[RUN_LEFT].mTexture;
			rect_ = KingImg[RUN_LEFT].rect_;
		}

		else
		{
			mTexture = KingImg[RUN_RIGHT].mTexture;
			rect_ = KingImg[RUN_RIGHT].rect_;
		}

	}
	else 
	{
		if (turn == LEFT)
		{
			mTexture = KingImg[STAND_LEFT].mTexture;
			rect_ = KingImg[STAND_LEFT].rect_;
		}
		else
		{
			mTexture = KingImg[STAND_RIGHT].mTexture;
			rect_ = KingImg[STAND_RIGHT].rect_;
		}
		
	
	}

	set_clips();
	rect_.w /= NUMBER_OF_FRAME;
	Render(x_pos, y_pos, des, &frame_clip_[frame_]);
}


void King::set_begin()
{
	Life = 2;

	set_clips();
	Action[3] = false;

	x_stand = 808;
	y_stand = 8800;
	delta_x = 0;
	delta_y = 0;
	lost_height = 2000;
	jump_forces = 0;
	on_ground = true;
	turn = 0;
	stage_ = 1;
	max_height = 0;

}

void King::loadKingImg(SDL_Renderer *des)
{
	KingImg[STAND_LEFT].LoadImg("img//King//king_left.png", des);
	KingImg[STAND_RIGHT].LoadImg("img//King//king_right.png", des);
	KingImg[RUN_LEFT].LoadImg("img//King//king_run_left.png", des);
	KingImg[RUN_RIGHT].LoadImg("img//King//king_run_right.png", des);
	KingImg[FALL_LEFT].LoadImg("img//King//king_fall_left.png", des);
	KingImg[FALL_RIGHT].LoadImg("img//King//king_fall_right.png", des);
	KingImg[JUMP_LEFT].LoadImg("img//King//king_jump_left.png", des);
	KingImg[JUMP_RIGHT].LoadImg("img//King//king_jump_right.png", des);
	KingImg[PRESS_LEFT].LoadImg("img//King//king_press_left.png", des);
	KingImg[PRESS_RIGHT].LoadImg("img//King//king_press_right.png", des);
	KingImg[FACE_DOWN_LEFT].LoadImg("img//King//face_down_left.png", des);
	KingImg[FACE_DOWN_RIGHT].LoadImg("img//King//face_down_right.png", des);


	
}

void King::Get_max_height()
{
	max_height = (max_height < (MAX_MAP_Y * TILE_SIZE - y_stand) ? (MAX_MAP_Y * TILE_SIZE - y_stand) : max_height);
}

void King::loadStage(int stage, GameMap& game_map, SDL_Renderer* des, Object &back_ground_)
{
	set_begin();
	char nameMap2[] = "map//map02.dat";
	nameMap2[9] = char(stage+'0');
	display_music_theme(music_theme[stage]);
	back_ground_.LoadImg("img//background" + std::to_string(stage) + ".png", des);
	game_map.LoadMap(nameMap2);

}