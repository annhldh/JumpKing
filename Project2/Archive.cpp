#pragma once

#include "Archive.h"

void Archive::LoadArchiveImg(SDL_Renderer* des)
{
	char name[] = "img//archive//archive_n.png";
	for (int i = 0; i < 3; i++)
	{
		name[22] = i + '0';
		archive_object[i].LoadImg(name, des);
	}
	char name2[] = "img//archive//shadow_n.png";
	for (int i = 0; i < 3; i++)
	{
		name2[21] = i + '0';
		archive_shadow[i].LoadImg(name2, des);
	}
	archive_data_load.open("Archive_data.txt");
	for (int i = 0; i < 3; i++)
	{
		archive_data_load >> owned[i];
	}
	archive_data_load.close();

}

void Archive::DisplayAchive(SDL_Renderer* des)
{
	for (int i = 0; i < 3; i++)
	{
		if (owned[i] == true)
		{
			archive_object[i].Render(20 + i * 100, 100, des, NULL);
		}
		else
		{
			archive_shadow[i].Render(20 + i * 100, 100, des, NULL);
		}
	}

}

void Archive::SaveArchiveData()
{
	archive_data_save.open("Archive_data.txt", std::ios::trunc);
	for (int i = 0; i < 3; i++)
	{
		archive_data_save << owned[i] << " ";
	}
}

void Archive::UpdateArchive()
{
	if (isVictory == true) owned[GAME_MODE] = true;
	std::cout << "UPDATED!!! \n";
}