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
	/// �ړ��͈͂��v�Z����ċA�֐�
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="move"></param>
	void CheckMoveRange(int x, int y, int move);

	void CheckAttackRange(int x, int y, int range);

	// �t�F�[�Y�ʊ֐�
	using PhaseUpdateFunction = void(TestScene::*)(std::shared_ptr<InputState> input);
	using PhaseDrawFunction = void(TestScene::*)();
	PhaseUpdateFunction updatePhase_;
	PhaseDrawFunction drawPhase_;

	/// <summary>
	/// ���͑҂��t�F�[�Y
	/// </summary>
	/// <param name="input">���͏��</param>
	void UpdateWaitInputPhase(std::shared_ptr<InputState> input);

	/// <summary>
	/// �L�����N�^�[�ړ��t�F�[�Y
	/// </summary>
	/// <param name="input">����</param>
	void UpdateMoveCharacterPhase(std::shared_ptr<InputState> input);

	/// <summary>
	/// �U���Ȃǂ̑ΏۑI���t�F�[�Y
	/// </summary>
	/// <param name="input"></param>
	void UpdateSelectTargetPhase(std::shared_ptr<InputState> input);

	void DrawWaitInputPhase();

	void DrawMoveCharacterPhase();

	void DrawSelectTargetPhase();
public:
	TestScene(SceneController& c);

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="input">����</param>
	void Update(std::shared_ptr<InputState> input) override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	~TestScene();
};