#pragma once
#ifndef KING_H_
#define KING_H_
#include "Object.h"
#include "game_map.h"
class King: public Object
{
public:

	King();
	~King();
	enum
	{
		RIGHT,
		LEFT,
		JUMP,
		FACE_DOWN,
		COUNT_ACTION,
	};
	// nhan lenh dieu khien
	void Control(SDL_Event events, SDL_Renderer* des);
	//di chuyen theo lenh dieu khien
	void MoveAction(Map& map);
	void set_clips();
	void CenterEntityOnMap(GameMap & game_map);
	void CheckMap(Map& map);
	void Show_frame(SDL_Renderer* des);
	void Jump_bar(SDL_Renderer* des);
	// vi tri hien tai theo Map
	int x_stand;
	int y_stand;

	// xu huong thay doi vi tri
	int delta_x;
	int delta_y;

	//
	int x_pos = SCREEN_WIDTH/2 ;
	int y_pos = SCREEN_HEIGHT/2 ;
	bool Action[COUNT_ACTION] = {};
	SDL_Rect frame_clip_[8] ;

	int turn;
	bool on_ground;
	int jump_forces;
	int val = 0;
	int lost_height;
	int Life;

	int frame_ = 0;
	int unframe_ = 0;
	int money_ = 0;

};

#endif 
