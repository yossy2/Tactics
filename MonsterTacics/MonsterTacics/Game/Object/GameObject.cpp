#include "GameObject.h"
#include "../../System/DrawManager.h"

void GameObject::Draw(const Position2f& pos)
{
	DrawManager::GetInstance().AddDrawQue(DrawQue{ imageHandle_,pos, LAYER::UI,1.0,0.0,500 });	//zorder“K“–‚¾‚©‚çŒã‚Å•Ï‚¦‚È‚«‚á
}

bool GameObject::IsDeletable()
{
	return isDeletable_;
}

void GameObject::Damage(int damage)
{
}
