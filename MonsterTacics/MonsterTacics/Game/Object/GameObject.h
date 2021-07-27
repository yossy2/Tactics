#pragma once
#include "../../Common/Geometry.h"

/// <summary>
/// マップのマスの上に配置されるオブジェクトの基底クラス
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