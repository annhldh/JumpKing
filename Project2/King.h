#pragma once
#ifndef KING_H_
#define KING_H_
#include "Object.h"
#include "game_map.h"
#include "SFX.h"
#include "Setting.h"
enum
{
	NO,
	RED_CROWN,
	GOLD_HAT,
	HAT_COUNT,
};
class King: public Object
{
public:
	King();
	~King();
	enum
	{
		RIGHT,
		LEFT,
		NONE,
		JUMP,
		FACE_DOWN,
		CLASH,
		COUNT_ACTION,
	};
	
	enum igm
	{
		STAND_LEFT,
		STAND_RIGHT,
		RUN_LEFT,
		RUN_RIGHT,
		FALL_LEFT,
		FALL_RIGHT,
		JUMP_LEFT,
		JUMP_RIGHT,
		FACE_DOWN_LEFT,
		FACE_DOWN_RIGHT,
		PRESS_LEFT,
		PRESS_RIGHT,
		CLASH_LEFT,
		CLASH_RIGHT,
		COUNT,
	};

	
	Object KingImg[COUNT][HAT_COUNT];
	Object KingTale;
	// nhan lenh dieu khien
	void Control(SDL_Event events, SDL_Renderer* des,Map & map);
	//di chuyen theo lenh dieu khien
	void MoveAction(Map& map);
	void set_clips();
	void CenterEntityOnMap(GameMap & game_map);
	void CheckMap(Map& map);
	void check_collect(Map& map,int val1, int val2, int val3, int val4);
	void Show_frame(SDL_Renderer* des);
	
	void set_begin();



	// vi tri hien tai theo Map
	int x_stand;
	int y_stand;

	// xu huong thay doi vi tri
	int delta_x;
	int delta_y;

	//
	int x_pos = SCREEN_WIDTH/2 ;
	int y_pos = 2*SCREEN_HEIGHT/3 ;
	bool Action[COUNT_ACTION] = {};
	SDL_Rect frame_clip_[8] ;
	SDL_Point tale = { 25,0 };
	

	int turn;
	int pre_turn;
	bool on_ground;
	int jump_forces;
	int val = 0;
	int lost_height;
	int Life;
	int max_height = 0;
	int frame_ = 0;
	int unframe_ = 0;
	int money_ = 0;
	int key_ = 0;
	int Timer;
	int time_xo = 0;
	int stage_;


	bool X = false;

	//MODE 2
	double tale_angle=20;
	double force = 0;
	int hori = 8;
	int energy = 3;
	int fly_force=0;

	bool connect_rope = false;
	bool pull = false;



	
	void loadKingImg(SDL_Renderer * des);
	void Get_max_height();
	void loadStage(int stage, GameMap& game_map, SDL_Renderer* des, Object& back_ground_);
	void Reborn(int stage,SDL_Renderer* des, Object lose_);
	bool check_rope(Map& map);
	void render_rope(SDL_Renderer* des, Map& map);



	int rope_stand_x1;
	int rope_stand_y1;
	int rope_stand_x2;
	int rope_stand_y2;

	int r_angle = 0;
	int r_length;

	int r_range;
	int pre_x = 0;
	int pre_y = 0;
	int pre_pos_x = 0;
	int pre_pos_y = 0;
	int rope_forces = 0;
	int kinetic_e = 0;

	double bounderies = 45;

	Object jump_tale[25][COLOR_COUNT];
	std::vector<int> jump_effect_x;

	std::vector<int> jump_effect_y;
	std::vector<int> jump_effect_frame;
	int jump_effect_index=0;
	void Jump_effect(SDL_Renderer* des, Map& map);


};

#endif 
