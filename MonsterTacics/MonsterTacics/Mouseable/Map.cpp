#include "Map.h"
#include <DxLib.h>
#include "../System/ImageManager.h"
#include "../System/DrawManager.h"
#include "../Input/Mouse.h"
#include "../Game/Object/Character.h"

namespace
{
	constexpr int grid_square_size = 70;
	constexpr float rhombus_slope = 7.0f / 9.0f;		// ひしがたの辺の一次方程式の傾き
	constexpr float half_height_rhombus = 42.0f;		// ひしがたの高さの半分
}

bool Map::OnClickDown(const Mouse& mouse)
{
	if (gameObject_.expired()) return false;

	auto chara = std::dynamic_pointer_cast<Character>(gameObject_.lock());

	if (chara == nullptr) return false;

	return true;
}

bool Map::MouseOver()
{
	state_ = MAP_STATE::MOUSE_OVER;

	return false;
}

std::shared_ptr<Character> Map::HasCharacter()
{
	if (gameObject_.expired()) return nullptr;

	auto chara = std::dynamic_pointer_cast<Character>(gameObject_.lock());

	if (chara == nullptr) return nullptr;

	return chara;
}

Map::Map(const Position2f& pos, const Vector2 mapNum, int zOrder):pos_(pos),mapNum_(mapNum),zOrder_(zOrder),state_(MAP_STATE::CLICK_UP)
{
}

int Map::GetGridSquareSize()
{
	return grid_square_size;
}

bool Map::IsHitWithMousePoint(const Mouse& mouse)
{
	auto mousePos = mouse.GetPosition();
	Position2f pos = { mousePos.x - pos_.x,mousePos.y - pos_.y };		// ひし形の中心を原点としたときのマウス座標

	auto side1 = -rhombus_slope * pos.x + half_height_rhombus;	// 右下の辺
	auto side2 = rhombus_slope * pos.x + half_height_rhombus;	// 左下
	auto side3 = -rhombus_slope * pos.x - half_height_rhombus;	// 左上
	auto side4 = rhombus_slope * pos.x - half_height_rhombus;	// 右上

	if (pos.y > side1 || pos.y > side2 || pos.y < side3 || pos.y < side4)
	{
		return false;
	}


	return true;
}

void Map::NotHitWithMouse()
{
	state_ = MAP_STATE::CLICK_UP;
}

void Map::Draw()
{
	DrawManager::GetInstance().AddDrawQue(DrawQue{ lpImageManager.GetImageHandle("map_test2",{2,2})[static_cast<int>(state_)],pos_, LAYER::UI,1.0,0.0,zOrder_ });
	if (gameObject_.expired()) return;

	gameObject_.lock()->Draw(pos_);
}

void Map::SetObject(std::shared_ptr<GameObject> object)
{
	if (object == nullptr)
	{
		gameObject_.reset();
		return;
	}
	gameObject_ = object;
}

std::shared_ptr<GameObject> Map::GetGameObject()
{
	return gameObject_.lock();
}

const Position2f& Map::GetPosition() const
{
	return pos_;
}

const Vector2& Map::GetMapNum() const
{
	return mapNum_;
}

int Map::GetMoveCost(TEAM_TAG tag) const
{
	if (gameObject_.expired()) return 1;

	auto character = std::dynamic_pointer_cast<Character>(gameObject_.lock());
	
	if (character == nullptr) return 100;

	if (character->GetTeamTag() == tag) return 1;

	return 100;
}
