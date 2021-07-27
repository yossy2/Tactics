#include <DxLib.h>
#include "InputState.h"

const TrgData& InputState::GetTrgData(void)
{
	return state_;
}

bool InputState::GetButtonDown(INPUT_ID id)
{
	return state_[id][static_cast<int>(Trg::Now)] && !state_.at(id)[static_cast<int>(Trg::Old)];
}

bool InputState::GetButton(INPUT_ID id)
{
	return state_[id][static_cast<int>(Trg::Now)];
}

bool InputState::GetButtonUp(INPUT_ID id)
{
	return !state_[id][static_cast<int>(Trg::Now)] && state_.at(id)[static_cast<int>(Trg::Old)];
}
