#include "Common.h"
#include <cassert>
#include "DxLib.h"

int Wrap(int value, int low, int high)
{
	assert((low < high)&& "ラップアラウンドの範囲エラー");
	int n = (value - low) % (high - low);
	return (n >= 0) ? (n + low) : (n + high) ;
}

float ConvertToRadians(float deg)
{
	return deg  * DX_PI_F/ 180.0f;
}

float ConvertToDegrees(float rad)
{
	return rad * 180.0f / DX_PI_F;
}
