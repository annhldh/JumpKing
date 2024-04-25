#pragma once
#include "King.h"
#include "CommonFunc.h"
#include "Sound.h"
#include "SFX.h"
#include <iostream>

King::King()
{
	
	x_stand = 640;
	y_stand = 8800;
	delta_x = 0;
	delta_y = 0;
    for ( int i = 0; i < COUNT_ACTION; i++ ) Action[i] = 0;
    on_ground = false;
	turn = RIGHT;
	pre_turn = RIGHT;
	jump_forces = 0;
	frame_ = 0;
	unframe_ = 0;
	lost_height = 0;
	Life = 2;
	Timer = 0;
	time_xo = 0;
	key_ = 1;
	stage_ = 0;
	r_range = 3* TILE_SIZE;
	jump_effect_x.resize(30,808);
	jump_effect_y.resize(30, 9000);
	jump_effect_frame.resize(30, 0);
	King_hat = 0;
	
	
}
King:: ~King()
{
	Free();
}

void King::Control(SDL_Event events, SDL_Renderer* des, Map& map)
{
	X = false;
	if (events.key.keysym.sym == SDLK_x) X = true;
	if (events.type == SDL_KEYDOWN )
	{
		
		if (events.key.keysym.sym == SDLK_r)
		{
			key_ = 1;
			x_stand == 1160;
			y_stand = 681;
		}
		if (on_ground == true)
		{
			if (events.key.keysym.sym == SDLK_UP)  if (on_ground == true && delta_y == 0 && delta_x == 0)
			{
				Action[JUMP] = 1;
				Action[FACE_DOWN] = false;
				turn = NONE;

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
		case SDLK_UP:if (on_ground == true)
		{
			display_sound(jumping);
			lost_height = y_stand;
			Action[JUMP] = 0;
		}
			break;
		}

	}
	
	if (GAME_MODE==1 && events.type == SDL_MOUSEBUTTONDOWN && energy>0)
	{
		turn = NONE;
		on_ground = false;

		int vec_x = mouse_x - x_pos - rect_.w / 2;
		int vec_y = mouse_y - y_pos - rect_.h;

		tale_angle =  - std::atan(1.0 * vec_x / std::max(vec_y, 1))*180/M_PI;
	
		if (vec_x>= 10) turn = LEFT;
		else if( vec_x <= -10) turn = RIGHT;
		force = std::min(sqrt((vec_x) * (vec_x) + (vec_y) * (vec_y)), 400.0);
		if (vec_y <= 0) force = 400;
	
		force = std::min( 1.0*(400 - force) * (400 - force) / 160000 * 100,100.0);
		
		hori = std::min(abs(vec_x) / std::max(sqrt((vec_x) * (vec_x) + (vec_y) * (vec_y) ),1.0) * force/12,10.0);
		
		fly_force = abs(vec_y) / std::max(sqrt((vec_x) * (vec_x) + (vec_y) * (vec_y)),0.1) * force;

		energy--;

;	}
	else if (events.type == SDL_MOUSEBUTTONDOWN && connect_rope==true)
	{
			pull = true;

	}
	else if (events.type == SDL_MOUSEBUTTONUP)
	{
		if (pull == true )
		{
			pull = false;
			connect_rope = false;
		
			hori = cos(1.00*r_angle/180*M_PI) * rope_forces ;
		
			delta_y = -rope_forces * sin(1.00*r_angle/180*M_PI);
			rope_forces = 0;
			if (hori > 0) turn = LEFT;
			else turn = RIGHT;
			hori = abs(hori)*0.7;
		}
	}
	int m_x1, m_y1;
	double anglefake = 0;
	
	if (pull == true)
	{
		SDL_GetMouseState(&m_x1, &m_y1);
		if (r_length <= r_range + 40)
		{

			x_stand += m_x1 - pre_x;
			y_stand += m_y1 - pre_y;
			pre_pos_x += m_x1 - pre_x;
			pre_pos_y += m_y1 - pre_y;

			rope_forces = std::min(std::max(r_length - r_range, 0), 60);
		}
		else
		{
			if ((rope_stand_x1 -m_x1) == 0) anglefake = 90;
			else
			{
				anglefake = std::atan(1.0 * (m_y1 - rope_stand_y1 + map.start_y_) / (m_x1 - rope_stand_x1 + map.start_x_));
				if (anglefake < 0) anglefake = M_PI + anglefake;
			}
	
			x_stand = rope_stand_x1 + (r_range + 40) * cos(anglefake )*0.9;
			y_stand = rope_stand_y1 + (r_range + 40) * sin(anglefake )*0.9;
			pre_pos_x = x_stand - map.start_x_;
			pre_pos_y = y_stand - map.start_y_;
			rope_forces = std::min(std::max(r_length - r_range, 0), 60);

		}
		pre_x = m_x1;
		pre_y = m_y1;
		

	}
	else
	{
		SDL_GetMouseState(&pre_x, &pre_y);
		pre_pos_x = x_pos;
		pre_pos_y = y_pos;


	}





}


void King::MoveAction(Map &map)
{
   

    if (Action[JUMP] == 1&& connect_rope==false)
    {
			if (jump_forces >= MAX_JUMP_FORCE) val = -1;
			else if (jump_forces <= 0) val = 1;
			jump_forces += val;
	
  
    }
	else if (Action[JUMP] == 0 && jump_forces > 0 && GAME_MODE !=1)
	{
	
		if (jump_forces >= 14)
		{
			delta_y -= 14;
			jump_forces -= 14;
		}

		else
		{
			delta_y -= jump_forces;
			jump_forces = 0;

		}


		on_ground = false;
	}

	if (sqrt((x_stand - jump_effect_x[jump_effect_index]) * (x_stand - jump_effect_x[jump_effect_index]) + (y_stand - jump_effect_y[jump_effect_index]) * (y_stand - jump_effect_y[jump_effect_index])) >= footprint_distance)
	{
		jump_effect_index = (jump_effect_index + 1) % 30;
		jump_effect_x[jump_effect_index] = x_stand;
		jump_effect_y[jump_effect_index] = y_stand;
		jump_effect_frame[jump_effect_index] = 0;

	}
	

	if (on_ground == false && connect_rope==false)
	{
		if (turn== RIGHT)	delta_x += hori;
		else if ( turn == LEFT) delta_x -= hori;
	}
	if (GAME_MODE == 1 && fly_force>0 && delta_y>=-5)
	{
		
		delta_y    =- std::min(fly_force, 15);
		fly_force -= std::min(15,fly_force);
		

	}
	if (on_ground == true && delta_y==0 && Action[JUMP] == 0)
	{
		if (Action[LEFT] == 1)
		{
			delta_x -= 4;
			display_sound(walking);

		}
		else if (Action[RIGHT] == 1)
		{
			delta_x += 4;	
			display_sound(walking);

		}
	}

	delta_y += GRAVITY;
	if (delta_y >= MAX_GRAVITY) delta_y = MAX_GRAVITY;


	if (turn == RIGHT || turn == LEFT)
	{
			pre_turn = turn;
	}

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


	game_map.game_map_.start_y_ = y_stand - 2 * SCREEN_HEIGHT / 3;
		
	if (y_stand < 2 * SCREEN_HEIGHT / 3)
	{
		game_map.game_map_.start_y_ = 0;
		y_pos = y_stand;
	}
	else if (y_stand + SCREEN_HEIGHT / 3 >= game_map.game_map_.max_y_)
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
		if (delta_x >= 0) //main object is moving to right
		{
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];
			int val3 = map_data.tile[y3][x2];
			int val4 = map_data.tile[y4][x2];

			if (val1 == 12 && key_>0)
			{
				map_data.tile[y1][x2] = 13;
				isVictory = true;
			}
			else if (val2 == 12 && key_>0)
			{
				map_data.tile[y2][x2] = 13;
				isVictory = true;
			}
			if (val1 == 25)
			{
				map_data.tile[y1][x2] = BLANK_TILE;
				key_++;
			}
			else if (val2 == 25)
			{
				map_data.tile[y2][x2] = 0;
				key_++;
			}
			else if (val3 == 25)
			{
				map_data.tile[y3][x2] = 0;
				key_++;
			}
			else if (val4 == 25)
			{
				map_data.tile[y4][x2] = 0;
				key_++;
			}
			if (val1 == 4)
			{
				map_data.tile[y1][x2] = BLANK_TILE;
				money_++;
			}
			if (val2 == 4)
			{
				map_data.tile[y2][x2] = 0;
				money_++;
			}
			if (val1 == 48 || val2== 48 || val3 == 48 || val4==48)
			{
				Life--;
				isDiebyLazer = true;
			}
			else if (!(map_data.IsNonCollisionBlock(val1) && map_data.IsNonCollisionBlock(val2) && map_data.IsNonCollisionBlock(val3) && map_data.IsNonCollisionBlock(val4)))
			{
				x_stand = (x2) * TILE_SIZE-rect_.w-8;
				if (on_ground == false)
				{
					turn = 1 - turn;
					jump_forces /= 2.5;
					delta_x = -delta_x / abs(delta_x) * jump_forces/2;
					Action[CLASH] = true;
					
				}

			}
		}
		else if (delta_x < 0)
		{		
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];
			int val3 = map_data.tile[y3][x1];
			int val4 = map_data.tile[y4][x1];

			if (val1 == 12 && key_>0)
			{
				map_data.tile[y1][x1] = 13;
				isVictory = true;
			}
			else if (val2 == 12 && key_>0)
			{
				map_data.tile[y2][x1] = 13;
				isVictory = true;

			}
			if (val1 == 25)
			{
				map_data.tile[y1][x1] = BLANK_TILE;
				key_++;
			}
			else if (val2 == 25)
			{
				map_data.tile[y2][x1] = 0;
				key_++;
			}
			else if (val3 == 25)
			{
				map_data.tile[y3][x1] = 0;
				key_++;
			}
			else if (val4 == 25)
			{
				map_data.tile[y4][x1] = 0;
				key_++;
			}
			if (val1 == 4)
			{
				map_data.tile[y1][x1] = BLANK_TILE;
				money_++;
			}
			if (val2 == 4)
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
					Action[CLASH] = true;
				
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
		if (delta_y >= 0)
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
			else if (val2 == 25)
			{
				map_data.tile[y2][x2] = 0;
				key_++;
			}
			else if (val3 == 25)
			{
				map_data.tile[y2][x3] = 0;
				key_++;
			}
			else if (val4 == 25)
			{
				map_data.tile[y2][x4] = 0;
				key_++;
			}
			
			if (val1 == 49 ||val4==49|| val3==49)
			{
				delta_x = 9;
				delta_y = 9;
			}
			if (!(map_data.IsNonCollisionBlock(val1) && map_data.IsNonCollisionBlock(val2) && map_data.IsNonCollisionBlock(val3) && map_data.IsNonCollisionBlock(val4)))
			{
				y_stand = (y2)*TILE_SIZE - rect_.h;
				delta_y = 0;
				if (on_ground == false)
				{
					display_sound(landing);
					is_landing = true;
					landing_x = x_stand + rect_.w/2 - landing_effect[0].rect_.w / 2;
					landing_y = y_stand + rect_.h - landing_effect[0].rect_.h;

				}


				on_ground = true;
				lost_height -= y_stand;
				Action[CLASH] = false;
				Timer++;
				if (lost_height < -2000)
				{
				
					Action[FACE_DOWN] = true;
					Life--;
					display_sound(fall);
			
				}
				lost_height = y_stand;
				if ((val1 == 11) || (val2 == 11) || (val3 == 11) || (val4 == 11) )
				{
					if (pre_turn == LEFT) delta_x = -2;
					else delta_x = 2;
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
				if (val1 == 48 || val2 == 48 || val3 == 48 || val4 == 48)
				{
					Life--;
					isDiebyLazer = true;
				}
				

				Timer %= 60;

				hori = 8;
				energy = 3;

			}
		}

		else if (delta_y <= 0)
		{
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y1][x1];
			int val3 = map_data.tile[y1][x3];
			int val4 = map_data.tile[y1][x4];
			if (val1 == 48 || val2==48||val3==48 ||val4==48)
			{
				Life--;
				isDiebyLazer = true;
			}

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



	Get_max_height(); 
	if(King_hat==1) y1 += 1;
	int val1 = map_data.tile[y1][x1];
	int val2 = map_data.tile[y1][x2];
	int val3 = map_data.tile[y2][x1];
	int val4 = map_data.tile[y2][x2];
	//if (val1 == 90 && X == true && map_data.x_cnt == map_data.o_cnt && (loop - time_xo) >= 60)
	//{
	//	map_data.tile[y1][x1] = 91;
	//	map_data.x_cnt++;
	//	map_data.Update_xo(1);
	//	time_xo = loop;

	//	if (map_data.x_cnt - map_data.o_cnt == 1)
	//	{
	//		map_data.xo_rival();
	//		map_data.Update_xo(0);
	//		map_data.o_cnt++;
	//	}
	//	if (map_data.Check_xo() == 1)std::cout << "X WIN";
	//	else if (map_data.Check_xo() == 0)std::cout << "O WIN";


	//}

	if ((val1 >= 26 && val1 <= 45) && (val2 >= 26 && val2 <= 45))
	{
		stage_++;
		key_ = 0;
		display_sound(door_open);
	}

	else if (val1 == 85)
	{
		stage_ = 1;
		display_sound(door_open);
	}
	else if (val1 == 86)
	{
		OnShop_ = true;
		display_sound(door_open);
	}
	else if (val1 == 87)
	{
		stage_ = 1;
		GAME_MODE = 1;
		GRAVITY = 1;
		MAX_GRAVITY = 16;
		display_sound(door_open);
	
	}
	else if (val1 == 88)
	{
		stage_ = 3;
		display_sound(door_open);
	
	}

	if (check_rope(map_data) == false) bounderies = 45;
	else if (connect_rope==false && check_rope(map_data) == true)connect_rope = true;
	else if (y_stand < rope_stand_y1 && pull == false)
	{
		connect_rope = false;
	}
	if (connect_rope == true && pull==false )
	{
		if (bounderies > 12)

		{
			bounderies -= 0.1;
	
			if (rope_stand_x1 - x_stand >= bounderies)
			{
				turn = RIGHT;
			}
			else if (rope_stand_x1 - x_stand <= -bounderies)
			{
				turn = LEFT;
			}


			if (turn == LEFT) delta_x = round(-6.0 * bounderies * bounderies / 64 / 64 * (1 - (abs(1.0 * rope_stand_x1 - x_stand) / 64))) - 1;
			else delta_x = round(6.0 * bounderies * bounderies / 64 / 64 * (1 - (abs(1.0 * rope_stand_x1 - x_stand) / 64))) + 1;
		}

		else bounderies = 0;
		delta_y = 0;
		y_stand = rope_stand_y1 - rect_.h / 2 + sqrt(std::max(r_range * r_range - (rope_stand_x1 - x_stand) * (rope_stand_x1 - x_stand), 0));
	}
	if (pull == true)
	{
		delta_x = 0;
		delta_y = 0;	
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

		if (turn == LEFT)
		{
			mTexture = KingImg[FACE_DOWN_LEFT][King_hat].mTexture;
			rect_ = KingImg[FACE_DOWN_LEFT][King_hat].rect_;
		}
		
		else
		{
			mTexture = KingImg[FACE_DOWN_RIGHT][King_hat].mTexture;
			rect_ = KingImg[FACE_DOWN_RIGHT][King_hat].rect_;
		}
	}
	else if (Action[JUMP] == true)
	{
		if (pre_turn == LEFT)
		{
			mTexture = KingImg[PRESS_LEFT][King_hat].mTexture;
			rect_ = KingImg[PRESS_LEFT][King_hat].rect_;
		}

		else /*(turn == RIGHT)*/
		{
			mTexture = KingImg[PRESS_RIGHT][King_hat].mTexture;
			rect_ = KingImg[PRESS_RIGHT][King_hat].rect_;
		}

	}
	else if (on_ground == false && delta_y<=0)
	{
		if (Action[CLASH] == true)
		{
			if (turn == LEFT)
			{
				mTexture = KingImg[CLASH_LEFT][King_hat].mTexture;
				rect_ = KingImg[CLASH_LEFT][King_hat].rect_;
			}

			else
			{
				mTexture = KingImg[CLASH_RIGHT][King_hat].mTexture;
				rect_ = KingImg[CLASH_RIGHT][King_hat].rect_;
			}
		}
		else
		{
			if (pre_turn == LEFT)
			{
				mTexture = KingImg[JUMP_LEFT][King_hat].mTexture;
				rect_ = KingImg[JUMP_LEFT][King_hat].rect_;
			}

			else
			{
				mTexture = KingImg[JUMP_RIGHT][King_hat].mTexture;
				rect_ = KingImg[JUMP_RIGHT][King_hat].rect_;
			}
		}
	}
	else if (on_ground == false && delta_y > 0)
	{
		if (Action[CLASH] == true)
		{
			if (turn == LEFT)
			{
				mTexture = KingImg[CLASH_LEFT][King_hat].mTexture;
				rect_ = KingImg[CLASH_LEFT][King_hat].rect_;
			}

			else
			{
				mTexture = KingImg[CLASH_RIGHT][King_hat].mTexture;
				rect_ = KingImg[CLASH_RIGHT][King_hat].rect_;
			}
		}
		else
		{
			if (pre_turn == LEFT)
			{
				mTexture = KingImg[FALL_LEFT][King_hat].mTexture;
				rect_ = KingImg[FALL_LEFT][King_hat].rect_;
			}

			else
			{
				mTexture = KingImg[FALL_RIGHT][King_hat].mTexture;
				rect_ = KingImg[FALL_RIGHT][King_hat].rect_;
			}
		}
	}
	
	else if (Action [LEFT] +Action[RIGHT] >0)
	{
		if (turn == LEFT)
		{
			mTexture = KingImg[RUN_LEFT][King_hat].mTexture;
			rect_ = KingImg[RUN_LEFT][King_hat].rect_;
		}

		else
		{
			mTexture = KingImg[RUN_RIGHT][King_hat].mTexture;
			rect_ = KingImg[RUN_RIGHT][King_hat].rect_;
		}
		jump_tale[0][king_tale_color].Render(x_pos + rect_.w / 16 - jump_tale[0][king_tale_color].rect_.w / 2  , y_pos + rect_.h - jump_tale[0][king_tale_color].rect_.h / 2 - 25, des, NULL);

	}
	else 
	{
		if (pre_turn == LEFT)
		{
			mTexture = KingImg[STAND_LEFT][King_hat].mTexture;
			rect_ = KingImg[STAND_LEFT][King_hat].rect_;
		}
		else
		{
			mTexture = KingImg[STAND_RIGHT][King_hat].mTexture;
			rect_ = KingImg[STAND_RIGHT][King_hat].rect_;
		}
		
	}

	set_clips();
	rect_.w /= NUMBER_OF_FRAME;
	if (GAME_MODE == 1)
	{
		double zoomtale = (1.0 * fly_force/ 70);
		KingTale.rect_ = { 0,0,int(zoomtale * 50) ,int(zoomtale * 62) }; 
		KingTale.Render(x_pos + rect_.w / 2 -KingTale.rect_.w/2 , y_pos + rect_.h, des, NULL, tale_angle, &tale);
	}
	if (pull == true)
	{
		Render(pre_pos_x, pre_pos_y, des, &frame_clip_[frame_]);
	}
	else Render(x_pos, y_pos, des, &frame_clip_[frame_]);




}


void King::set_begin()
{
	Life = 2;

	set_clips();
	Action[3] = false;

	x_stand = 808;
	y_stand = 8900;
	delta_x = 0;
	delta_y = 0;
	lost_height = 2000;
	jump_forces = 0;
	on_ground = true;
	turn = 0;
	max_height = 0;
	key_ = 0;

}

void King::loadKingImg(SDL_Renderer *des)
{
	std::string a;
	for (int hat = 0; hat < HAT_COUNT; hat++)
	{
		 a= "img//King//" + std::to_string(hat);

		KingImg[STAND_LEFT][hat].LoadImg(a+ "//king_left.png", des);
		KingImg[STAND_RIGHT][hat].LoadImg(a+ "//king_right.png", des);
		KingImg[RUN_LEFT][hat].LoadImg(a + "//king_run_left.png", des);
		KingImg[RUN_RIGHT][hat].LoadImg(a + "//king_run_right.png", des);
		KingImg[FALL_LEFT][hat].LoadImg(a + "//king_fall_left.png", des);
		KingImg[FALL_RIGHT][hat].LoadImg(a + "//king_fall_right.png", des);
		KingImg[JUMP_LEFT][hat].LoadImg(a + "//king_jump_left.png", des);
		KingImg[JUMP_RIGHT][hat].LoadImg(a + "//king_jump_right.png", des);
		KingImg[PRESS_LEFT][hat].LoadImg(a + "//king_press_left.png", des);
		KingImg[PRESS_RIGHT][hat].LoadImg(a + "//king_press_right.png", des);
		KingImg[FACE_DOWN_LEFT][hat].LoadImg(a + "//face_down_left.png", des);
		KingImg[FACE_DOWN_RIGHT][hat].LoadImg(a + "//face_down_right.png", des);
		KingImg[CLASH_LEFT][hat].LoadImg(a + "//king_clash_left.png", des);
		KingImg[CLASH_RIGHT][hat].LoadImg(a + "//king_clash_right.png", des);
	}

	KingTale.LoadImg("img//King//king_tale.png", des);
	char nam[] = "img//button//jump_effect_2.png";
	for (int color = 0; color < COLOR_COUNT; color++)
	{
		nam[25] = color + '0';
		for (int i = 0; i < 25; i++)
		{

			jump_tale[i][color].LoadImg(nam, des);
			jump_tale[i][color].rect_.w = 48 - 2 * i;
			jump_tale[i][color].rect_.h = 48 - 2 * i;
		}
	}
	char nam2[] = "img//King//landing_effect_n.png";
	for (int i = 0; i < 4; i++)
	{
		nam2[26] = i + '0';
		landing_effect[i].LoadImg(nam2, des);
	}
	
}

void King::Get_max_height()
{
	max_height = (max_height < (MAX_MAP_Y * TILE_SIZE - y_stand) ? (MAX_MAP_Y * TILE_SIZE - y_stand) : max_height);
}

void King::loadStage(int stage, GameMap& game_map, SDL_Renderer* des, Object &back_ground_)
{
	Achive_ += max_height;
	score_ += max_height;
	std::cout << score_ << '\n';;
	set_begin();
	stage_ = stage;
	char nameMap2[] = "map//map03.dat";
	nameMap2[9] = char(stage+'0');
	display_music_theme(music_theme[stage]);
	back_ground_.LoadImg("img//background" + std::to_string(stage) + ".png", des);
	hori = 8;
	game_map.time =0;
	game_map.LoadMap(nameMap2);
	if (stage == 3)
	{
		GAME_MODE = 2;
	}
	if(stage==0) 	score_ = 0;
	pause_ = false;
	isTutor = false;
	

}
void King::Reborn(int stage,SDL_Renderer* des,Object lose_)
{
	lose_.Render(0, 0, des, NULL);
	SDL_RenderPresent(des);
	display_rick(music_rick);
	if (isDiebyLazer)
	{
		y_stand = 2569;
		x_stand = 544;
	}
	Life = 1;
	display_music_theme(music_theme[stage]);
}
bool King::check_rope(Map& map)
{

	if (sqrt(delta_y*delta_y+delta_x*delta_x) > 40) return 0;
	int point_x = x_stand + rect_.w/2;
	int point_y = y_stand + rect_.h/2;
	int tile_x = point_x / TILE_SIZE;
	int tile_y = point_y / TILE_SIZE;

	for (int i = -3; i <= 2; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			if (map.tile[tile_y + i][tile_x + j] == 93) 
			{
				connect_rope = true;
				rope_stand_x1=(tile_x+j)*TILE_SIZE-7;
				rope_stand_y1=(tile_y+i+0.5)*TILE_SIZE;
				rope_stand_x2= (tile_x + j+1) * TILE_SIZE;
				rope_stand_y2 = rope_stand_y1;

				on_ground = false;
				Action[CLASH] = false;

				return 1;

			}
		}
	}
	return 0;

	
}

void King::render_rope(SDL_Renderer* des, Map& map)
{

	
	r_length = std::sqrt((rope_stand_x1 - x_stand) * (rope_stand_x1 - x_stand ) + (rope_stand_y1 - y_stand - rect_.h / 2) * (rope_stand_y1 - y_stand - rect_.h / 2));
	if ((rope_stand_x1 - x_stand) == 0) r_angle = 90;
	else
	{
		r_angle = std::atan(1.0 * (y_stand + rect_.h / 2 - rope_stand_y1) / (x_stand - rope_stand_x1)) / M_PI * 180;
		if (r_angle < 0) r_angle = 180 + r_angle;
	}

	SDL_Point p = { 0,7 };
	rope.rect_.w = r_length;

	rope.Render(rope_stand_x1 - map.start_x_, rope_stand_y1 - map.start_y_, des, NULL, r_angle, &p);
	rope.Render(rope_stand_x2 - map.start_x_, rope_stand_y2 - map.start_y_, des, NULL, r_angle, &p);
}

void King::Jump_effect(SDL_Renderer* des, Map& map)
{

	for (int i = 0; i < 30; i++)
	{

		if(jump_effect_frame[i] <24 ) jump_effect_frame[i]++;
		jump_tale[jump_effect_frame[i]][king_tale_color].Render(jump_effect_x[i] - map.start_x_ + rect_.w / 2 - jump_tale[jump_effect_frame[i]][king_tale_color].rect_.w / 2, jump_effect_y[i] - map.start_y_ + rect_.h - jump_tale[jump_effect_frame[i]][king_tale_color].rect_.h / 2 - 25, des, NULL);
	}
}

void King::Landing_effect(SDL_Renderer*des, Map &map)
{
	if (landing_effect_frame_ < 3)
	{
		landing_effect[landing_effect_frame_].Render(landing_x - map.start_x_, landing_y - map.start_y_, des, NULL);
		if (loop % 8 == 0) landing_effect_frame_++;
	}
	else
	{
		landing_effect_frame_ = 0;
		is_landing = false;
	}
}