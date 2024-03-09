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
		COUNT_ACTION,
	};
	// nhan lenh dieu khien
	void Control(SDL_Event events, SDL_Renderer* des);
	//di chuyen theo lenh dieu khien
	void MoveAction(Map& map);
	void CheckMap(Map& map);

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

	int turn;
	bool on_ground;
	int jump_forces;
	

};

#endif 
