#pragma once
#include "GameObject.h"
#include "../TEAM_TAG.h"

/// <summary>
/// マップ状に配置される移動や攻撃ができるオブジェクトクラス
/// </summary>
class Character : public GameObject
{
private:
	bool hasMoved_ = false;
	bool hasAttackd_ = false;
	unsigned int moveRange_;
	unsigned int attackRange_;
	Vector2 mapPos_;
	TEAM_TAG team_;

public:
	Character(TEAM_TAG team);

	/// <summary>
	/// テスト用の画像切り替えコンストラクタ
	/// そのうち消える
	/// </summary>
	/// <param name="imageNum"></param>
	Character(int imageNum,TEAM_TAG team);

	unsigned int GetMoveRange()const;
	unsigned int GetAttackRange()const;

	bool HasMoved()const;
	bool HasAttacked()const;

	void MoveCancel();
	void Moved(const Vector2& mapPos);
	void Attacked();
	void Damage(int damage)override;

	/// <summary>
	/// ターンが開始したときの処理
	/// </summary>
	void TurnEnd();

	TEAM_TAG GetTeamTag()const;
	const Vector2& GetMapPos()const;
};