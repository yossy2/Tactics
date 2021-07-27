#include "Button.h"
#include <DxLib.h>
#include "../Input/Mouse.h"
#include "../System/ImageManager.h"
#include "../System/DrawManager.h"

bool Button::OnClickDown(const Mouse& mouse)
{
	state_ = MOUSEABLE_STATE::CLICK_DOWN;
	functionMap_[MOUSEABLE_STATE::CLICK_DOWN]();
	return true;
}

void Button::OnClickHold(const Mouse& mouse)
{
	state_ = MOUSEABLE_STATE::CLICK_HOLD;
	functionMap_[MOUSEABLE_STATE::CLICK_HOLD]();
}

void Button::OnClickUp(const Mouse& mouse)
{
	state_ = MOUSEABLE_STATE::CLICK_UP;
	if (IsHitWithMousePoint(mouse))
	{
		functionMap_[MOUSEABLE_STATE::CLICK_UP]();
	}
	isRelease_ = true;
}

bool Button::MouseOver(const Mouse& mouse)
{
	state_ = MOUSEABLE_STATE::MOUSE_OVER;
	functionMap_[MOUSEABLE_STATE::MOUSE_OVER]();
	return false;
}

Button::Button(std::shared_ptr<Shape> shape, std::unordered_map<MOUSEABLE_STATE, std::function<void()>>& func, std::string fileName)
	:shape_(shape),functionMap_(func)
{
	state_ = MOUSEABLE_STATE::CLICK_UP;
	std::string filepath = "System/Button/" + fileName;
	imageHandle_ = lpImageManager.GetImageHandle(filepath, { 2,2 });
}

bool Button::IsHitWithMousePoint(const Mouse& mouse)
{
	return shape_->IsHitWithPoint(mouse.GetPosition());
}

void Button::NotHitWithMouse()
{
	state_ = MOUSEABLE_STATE::CLICK_UP;
}

void Button::Draw()
{
	auto pos = shape_->GetCenter();
	DrawManager::GetInstance().AddDrawQue(DrawQue{ imageHandle_[static_cast<int>(state_)], pos, LAYER::UI,1.0,0.0,3 });
}
