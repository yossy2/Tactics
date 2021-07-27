#pragma once
#include <memory>
#include <vector>
#include "../Common/Geometry.h"

class MouseableObject;

/// <summary>
/// マウスボタン
/// 数値はDxLibの仕様に基づく
/// </summary>
enum class MOUSE_BUTTON
{
	LEFT = 0x0001,	// 左
	RIGHT = 0x0002,	// 右
	MIDDLE = 0x0004,	// 中央
};

/// <summary>
/// マウスの入力状況を管理するクラス
/// </summary>
class Mouse
{
private:
	Vector2 pos_;
	int buttonState_[2];
	int currentBufferNum_ = 0;
	int wheelRotateVolume_ = 0;

	mutable std::vector<std::weak_ptr<MouseableObject>> holdingObjects_;	// 紐づいているオブジェクト

	/// <summary>
	/// 現在のbuttonStateを返す
	/// </summary>
	/// <returns>現在のbuttonState</returns>
	int CurrentButtonState()const;

	/// <summary>
	/// 1フレーム前のbuttonStateを返す
	/// </summary>
	/// <returns>1フレーム前のbuttonState</returns>
	int OldButtonState()const;
public:
	void Update();

	/// <summary>
	/// ボタンが押された瞬間か判定する関数
	/// </summary>
	/// <param name="button">判定したいボタンの種類</param>
	/// <returns>指定したボタンが押された瞬間か</returns>
	bool GetButtonDown(MOUSE_BUTTON button)const;

	/// <summary>
	/// ボタンが押されているか判定する関数
	/// </summary>
	/// <param name="button">判定したいボタンの種類</param>
	/// <returns>指定したボタンが押されているか</returns>
	bool GetButton(MOUSE_BUTTON button)const;

	/// <summary>
	/// ボタンが離された瞬間か判定
	/// </summary>
	/// <param name="button">判定したいボタンの種類</param>
	/// <returns>指定したボタンが離された瞬間か</returns>
	bool GetButtonUp(MOUSE_BUTTON button)const;

	Position2 GetPosition()const;

	/// <summary>
	/// マウスに紐づけるオブジェクトのセット
	/// ドラッグで移動させるものなどに使う
	/// MouseableObjectから呼び出すのでconst
	/// </summary>
	/// <param name="obj">紐づけたいオブジェクトのポインタ</param>
	void Hold(std::shared_ptr<MouseableObject> obj)const;

	/// <summary>
	/// 引数がマウスと紐づいてるオブジェクトと等しいか判定
	/// </summary>
	/// <param name="obj">判定したいオブジェクト</param>
	/// <returns>等しい：true</returns>
	bool EqualHoldingObject(std::shared_ptr<MouseableObject> obj) const;

	std::vector<std::weak_ptr<MouseableObject>>& GetHoldingObjects()const;

	/// <summary>
	/// マウスに紐づけるオブジェクトのクリア
	/// MouseableObjectから呼び出すのでconst
	/// </summary>
	void ClearHoldingObject()const;

	/// <summary>
	/// マウスホイールの回転量を得る
	/// 手前：マイナス値、奥：プラス値
	/// </summary>
	/// <returns>ホイールの回転量　手前：マイナス値、奥：プラス値</returns>
	int GetWheelRotateVolume()const;
};