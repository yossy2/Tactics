#pragma once
#include "Scene.h"
#include <memory>
#include <unordered_map>
#include "../Game/TEAM_TAG.h"

class SceneController;
class MouseableManager;
class Map;
class Character;

class TestScene :
	public Scene
{
private:
	TEAM_TAG currentTurn_;
	std::shared_ptr<MouseableManager> mouseableManager_;
	std::shared_ptr<Map> selectMap_;
	std::weak_ptr<Character> selectCharacter_;
	std::unordered_map<TEAM_TAG, std::vector<std::shared_ptr<Character>>> characters_;

	/// <summary>
	/// 移動範囲を計算する再帰関数
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="move"></param>
	void CheckMoveRange(int x, int y, int move);

	void CheckAttackRange(int x, int y, int range);

	// フェーズ別関数
	using PhaseUpdateFunction = void(TestScene::*)(std::shared_ptr<InputState> input);
	using PhaseDrawFunction = void(TestScene::*)();
	PhaseUpdateFunction updatePhase_;
	PhaseDrawFunction drawPhase_;

	/// <summary>
	/// 入力待ちフェーズ
	/// </summary>
	/// <param name="input">入力情報</param>
	void UpdateWaitInputPhase(std::shared_ptr<InputState> input);

	/// <summary>
	/// キャラクター移動フェーズ
	/// </summary>
	/// <param name="input">入力</param>
	void UpdateMoveCharacterPhase(std::shared_ptr<InputState> input);

	/// <summary>
	/// 攻撃などの対象選択フェーズ
	/// </summary>
	/// <param name="input"></param>
	void UpdateSelectTargetPhase(std::shared_ptr<InputState> input);

	void DrawWaitInputPhase();

	void DrawMoveCharacterPhase();

	void DrawSelectTargetPhase();
public:
	TestScene(SceneController& c);

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="input">入力</param>
	void Update(std::shared_ptr<InputState> input) override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	~TestScene();
};