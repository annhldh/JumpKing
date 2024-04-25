#pragma once
#ifndef ARCHIVE_H_
#define ARCHIVE_H_
#include "Object.h"
#include "CommonFunc.h"
#include "SFX.h"

class Archive
{
public:
	Object archive_object[3];
	Object archive_shadow[3];
	
	bool owned[3] = { 0,0,0 };

	void LoadArchiveImg(SDL_Renderer* des);
	void DisplayAchive(SDL_Renderer* des);
	void SaveArchiveData();
	void UpdateArchive();

	std::ifstream archive_data_load;
	std::ofstream archive_data_save;

};


#endif // !ARCHIVE_H_
