#pragma once
#include "CommonFunc.h"
bool Map::IsNonCollisionBlock(int val)
{
	for (int x : non_collision_block)
	{
		if (val == x) return true;
	}
	return false;
}
int GRAVITY=2;
int MAX_GRAVITY = 32;
int Map::Check_xo()
{
	for (int i = 0; i < 3; i++)
	{

		int tong1 = 0;
		int tong2 = 0;
		for (int j = 0; j < 3; j++)
		{
			tong1 += xo[i][j];
			tong2 += xo[j][i];
	
	
		}
		if (tong1 == 3 || tong2 == 3) return 1;
		else if (tong1 == 0 || tong2 == 0) return 0;


	}
	int cheo1 = xo[0][0] + xo[1][1] + xo[2][2];
	int cheo2 = xo[0][2] + xo[1][1] + xo[2][0];
	if (cheo1 == 3 || cheo2 == 3) return 1;
	else if (cheo1 == 0 || cheo2 == 0) return 0;
	return -1;

}
void Map::Update_xo(int mode)
{
	if (mode == 1)
	{
		int i = 0;
		for (std::pair<int, int> a : XO_block)
		{
			if (tile[a.first][a.second] == 90) xo[i / 3][i % 3] = 9;
			else if (tile[a.first][a.second] == 91) xo[i / 3][i % 3] = 1;
			else if (tile[a.first][a.second] == 92) xo[i / 3][i % 3] = 0;
			i++;
		}
	}
	if (mode == 0)
	{

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (xo[i][j] == 9) tile[XO_block[i * 3 + j].first][XO_block[i * 3 + j].second] = 90;
				else if (xo[i][j] == 0) tile[XO_block[i * 3 + j].first][XO_block[i * 3 + j].second] = 92;
				else if (xo[i][j] == 1) tile[XO_block[i * 3 + j].first][XO_block[i * 3 + j].second] = 91;
				
			}
			
		}
	}
}
void Map::xo_rival()
{
	for (int i = 0; i < 3; i++)
	{

		int tong1 = 0;
		int tong2 = 0;
		for (int j = 0; j < 3; j++)
		{
			tong1 += xo[i][j];
			tong2 += xo[j][i];

		}
		if (tong2 == 9)
		{
			for (int c = 0; c < 3; c++)
			{
				if (xo[c][i] == 9) xo[c][i] = 0;
			}
			return;
		}
		else if (tong1 == 9)
		{
			for (int c = 0; c < 3; c++)
			{
				if (xo[i][c]== 9) xo[i][c] = 0;
			}
			return;

		}
		else if (tong1 == 11)
		{
			for (int c = 0; c < 3; c++)
			{
				if (xo[i][c] == 9) xo[i][c] = 0;
			}
			return;
		}
		else if (tong2 == 11)
		{
			for (int c = 0; c < 3; c++)
			{
				if (xo[c][i] == 9) xo[c][i] = 0;
			}
			return;
		}

	}
	if (xo[1][1] == 9) xo[1][1] = 0;
	else if (xo[0][0] == 9)xo[0][0] = 0;
	else if (xo[0][2] == 9)xo[0][2] = 0;
	else if (xo[2][0] == 9)xo[2][0] = 0;
	else if (xo[2][0] == 9)xo[2][2] = 0;
	else if (xo[0][1] == 9)xo[2][2] = 0;
	else if (xo[1][0] == 9)xo[2][2] = 0;
	else if (xo[1][2] == 9)xo[2][2] = 0;
	else if (xo[2][1] == 9)xo[2][2] = 0;
}
 Uint32 loop = 0;


 void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int x, int y) {
	 SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	 SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	 SDL_Rect dstRect = { x, y, textSurface->w, textSurface->h };
	 SDL_RenderCopy(renderer, textTexture, nullptr, &dstRect);
	 SDL_FreeSurface(textSurface);
	 SDL_DestroyTexture(textTexture);
 }
