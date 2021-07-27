#pragma once
#include <memory>
#include "../Common/Geometry.h"
#include "../Game/TEAM_TAG.h"

class GameObject;
class Character;
class Mouse;

enum class MAP_STATE
{
	CLICK_UP = 0,
	MOUSE_OVER = 3
};

/// <summary>
/// ゲームプレイ中のマスのクラス
/// 地形情報やゲームオブジェクトの情報をもつ
/// </summary>
class Map
{
private:
	int zOrder_;
	Position2f pos_;
	Vector2 mapNum_;	// マップの行列番号
	MAP_STATE state_;

	std::weak_ptr<GameObject> gameObject_;

	/// <summary>
	/// クリックされた時の処理
	/// </summary>
	/// <param name="mouse">マウス</param>
	/// <returns>マウスに紐づけるかどうか</returns>
	bool OnClickDown(const Mouse& mouse);

	

public:
	Map(const Position2f& pos,const Vector2 mapNum,int zOrder);

	static int GetGridSquareSize();

	/// <summary>
	/// マウスとの当たり判定
	/// </summary>
	/// <param name="mouse"></param>
	/// <returns></returns>
	bool IsHitWithMousePoint(const Mouse& mouse);

	/// <summary>
	/// マウスがオブジェクトの上にあるときの処理
	/// </summary>
	/// <param name="mouse">マウス</param>
	/// <returns>マウスに紐づけるかどうか</returns>
	bool MouseOver();

	std::shared_ptr<Character> HasCharacter();

	/// <summary>
	/// マウスとぶつかっていなかった時の処理
	/// </summary>
	void NotHitWithMouse();

	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw();

	void SetObject(std::shared_ptr<GameObject> object);
	std::shared_ptr<GameObject> GetGameObject();
	const Position2f& GetPosition()const;
	const Vector2& GetMapNum()const;

	/// <summary>
	/// そのマップの移動コストを返す
	/// 持っているObjectやキャラの移動性能（飛行とか）で変わってくる
	/// そのうち引数増える
	/// </summary>
	/// <param name="tag"></param>
	/// <returns></returns>
	int GetMoveCost(TEAM_TAG tag)const;
};