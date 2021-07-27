#include "KeyState.h"
#include <DxLib.h>
#include "Mouse.h"

bool KeyState::Setup(void)
{
	_keyConDef.clear();

	
	_keyConDef = 
	{
		{INPUT_ID::BUTTON_LEFT,KEY_INPUT_A},
		{INPUT_ID::BUTTON_UP,KEY_INPUT_W},
		{INPUT_ID::BUTTON_RIGHT,KEY_INPUT_D},
		{INPUT_ID::BUTTON_DOWN,KEY_INPUT_S},
		{INPUT_ID::BUTTON_SPACE,KEY_INPUT_SPACE},
		{INPUT_ID::BUTTON_EDIT,KEY_INPUT_E},
		{INPUT_ID::BUTTON_MENU,KEY_INPUT_ESCAPE},
		{INPUT_ID::BUTTON_SELECT,KEY_INPUT_Z},
		{INPUT_ID::BUTTON_BACK,KEY_INPUT_BACK},
	};

	for (auto id : INPUT_ID())
	{
		state_[id][static_cast<int>(Trg::Now)] = 0;
		state_[id][static_cast<int>(Trg::Old)] = 0;
	}

	_keyCon = _keyConDef;
	return false;
}

void KeyState::Update()
{
	GetHitKeyStateAll(_buf.data());																// キーボードの情報取得

	for (auto id : INPUT_ID())
	{
		state_[id][static_cast<int>(Trg::Old)] = state_[id][static_cast<int>(Trg::Now)];		// oldのセット
		state_[id][static_cast<int>(Trg::Now)] = _buf[_keyCon[id]];								// nowのセット
	}

	mouse_->Update();
}

const std::shared_ptr<Mouse> KeyState::GetMouse()
{
	return mouse_;
}

KeyState::KeyState()
{
	Setup();
	mouse_ = std::make_shared<Mouse>();
}

KeyState::~KeyState()
{
}
