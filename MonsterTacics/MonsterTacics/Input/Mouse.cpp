#include "Mouse.h"
#include <algorithm>
#include <DxLib.h>
#include "../Common/Common.h"
#include "../Mouseable/MouseableObject.h"

int Mouse::CurrentButtonState()const
{
	return buttonState_[currentBufferNum_];
}

int Mouse::OldButtonState()const
{
	return buttonState_[Wrap(currentBufferNum_ - 1, 0, static_cast<int>(_countof(buttonState_)))];
}

void Mouse::Update()
{
	// バッファ切り替え
	currentBufferNum_ = Wrap(currentBufferNum_ + 1, 0, static_cast<int>(_countof(buttonState_)));

	// 座標
	GetMousePoint(&pos_.x, &pos_.y);

	// クリック判定
	buttonState_[currentBufferNum_] = GetMouseInput();

	wheelRotateVolume_ = GetMouseWheelRotVol();

	ClearHoldingObject();

}

bool Mouse::GetButtonDown(MOUSE_BUTTON button) const
{
	return (CurrentButtonState() & static_cast<int>(button)) && !(OldButtonState() & static_cast<int>(button));
}

bool Mouse::GetButton(MOUSE_BUTTON button) const
{
	return (CurrentButtonState() & static_cast<int>(button));
}

bool Mouse::GetButtonUp(MOUSE_BUTTON button) const
{
	return !(CurrentButtonState() & static_cast<int>(button)) && (OldButtonState() & static_cast<int>(button));
}

Position2 Mouse::GetPosition() const
{
	return pos_;
}

void Mouse::Hold(std::shared_ptr<MouseableObject> obj) const
{
	obj->Hold();
	holdingObjects_.push_back(obj);
}

bool Mouse::EqualHoldingObject(std::shared_ptr<MouseableObject> obj) const
{
	auto it = std::find_if(holdingObjects_.begin(), holdingObjects_.end(), [obj](std::weak_ptr<MouseableObject>& m) 
		{
			return m.lock() == obj;
		});
	return (it != holdingObjects_.end());
}

std::vector<std::weak_ptr<MouseableObject>>& Mouse::GetHoldingObjects() const
{
	return holdingObjects_;
}

void Mouse::ClearHoldingObject() const
{
	holdingObjects_.erase(std::remove_if(holdingObjects_.begin(), holdingObjects_.end(),
		[](std::weak_ptr<MouseableObject>& m) {
			// ここに離された時だけではなく、非activeになったとき、空になっているときなども追加予定
			if (m.expired()) return true;
			return m.lock()->IsRelease();
		}), holdingObjects_.end());
}

int Mouse::GetWheelRotateVolume() const
{
	return wheelRotateVolume_;
}
