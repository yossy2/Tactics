#pragma once
#include "Geometry.h"

class MapManager
{
private:
	int mapSize_;	// 一辺のマスの数
	Position2f pos_ = {0,0};
	Quadrangle quad_;
public:
	MapManager(int size);

	void Update();
	void Draw();
};

