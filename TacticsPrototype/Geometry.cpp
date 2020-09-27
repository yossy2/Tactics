#include "Geometry.h"
#include <DxLib.h>

const Vector2D<float> Vector2f::ZERO = { 0, 0 };
const Vector2D<float> Vector2f::NIL = { NAN, NAN };
const Segment Segment::ZERO(Vector2f::ZERO,Vector2f::ZERO);
const Segment Segment::NIL(Vector2f::NIL,Vector2f::NIL);

bool Segment::IsNil()
{
	return isnan(vec.x) || isnan(vec.y);
}

Position2f Segment::End()
{
	return start + vec;
}

Vector2f Reflected(Vector2f ref, Vector2f wall)
{
	auto cross = Cross(ref, wall);
	Vector2f n = Vector2f(-wall.y, wall.x);
	n.Normalize();

	// 法線ベクトルの向き決定
	if (cross == 0)
	{
		// 平行
		return ref;
	}
	else if (cross < 0)
	{
		n *= -1.0f;
	}
	else
	{

	}

	// 壁に平行なベクトルを計算
	auto p = ref + (n * Dot(ref * -1.0f, n));

	return p * 2.0f - ref;
}

Matrix IdentityMat()
{
	Matrix ret = {};
	ret.m[0][0] = ret.m[1][1] = ret.m[2][2] = 1.0f;
	return ret;
}

Matrix TranslateMat(float x, float y)
{
	auto ret = IdentityMat();
	ret.m[0][2] = x;
	ret.m[1][2] = y;

	return ret;
}

Matrix RotateMat(float angle)
{
	auto ret = IdentityMat();
	ret.m[0][0] = ret.m[1][1] = cosf(angle);
	ret.m[0][1] = ret.m[1][0] = sinf(angle);
	ret.m[0][1] = -ret.m[0][1];
	return ret;
}

Matrix MultipleMat(const Matrix& lmat, const Matrix& rmat)
{
	Matrix ret;
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			ret.m[j][i] = lmat.m[j][0] * rmat.m[0][i] + lmat.m[j][1] * rmat.m[1][i] + lmat.m[j][2] * rmat.m[2][i];
		}
	}
	
	return ret;
}

Vector2f MultipleVec(const Matrix& mat, const Vector2f& vec)
{
	Vector2f ret = {};
	ret.x = mat.m[0][0] * vec.x + mat.m[0][1] * vec.y + mat.m[0][2];
	ret.y = mat.m[1][0] * vec.x + mat.m[1][1] * vec.y + mat.m[1][2];

	return ret;
}

void Quadrangle::Draw(Vector2f offset, int color, bool fill)
{
	DrawQuadrangle(pos1.x + offset.x, pos1.y + offset.y, pos2.x + offset.x, pos2.y + offset.y,
		           pos3.x + offset.x, pos3.y + offset.y, pos4.x + offset.x, pos4.y + offset.y, color, fill);
}
