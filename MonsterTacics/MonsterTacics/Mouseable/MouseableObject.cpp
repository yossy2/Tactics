#include "MouseableObject.h"
#include "../Input/Mouse.h"
#include <cassert>

namespace
{
	constexpr MOUSE_BUTTON decision_button = MOUSE_BUTTON::LEFT;
}

bool MouseableObject::SelectFuncWithMouseState(const Mouse& mouse)
{
	// マウスがオブジェクトの上にあるの前提
	
	if (mouse.GetButtonDown(decision_button))
	{
		return OnClickDown(mouse);
	}
	return MouseOver(mouse);
}

void MouseableObject::Holded(const Mouse& mouse)
{
	if (mouse.GetButton(decision_button))
	{
		OnClickHold(mouse);
	}
	else
	{
		OnClickUp(mouse);
	}
}

bool MouseableObject::IsRelease()
{
	return isRelease_;
}

bool MouseableObject::IsDeletable()
{
	return isDeletable_;
}

void MouseableObject::Hold()
{
	isRelease_ = false;
}
