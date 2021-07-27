#include "Character.h"
#include "../../System/ImageManager.h"

Character::Character(TEAM_TAG team):moveRange_(3),attackRange_(1),team_(team)
{
	imageHandle_ = lpImageManager.GetImageHandle("character_test")[0];
}

Character::Character(int imageNum, TEAM_TAG team) : moveRange_(3), attackRange_(1),team_(team)
{
	switch (imageNum)
	{
	case 0:
		imageHandle_ = lpImageManager.GetImageHandle("character_test")[0];
		break;

	case 1:
		imageHandle_ = lpImageManager.GetImageHandle("character_test2")[0];
		moveRange_ = 4;
		attackRange_ = 2;
		break;

	case 2:
		imageHandle_ = lpImageManager.GetImageHandle("character_test3")[0];
		moveRange_ = 5;
		break;

	default:
		imageHandle_ = lpImageManager.GetImageHandle("character_test")[0];
		break;
	}
}

unsigned int Character::GetMoveRange() const
{
	return moveRange_;
}

unsigned int Character::GetAttackRange() const
{
	return attackRange_;
}

bool Character::HasMoved() const
{
	return hasMoved_;
}

bool Character::HasAttacked() const
{
	return hasAttackd_;
}

void Character::MoveCancel()
{
	hasMoved_ = false;
}

void Character::Moved(const Vector2& mapPos)
{
	mapPos_ = mapPos;
	hasMoved_ = true;
}

void Character::Attacked()
{
	hasMoved_ = true;
	hasAttackd_ = true;
}

void Character::Damage(int damage)
{
	isDeletable_ = true;
}

void Character::TurnEnd()
{
	hasMoved_ = false;
	hasAttackd_ = false;
}

TEAM_TAG Character::GetTeamTag() const
{
	return team_;
}

const Vector2& Character::GetMapPos() const
{
	return mapPos_;
}
