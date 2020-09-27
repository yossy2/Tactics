#include "MapSquare.h"
#include <DxLib.h>

MapSquare::MapSquare(RectF rect, Quadrangle quad)
{
	rect_ = rect;
	quad_ = quad;
}

void MapSquare::Update(Position2f mousePos)
{
	isMouseOver_ = false;
	if (mousePos.x >= rect_.Left() &&
		mousePos.x <= rect_.Right() &&
		mousePos.y >= rect_.Top() &&
		mousePos.y <= rect_.Bottom())
	{
		isMouseOver_ = true;
	}
}

void MapSquare::Draw()
{
	int color = 0xaa0000;

	if (isMouseOver_)
	{
		color = 0xffffff;
	}

	quad_.Draw({0,0}, color, true);
}
