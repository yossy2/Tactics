#include "TestScene.h"
#include <DxLib.h>
#include <vector>
#include "SceneController.h"
#include "../Input/InputState.h"
#include "../Input/Mouse.h"
#include "../System/Application.h"
#include "../System/ImageManager.h"
#include "../System/DrawManager.h"
#include "../Common/Geometry.h"
#include "../Mouseable/Map.h"
#include "../Mouseable/MouseableManager.h"
#include "../Mouseable/Button.h"
#include "../Game/Object/Character.h"

namespace
{
	constexpr int grid_num = 8;
	std::array<std::array<std::shared_ptr<Map>, grid_num>, grid_num> map_;
	std::array<std::array<int, grid_num>, grid_num > movableRange_;
	std::array<std::array<int, grid_num>, grid_num > attackableRange_;
	std::shared_ptr<Character> testCharacter2_ = nullptr;

	using MoveHistoryInfo = std::pair < std::shared_ptr<Map>, Vector2>;
	std::vector<MoveHistoryInfo> moveHistory_;

}

namespace
{
	// 移動範囲や攻撃範囲を格納する二次元配列を指定した値で初期化する
	void FillRangeArray(std::array<std::array<int, grid_num>, grid_num >& rangeArray,int fillValue = -1)
	{
		for (auto& range : rangeArray)
		{
			range.fill(fillValue);
		}
	}
}

void TestScene::CheckMoveRange(int x, int y, int move)
{
	if (map_[y][x]->GetGameObject() == nullptr) movableRange_[y][x] = move;

	if (move == 0) return;

	// 上
	if (y - 1 >= 0)
	{
		if (movableRange_[y - 1][x] < move) CheckMoveRange(x, y - 1, move - map_[y-1][x]->GetMoveCost(currentTurn_));
	}

	// 左
	if (x - 1 >= 0)
	{
		if (movableRange_[y][x - 1] < move) CheckMoveRange(x - 1, y, move - map_[y][x - 1]->GetMoveCost(currentTurn_));
	}

	// 右
	if (x + 1 < grid_num)
	{
		if (movableRange_[y][x + 1] < move) CheckMoveRange(x + 1, y, move - map_[y][x + 1]->GetMoveCost(currentTurn_));
	}

	// 下
	if (y + 1 < grid_num)
	{
		if (movableRange_[y + 1][x] < move) CheckMoveRange(x, y + 1, move - map_[y + 1][x]->GetMoveCost(currentTurn_));
	}
}

void TestScene::CheckAttackRange(int x, int y, int range)
{
	attackableRange_[y][x] = range;

	if (range == 0) return;

	// 上
	if (y - 1 >= 0)
	{
		if (attackableRange_[y - 1][x] < range) CheckAttackRange(x, y - 1, range - 1);
	}

	// 左
	if (x - 1 >= 0)
	{
		if (attackableRange_[y][x - 1] < range) CheckAttackRange(x - 1, y, range - 1);
	}

	// 右
	if (x + 1 < grid_num)
	{
		if (attackableRange_[y][x + 1] < range) CheckAttackRange(x + 1, y, range - 1);
	}

	// 下
	if (y + 1 < grid_num)
	{
		if (attackableRange_[y + 1][x] < range) CheckAttackRange(x, y + 1, range - 1);
	}
}

void TestScene::UpdateWaitInputPhase(std::shared_ptr<InputState> input)
{
	auto& mouse = input->GetMouse();
	bool findHitMap = false;

	// マップのあたり判定
	for (int y = 0; y < grid_num; y++)
	{
		for (int x = 0; x < grid_num; x++)
		{
			auto& map = map_[y][x];

			if (findHitMap)
			{
				map->NotHitWithMouse();
				continue;
			}

			if (map->IsHitWithMousePoint(*mouse))
			{
				findHitMap = true;

				if (!(mouse->GetButtonDown(MOUSE_BUTTON::LEFT)))
				{
					map->MouseOver();
					continue;
				}

				auto chara = map->HasCharacter();

				if (chara == nullptr)
				{
					map->MouseOver();
					continue;
				}

				selectCharacter_ = chara;

				if (chara->GetTeamTag() != currentTurn_)
				{
					map->MouseOver();
					continue;
				}

				if (chara->HasMoved())
				{
					map->MouseOver();
					continue;
				}

				selectMap_ = map;

				// 移動範囲計算
				CheckMoveRange(x, y, chara->GetMoveRange());

				updatePhase_ = &TestScene::UpdateMoveCharacterPhase;
				drawPhase_ = &TestScene::DrawMoveCharacterPhase;

			}
			else
			{
				map->NotHitWithMouse();
			}
		}
	}

	// 移動の取り消し
	if (input->GetButtonDown(INPUT_ID::BUTTON_BACK))
	{
		if (moveHistory_.size() > 0)
		{
			auto history = moveHistory_.back();
			auto backNum = history.first->GetMapNum() - history.second;
			map_[backNum.y][backNum.x]->SetObject(history.first->GetGameObject());

			auto chara = std::dynamic_pointer_cast<Character>(history.first->GetGameObject());
			if (chara != nullptr)
			{
				chara->MoveCancel();
			}

			history.first->SetObject(nullptr);
			moveHistory_.pop_back();
		}
	}
}

void TestScene::UpdateMoveCharacterPhase(std::shared_ptr<InputState> input)
{
	auto& mouse = input->GetMouse();
	bool findHitMap = false;

	auto BackWaitInputPhase = [&]() {
		selectMap_.reset();
		//selectCharacter_.reset();

		FillRangeArray(movableRange_);

		updatePhase_ = &TestScene::UpdateWaitInputPhase;
		drawPhase_ = &TestScene::DrawWaitInputPhase;
	};

	// マップのあたり判定
	for (int y = 0; y < grid_num;y++)
	{
		for (int x = 0; x < grid_num;x++)
		{
			auto& map = map_[y][x];

			if (findHitMap)
			{
				map->NotHitWithMouse();
				continue;
			}

			if (map->IsHitWithMousePoint(*mouse))
			{
				findHitMap = true;

				// マウス入力確認
				if (!(mouse->GetButtonDown(MOUSE_BUTTON::LEFT)))
				{
					map->MouseOver();
					continue;
				}

				// 移動範囲確認
				if (movableRange_[y][x] < 0)
				{
					map->MouseOver();
					continue;
				}

				// 同じマスだったら入力キャンセル
				if (map == selectMap_)
				{
					BackWaitInputPhase();
					continue;
				}

				map->SetObject(selectCharacter_.lock());
				selectMap_->SetObject(nullptr);
				selectCharacter_.lock()->Moved(Vector2(x,y));

				// 移動履歴登録
				auto distance = map->GetMapNum() - selectMap_->GetMapNum();
				moveHistory_.emplace_back(std::make_pair(map,distance));


				BackWaitInputPhase();
			}
			else
			{
				map->NotHitWithMouse();
			}
		}
	}

	if (mouse->GetButtonDown(MOUSE_BUTTON::RIGHT)) BackWaitInputPhase();
}

void TestScene::UpdateSelectTargetPhase(std::shared_ptr<InputState> input)
{
	auto& mouse = input->GetMouse();
	bool findHitMap = false;

	auto BackWaitInputPhase = [&]() {
		selectMap_.reset();
		//selectCharacter_.reset();

		FillRangeArray(attackableRange_);

		updatePhase_ = &TestScene::UpdateWaitInputPhase;
		drawPhase_ = &TestScene::DrawWaitInputPhase;
	};

	// マップのあたり判定
	for (int y = 0; y < grid_num; y++)
	{
		for (int x = 0; x < grid_num; x++)
		{
			auto& map = map_[y][x];

			if (findHitMap)
			{
				map->NotHitWithMouse();
				continue;
			}

			if (map->IsHitWithMousePoint(*mouse))
			{
				findHitMap = true;

				// マウス入力確認
				if (!(mouse->GetButtonDown(MOUSE_BUTTON::LEFT)))
				{
					map->MouseOver();
					continue;
				}

				// 移動範囲確認
				if (attackableRange_[y][x] < 0)
				{
					map->MouseOver();
					continue;
				}

				auto obj = map->GetGameObject();

				if (obj == nullptr)
				{
					map->MouseOver();
					continue;
				}

				auto chara = std::dynamic_pointer_cast<Character>(obj);

				if (chara != nullptr)
				{
					if (chara->GetTeamTag() == currentTurn_)
					{
						map->MouseOver();
						continue;
					}
				}

				obj->Damage(1);
				selectCharacter_.lock()->Attacked();

				BackWaitInputPhase();
			}
			else
			{
				map->NotHitWithMouse();
			}
		}
	}

	if (mouse->GetButtonDown(MOUSE_BUTTON::RIGHT)) BackWaitInputPhase();
}

void TestScene::DrawWaitInputPhase()
{
}

void TestScene::DrawMoveCharacterPhase()
{
	for (int y = 0; y < grid_num; y++)
	{
		for (int x = 0; x < grid_num; x++)
		{
			if (movableRange_[y][x] >= 0)
			{
				DrawManager::GetInstance().AddDrawQue(DrawQue{ lpImageManager.GetImageHandle("map_can_move")[0],map_[y][x]->GetPosition(), LAYER::UI,1.0,0.0,-x + y + 1 });
			}
		}
	}
}

void TestScene::DrawSelectTargetPhase()
{
	for (int y = 0; y < grid_num; y++)
	{
		for (int x = 0; x < grid_num; x++)
		{
			if (attackableRange_[y][x] >= 0)
			{
				DrawManager::GetInstance().AddDrawQue(DrawQue{ lpImageManager.GetImageHandle("map_can_attack2")[0],map_[y][x]->GetPosition(), LAYER::UI,1.0,0.0,-x + y + 1 });
			}
		}
	}
}

TestScene::TestScene(SceneController& controller):Scene(controller),updatePhase_(&TestScene::UpdateWaitInputPhase),drawPhase_(&TestScene::DrawWaitInputPhase)
{
	mouseableManager_ = std::make_shared<MouseableManager>();

	// マップ生成
	auto view = Application::Instance().GetViewport().GetSize();

	// マップのグリッドの描画位置のオフセット
	float offsetX = 58;
	float offsetY = 42;

	Position2f firstPos = { static_cast<float>(view.w / 2) - offsetX * (grid_num - 1) ,static_cast<float>(view.h / 2) };
	auto pos = firstPos;

	for (int y = 0; y < grid_num; y++)
	{
		for (int x = 0; x < grid_num; x++)
		{
			map_[y][x] = (std::make_shared<Map>(pos, Vector2{x,y}, (-x + y)));
			pos.x += offsetX;
			pos.y -= offsetY;
		}

		pos = firstPos;
		pos.x += (y + 1) * offsetX;
		pos.y += (y + 1) * offsetY;
	}

	// キャラクター生成
	std::vector<std::shared_ptr<Character>> characterList;
	Vector2 mapPos;

	characterList.emplace_back( std::make_shared<Character>(TEAM_TAG::PLAYER));
	characterList.emplace_back(std::make_shared<Character>(TEAM_TAG::PLAYER));
	characterList.emplace_back(std::make_shared<Character>(TEAM_TAG::PLAYER));
	
	mapPos = { 0,0 };
	map_[mapPos.y][mapPos.x]->SetObject(characterList[0]);
	characterList[0]->Moved(mapPos);
	characterList[0]->TurnEnd();

	mapPos = { 4,3 };
	map_[mapPos.y][mapPos.x]->SetObject(characterList[1]);
	characterList[1]->Moved(mapPos);
	characterList[1]->TurnEnd();

	mapPos = { 5,5 };
	map_[mapPos.y][mapPos.x]->SetObject(characterList[2]);
	characterList[2]->Moved(mapPos);
	characterList[2]->TurnEnd();

	characters_[TEAM_TAG::PLAYER] = characterList;

	characterList.clear();
	characterList.emplace_back(std::make_shared<Character>(1,TEAM_TAG::ENEMY));
	characterList.emplace_back(std::make_shared<Character>(1,TEAM_TAG::ENEMY));
	characterList.emplace_back(std::make_shared<Character>(1,TEAM_TAG::ENEMY));

	mapPos = { 1,0 };
	map_[mapPos.y][mapPos.x]->SetObject(characterList[0]);
	characterList[0]->Moved(mapPos);
	characterList[0]->TurnEnd();

	mapPos = { 4,2 };
	map_[mapPos.y][mapPos.x]->SetObject(characterList[1]);
	characterList[1]->Moved(mapPos);
	characterList[1]->TurnEnd();

	mapPos = { 5,6 };
	map_[mapPos.y][mapPos.x]->SetObject(characterList[2]);
	characterList[2]->Moved(mapPos);
	characterList[2]->TurnEnd();

	characters_[TEAM_TAG::ENEMY] = characterList;

	FillRangeArray(movableRange_);
	FillRangeArray(attackableRange_);

	currentTurn_ = TEAM_TAG::PLAYER;

	// ボタン設定
	// ターン終了ボタン
	std::unordered_map<MOUSEABLE_STATE, std::function<void()>> functionMap;
	functionMap[MOUSEABLE_STATE::CLICK_DOWN] = []() {};
	functionMap[MOUSEABLE_STATE::CLICK_HOLD] = []() {};
	functionMap[MOUSEABLE_STATE::MOUSE_OVER] = []() {};
	functionMap[MOUSEABLE_STATE::CLICK_UP] = [&]() {
		for (auto& chara : characters_[currentTurn_])
		{
			chara->TurnEnd();
		}

		moveHistory_.clear();

		currentTurn_ = GetAnoterTag(currentTurn_);
	};

	mouseableManager_->AddMouseableObject(std::make_shared<Button>(
		std::make_shared<RectF>(Position2f::ZERO, Size(256, 128)), functionMap, "turn_end"));

	// 攻撃ボタン
	functionMap[MOUSEABLE_STATE::CLICK_UP] = [&]() {
		if (selectCharacter_.expired()) return;
		if (selectCharacter_.lock()->GetTeamTag() != currentTurn_) return;
		if (selectCharacter_.lock()->HasAttacked()) return;

		auto& mapPos = selectCharacter_.lock()->GetMapPos();

		CheckAttackRange(mapPos.x, mapPos.y, selectCharacter_.lock()->GetAttackRange());

		attackableRange_[mapPos.y][mapPos.x] = -1;

		updatePhase_ = &TestScene::UpdateSelectTargetPhase;
		drawPhase_ = &TestScene::DrawSelectTargetPhase;
	};

	mouseableManager_->AddMouseableObject(std::make_shared<Button>(
		std::make_shared<RectF>(Position2f(0,656), Size(128, 64)), functionMap, "attack"));
}

void TestScene::Update(std::shared_ptr<InputState> input)
{
	for (auto& characterList : characters_)
	{
		characterList.second.erase(std::remove_if(characterList.second.begin(), characterList.second.end(),
			[](std::shared_ptr<Character>& c) {
				return c->IsDeletable();
			}), characterList.second.end());
	}

	(this->*updatePhase_)(input);
	mouseableManager_->CheckHitWithMouse(*(input->GetMouse()));
}

void TestScene::Draw()
{
	for (auto& mapX : map_)
	{
		for (auto& map : mapX)
		{
			map->Draw();
		}
	}

	(this->*drawPhase_)();

	

	DrawManager::GetInstance().AddDrawQue(DrawQue{ lpImageManager.GetImageHandle("map_big")[0],{640,360}, LAYER::UI,1.0,0.0,100 });
	mouseableManager_->Draw();
}

TestScene::~TestScene()
{
}
