#pragma once
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "CommonFunc.h"



class TileMat :public Object
{
public:
	TileMat() { ; };
	~TileMat()  { ; };
};

class GameMap
{
public:
	GameMap() { ; };
	~GameMap() { ; };

	void LoadMap(char* name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
	void Refresh_Ice();
	Map game_map_;
	TileMat tile_mat[MAX_TILES] = {};
	Uint32 time=0;


};



#endif
