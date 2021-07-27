#pragma once
#include "../../Common/Geometry.h"

/// <summary>
/// �}�b�v�̃}�X�̏�ɔz�u�����I�u�W�F�N�g�̊��N���X
/// </summary>
class GameObject
{
protected:
	int imageHandle_;
	bool isDeletable_ = false;

public:
	void Draw(const Position2f& pos);
	bool IsDeletable();
	virtual void Damage(int damage);

	virtual ~GameObject() = default;
};