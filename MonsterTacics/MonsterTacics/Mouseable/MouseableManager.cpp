#include "MouseableManager.h"
#include "MouseableObject.h"
#include "../Input/Mouse.h"

void MouseableManager::CheckHitWithMouse(const Mouse& mouse)
{
	mouseables_.erase(remove_if(mouseables_.begin(), mouseables_.end(),
		[](std::shared_ptr<MouseableObject>& c) {
			return c->IsDeletable();
		}), mouseables_.end());

	// まずマウスと紐づいてるオブジェクトを更新
	for (auto& holded : mouse.GetHoldingObjects())
	{
		if (holded.expired()) continue;
		holded.lock()->Holded(mouse);
	}
	// 全オブジェクトと当たり判定をとるが、距離近い順にソートしたほうがいいかも
	for (auto& obj : mouseables_)
	{

		if (obj->IsHitWithMousePoint(mouse))
		{
			if (mouse.EqualHoldingObject(obj)) continue;

			if(obj->SelectFuncWithMouseState(mouse)) mouse.Hold(obj);
		}
		else
		{
			obj->NotHitWithMouse();
		}
	}
}

void MouseableManager::Draw()
{
	for (auto& obj : mouseables_)
	{
		obj->Draw();
	}
}

void MouseableManager::AddMouseableObject(std::shared_ptr<MouseableObject> mouseable)
{
	mouseables_.emplace_back(mouseable);
}
