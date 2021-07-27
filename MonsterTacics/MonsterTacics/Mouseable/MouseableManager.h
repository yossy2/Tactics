#pragma once
#include <vector>
#include <memory>

class MouseableObject;
class Mouse;

/// <summary>
/// マウスに反応するもの（MouseableObject）を管理するクラス
/// シーンコントローラー（SceneController）が持つ
/// </summary>
class MouseableManager
{
private:
	std::vector<std::shared_ptr<MouseableObject>> mouseables_;
public:

	/// <summary>
	/// 持ってるオブジェクトとマウスとそれぞれ当たり判定を行う
	/// </summary>
	void CheckHitWithMouse(const Mouse& mouse);

	/// <summary>
	/// 全オブジェクトの描画
	/// </summary>
	void Draw();

	void AddMouseableObject(std::shared_ptr<MouseableObject> mouseable);
};
