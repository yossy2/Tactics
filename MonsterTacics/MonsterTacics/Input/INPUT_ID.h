#pragma once

enum class INPUT_ID
{
	BUTTON_LEFT,
	BUTTON_UP,
	BUTTON_RIGHT,
	BUTTON_DOWN,
	BUTTON_SPACE,
	BUTTON_EDIT,
	BUTTON_MENU,
	BUTTON_SELECT,
	BUTTON_BACK,
	MAX,
};

INPUT_ID begin(INPUT_ID);
INPUT_ID end(INPUT_ID);
INPUT_ID operator++(INPUT_ID& key);
INPUT_ID operator*(INPUT_ID key);