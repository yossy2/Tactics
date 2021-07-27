#pragma once
#include <array>
#include <map>
#include "InputState.h"
#include "INPUT_ID.h"

struct KeyState :
	public InputState
{
public:
	bool Setup(void);
	void Update(void) override;
	const std::shared_ptr<Mouse> GetMouse()override;
	KeyState();
	~KeyState();
private:
	std::shared_ptr<Mouse> mouse_;
	std::array<char, 256> _buf;							// キーボード情報取得用
	std::map<INPUT_ID, int> _keyCon;					// キーの登録
	std::map<INPUT_ID, int> _keyConDef;					//
};

