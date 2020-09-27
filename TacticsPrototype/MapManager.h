#pragma once
#include "Geometry.h"

class MapManager
{
private:
	int mapSize_;	// ˆê•Ó‚Ìƒ}ƒX‚Ì”
	Position2f pos_ = {0,0};
	Quadrangle quad_;
public:
	MapManager(int size);

	void Update();
	void Draw();
};

