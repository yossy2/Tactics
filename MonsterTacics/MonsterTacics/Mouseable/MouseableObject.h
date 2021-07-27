#pragma once
#include "../Common/Geometry.h"

class Mouse;

enum class MOUSEABLE_STATE
{
	CLICK_DOWN,
	CLICK_HOLD,
	CLICK_UP,
	MOUSE_OVER
};

/// <summary>
/// マウスに反応するオブジェクトの基底クラス
/// </summary>
class MouseableObject
{
protected:
	bool isRelease_ = false;
	bool isDeletable_ = false;
	/// <summary>
	/// クリックされた時の処理
	/// </summary>
	/// <param name="mouse">マウス</param>
	/// <returns>マウスに紐づけるかどうか</returns>
	virtual bool OnClickDown(const Mouse& mouse) = 0;

	/// <summary>
	/// 長押しされているときの処理
	/// </summary>
	/// <param name="mouse">マウス</param>
	virtual void OnClickHold(const Mouse& mouse) = 0;

	/// <summary>
	/// ボタンが離された時の処理
	/// </summary>
	/// <param name="mouse">マウス</param>
	virtual void OnClickUp(const Mouse& mouse) = 0;

	/// <summary>
	/// マウスがオブジェクトの上にあるときの処理
	/// </summary>
	/// <param name="mouse">マウス</param>
	/// <returns>マウスに紐づけるかどうか</returns>
	virtual bool MouseOver(const Mouse& mouse) = 0;

public:
	virtual ~MouseableObject() = default;

	/// <summary>
	/// マウスとの当たり判定
	/// </summary>
	/// <param name="mouse"></param>
	/// <returns></returns>
	virtual bool IsHitWithMousePoint(const Mouse& mouse) = 0;

	/// <summary>
	/// マウスの状態を見て、
	/// 実行する関数を決める
	/// マウスがオブジェクトの上にあるの前提
	/// </summary>
	/// <param name="mouse"></param>
	/// <returns>マウスに紐づけるかどうか</returns>
	bool SelectFuncWithMouseState(const Mouse& mouse);

	/// <summary>
	/// マウスと紐づいているときの処理
	/// </summary>
	/// <param name="mouse"></param>
	void Holded(const Mouse& mouse);

	/// <summary>
	/// マウスと当たっていなかった時の処理
	/// </summary>
	virtual void NotHitWithMouse() = 0;

	/// <summary>
	/// 描画関数
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// 持たれているものが離されるかどうかのフラグを返す
	/// </summary>
	/// <returns></returns>
	bool IsRelease();

	/// <summary>
	/// 削除可能か
	/// </summary>
	/// <returns></returns>
	bool IsDeletable();

	/// <summary>
	/// マウスにもたれるときに呼ばれる
	/// 最低でもisReleaseをfalseにする
	/// </summary>
	virtual void Hold();
};

