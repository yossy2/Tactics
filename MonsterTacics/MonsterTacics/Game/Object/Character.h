#pragma once
#include "GameObject.h"
#include "../TEAM_TAG.h"

/// <summary>
/// �}�b�v��ɔz�u�����ړ���U�����ł���I�u�W�F�N�g�N���X
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
	/// �e�X�g�p�̉摜�؂�ւ��R���X�g���N�^
	/// ���̂���������
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
	/// �^�[�����J�n�����Ƃ��̏���
	/// </summary>
	void TurnEnd();

	TEAM_TAG GetTeamTag()const;
	const Vector2& GetMapPos()const;
};