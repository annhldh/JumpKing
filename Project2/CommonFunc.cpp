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
