#pragma once
#include <vector>
#include <array>
#include <map>
#include <memory>
#include "INPUT_ID.h"

class Mouse;

enum class Trg
{
	Now,
	Old,
	Max
};

using TrgBool = std::array<bool, static_cast<size_t>(Trg::Max)>;
using TrgData = std::map<INPUT_ID, TrgBool>;

struct InputState
{
	const TrgData& GetTrgData(void);			// �f�[�^�̃Q�b�g�֐�

	/// <summary>
	/// �{�^���������ꂽ�u�Ԃ�
	/// </summary>
	/// <param name="id">�{�^����ID</param>
	/// <returns>�{�^���������ꂽ�u�Ԃ�</returns>
	bool GetButtonDown(INPUT_ID id);

	/// <summary>
	/// �{�^����������Ă��邩�ǂ���
	/// </summary>
	/// <param name="id">�{�^����ID</param>
	/// <returns>������Ă��邩�ǂ���</returns>
	bool GetButton(INPUT_ID id);

	/// <summary>
	/// �{�^���������ꂽ�u�Ԃ�
	/// </summary>
	/// <param name="id">�{�^����ID</param>
	/// <returns>�����ꂽ�u�Ԃ��ǂ���</returns>
	bool GetButtonUp(INPUT_ID id);

	virtual void Update(void) = 0;

	virtual const std::shared_ptr<Mouse> GetMouse() = 0;

protected:

	TrgData state_;								// ���ꂼ���key��new �� old�̏��i�[
};

