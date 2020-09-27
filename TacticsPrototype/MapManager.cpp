#include "MapManager.h"
#include <DxLib.h>
#include <vector>
#include <memory>
#include <cmath>
#include "System/Application.h"
#include "MapSquare.h"

namespace
{
	constexpr int base_map_size = 560;
	std::vector<std::shared_ptr<MapSquare>> squares_;
	Matrix mat_;
	Matrix inverseMat_;	// ãtçsóÒ
}

MapManager::MapManager(int size)
{
	mapSize_ = size;

	auto rad = 35.0f * DX_PI_F / 180.0f;

	mat_.m[0][0] = cosf(rad);
	mat_.m[0][1] = cosf(rad);
	mat_.m[1][0] = -sinf(rad);
	mat_.m[1][1] = sinf(rad);
	mat_.m[2][2] = 1.0f;

	auto a = mat_.m[0][0];
	auto b = mat_.m[0][1];
	auto c = mat_.m[1][0];
	auto d = mat_.m[1][1];

	auto D = a*d - b*c;

	if (D != 0)
	{
		inverseMat_.m[0][0] = d / D;
		inverseMat_.m[0][1] = -b / D;
		inverseMat_.m[1][0] = -c / D;
		inverseMat_.m[1][1] = a / D;
		inverseMat_.m[2][2] = 1.0f;
	}

	// äOògÇÃéläpå`
	Vector2 vec = { 0,0 };

	auto left = vec.x;
	auto right = vec.x + base_map_size;
	auto top = vec.y;
	auto bottom = vec.y + base_map_size;

	Position2f upL = { static_cast<float>(left),static_cast<float>(top) };
	Position2f upR = { static_cast<float>(right),static_cast<float>(top) };
	Position2f downL = { static_cast<float>(left),static_cast<float>(bottom) };
	Position2f downR = { static_cast<float>(right),static_cast<float>(bottom) };

	quad_ = Quadrangle(MultipleVec(mat_, upL), MultipleVec(mat_, upR),
					   MultipleVec(mat_, downR), MultipleVec(mat_, downL));

	auto view = Application::Instance().GetViewport().GetSize();
	pos_.x = static_cast<float>(view.w / 2) - quad_.pos2.x;
	pos_.y = static_cast<float>(view.h / 2);

	squares_.reserve(size * size);

	auto lineSpace = base_map_size / mapSize_;
	Size squareSize = { lineSpace,lineSpace };

	auto space1 = MultipleVec(mat_, Vector2f(static_cast <float>(lineSpace), 0));
	auto space2 = MultipleVec(mat_, Vector2f(0, static_cast <float>(lineSpace)));

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			auto pos = pos_;
			pos.x += lineSpace * x;
			pos.y += lineSpace * y;

			auto pos1 = pos_ + space1 * static_cast<float>(x) + space2 * static_cast<float>(y);
			auto pos2 = pos1 + space1;
			auto pos3 = pos2 + space2;
			auto pos4 = pos1 + space2;

			squares_.emplace_back(new MapSquare(RectF(pos, squareSize),
												Quadrangle(pos1,pos2,pos3,pos4)));
		}
	}
}

void MapManager::Update()
{
	int x, y;
	GetMousePoint(&x, &y);
	Position2f mPos = { static_cast<float>(x),static_cast<float>(y) };
	mPos -= pos_;
	mPos = MultipleVec(inverseMat_, mPos);
	mPos += pos_;
	for (auto& square : squares_)
	{
		square->Update(mPos);
	}
}

void MapManager::Draw()
{
	for (auto& square : squares_)
	{
		square->Draw();
	}

	int color = 0xffffff;

	auto lineSpace = base_map_size / mapSize_;

	quad_.Draw(pos_, color, false);
	

	auto space1 = MultipleVec(mat_, Vector2f(static_cast <float>(lineSpace),0));
	auto space2 = MultipleVec(mat_, Vector2f(0,static_cast <float>(lineSpace)));

	for (int i = 1; i < mapSize_; i++)
	{
		DrawLine(quad_.pos1.x + pos_.x + i * space2.x, quad_.pos1.y + pos_.y + i * space2.y,
				 quad_.pos2.x + pos_.x + i * space2.x, quad_.pos2.y + pos_.y + i * space2.y, color);

		DrawLine(quad_.pos1.x + pos_.x + i * space1.x, quad_.pos1.y + pos_.y + i * space1.y,
				 quad_.pos4.x + pos_.x + i * space1.x, quad_.pos4.y + pos_.y + i * space1.y, color);
	}

	DrawLine(quad_.pos1.x + pos_.x, quad_.pos1.y + pos_.y, quad_.pos1.x + pos_.x, quad_.pos1.y + pos_.y + 60, color);
	DrawLine(quad_.pos3.x + pos_.x, quad_.pos3.y + pos_.y, quad_.pos3.x + pos_.x, quad_.pos3.y + pos_.y + 60, color);
	DrawLine(quad_.pos4.x + pos_.x, quad_.pos4.y + pos_.y, quad_.pos4.x + pos_.x, quad_.pos4.y + pos_.y + 60, color);
	DrawLine(quad_.pos1.x + pos_.x , quad_.pos1.y + pos_.y + 60,
			 quad_.pos4.x + pos_.x, quad_.pos4.y + pos_.y + 60, color);

	DrawLine(quad_.pos3.x + pos_.x, quad_.pos3.y + pos_.y + 60,
			 quad_.pos4.x + pos_.x, quad_.pos4.y + pos_.y + 60, color);
}
