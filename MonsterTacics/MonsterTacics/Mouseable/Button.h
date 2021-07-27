#pragma once
#include "MouseableObject.h"
#include <memory>
#include <functional>
#include <unordered_map>
#include <string>


class Button :public MouseableObject
{
	std::shared_ptr<Shape> shape_;
	std::unordered_map<MOUSEABLE_STATE,std::function<void()>> functionMap_;
	std::vector<int> imageHandle_;
	MOUSEABLE_STATE state_;

	/// <summary>
	/// クリックされた時の処理
	/// </summary>
	/// <param name="mouse">マウス</param>
	/// <returns>マウスに紐づけるかどうか</returns>
	bool OnClickDown(const Mouse& mouse)override;

	/// <summary>
	/// 長押しされているときの処理
	/// </summary>
	/// <param name="mouse">マウス</param>
	void OnClickHold(const Mouse& mouse)override;

	/// <summary>
	/// ボタンが離された時の処理
	/// </summary>
	/// <param name="mouse">マウス</param>
	void OnClickUp(const Mouse& mouse)override;

	/// <summary>
	/// マウスがオブジェクトの上にあるときの処理
	/// </summary>
	/// <param name="mouse">マウス</param>
	/// <returns>マウスに紐づけるかどうか</returns>
	bool MouseOver(const Mouse& mouse)override;

public:
	Button(std::shared_ptr<Shape> shape, std::unordered_map<MOUSEABLE_STATE, std::function<void()>>& func,std::string fileName);
	/// <summary>
	/// マウスとの当たり判定
	/// </summary>
	/// <param name="mouse"></param>
	/// <returns></returns>
	bool IsHitWithMousePoint(const Mouse& mouse)override;

	/// <summary>
	/// マウスとぶつかっていなかった時の処理
	/// </summary>
	void NotHitWithMouse()override;

	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw()override;
};