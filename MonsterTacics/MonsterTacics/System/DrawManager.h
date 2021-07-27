#pragma once
#include <memory>
#include <list>
#include <vector>
#include <map>
#include "LAYER.h"
#include "../Common/Geometry.h"

/// <summary>
/// キューに必要な要素
/// </summary>
struct DrawQue
{
	int imageID_;		// 画像ID
	Position2f pos_;	// 座標
	LAYER layer_;		// レイヤー
	double exRate_;		// 拡大率
	double angle_;		// 角度
	int zOrder_;		// 奥行
	int blendMode_;		// ブレンド設定
	int blendParam_;	// ブレンドのパラメーター
	bool reverseX_;		// X反転フラグ
	bool reverseY_;		// Y反転フラグ

	/// <summary>
	/// コンストラクタ
	/// </summary>
	DrawQue(int id, Position2f pos, LAYER layer,
		double exRate, double angle,int zOrder,
		int blendMode = -1, int blendParam = 255,
		bool reverseX = false, bool reverseY = false);
};

class DrawManager
{
private:

	DrawManager();
	~DrawManager();

	/// <summary>
	/// カスタムデリーター
	/// </summary>
	struct DrawManagerDeleter
	{
		void operator()(DrawManager* manager)const
		{
			delete manager;
		}
	};

	static std::unique_ptr<DrawManager, DrawManagerDeleter> sInstance_;			// 実体

	// std::map<Layer, int> layerScreen_;										// 各レイヤーのスクリーン
	
	/// <summary>
	/// シーンスタック分キューを用意して
	/// スタックが複数あってもちゃんと裏から描画できるように
	/// </summary>
	std::list<std::vector<DrawQue>> drawQueList_;								// 描画情報格納

	int screenID_;																// 描画用スクリーン
public:
	/// <summary>
	/// ポインター取得
	/// </summary>
	/// <returns></returns>
	static DrawManager& GetInstance(void)
	{
		return *sInstance_;
	};

	/// <summary>
	/// 初期化
	/// </summary>
	void Init(void);
	/// <summary>
	/// キューに溜まっているものをすべて描画
	/// </summary>
	void Draw(void);
	/// <summary>
	/// 新しくキューを作る
	/// </summary>
	void AddQueList(void);
	/// <summary>
	/// キューに追加する
	/// </summary>
	/// <param name="drawQue">キューに追加する情報</param>
	/// <returns>true : 成功</returns>
	bool AddDrawQue(const DrawQue& drawQue);
};

