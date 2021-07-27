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
	const TrgData& GetTrgData(void);			// データのゲット関数

	/// <summary>
	/// ボタンが押された瞬間か
	/// </summary>
	/// <param name="id">ボタンのID</param>
	/// <returns>ボタンが押された瞬間か</returns>
	bool GetButtonDown(INPUT_ID id);

	/// <summary>
	/// ボタンが押されているかどうか
	/// </summary>
	/// <param name="id">ボタンのID</param>
	/// <returns>押されているかどうか</returns>
	bool GetButton(INPUT_ID id);

	/// <summary>
	/// ボタンが離された瞬間か
	/// </summary>
	/// <param name="id">ボタンのID</param>
	/// <returns>離された瞬間かどうか</returns>
	bool GetButtonUp(INPUT_ID id);

	virtual void Update(void) = 0;

	virtual const std::shared_ptr<Mouse> GetMouse() = 0;

protected:

	TrgData state_;								// それぞれのkeyのnew と oldの情報格納
};

