#pragma once
#ifndef  LOADDATA_H_
#define LOADDATA_H_

#include "CommonFunc.h"
#include "SFX.h"
#include "Archive.h"

void LoadSFX();
void LoadMoney(std::ifstream& money);
void loadLeaderBoard(std::ifstream& board, std::pair< int, std::string> bo[11]);

void SaveMoney(std::ofstream& money2);


#endif // ! LOADDATA_H_
