#pragma once
#include "Geometry.h"


/// <summary>
/// マップのマス目一つ一つのクラス
/// </summary>
class MapSquare
{
private:
	RectF rect_;			// 座標変換前の矩形、あたり判定に使う
	Quadrangle quad_;	// 座標返還後の四角形、実際に描画される
	bool isMouseOver_ = false;
public:
	MapSquare(RectF rect,Quadrangle quad);
	void Update(Position2f mousePos);
	void Draw();
};

