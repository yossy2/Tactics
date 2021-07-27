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
	std::array<char, 256> _buf;							// �L�[�{�[�h���擾�p
	std::map<INPUT_ID, int> _keyCon;					// �L�[�̓o�^
	std::map<INPUT_ID, int> _keyConDef;					//
};

