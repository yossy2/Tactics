#pragma once
#include <memory>
#include <map>
#include <string>
#include <vector>
#include "../Common/Geometry.h"

#define lpImageManager ImageManager::GetInstance()

class ImageManager
{
private:
	ImageManager();
	~ImageManager();

	/// <summary>
	/// カスタムデリーター
	/// </summary>
	struct ImageManagerDeleter
	{
		void operator()(ImageManager* manager)
		{
			delete manager;
		}
	};

	static std::unique_ptr<ImageManager, ImageManagerDeleter> sInstance_;		// 実態

	std::map<std::string, std::vector<int>> imageID_;							// 画像ID

public:
	/// <summary>
	/// 実態の取得
	/// </summary>
	/// <returns>実態が返る</returns>
	static ImageManager& GetInstance()
	{
		return *sInstance_;
	}
	/// <summary>
	/// イメージのハンドル取得
	/// パスは引数に書かなくていい
	/// </summary>
	/// <param name="name">ファイル名+形式</param>
	/// <returns>ハンドル</returns>
	const std::vector<int>& GetImageHandle(const std::string& name);
	/// <summary>
	/// イメージのハンドル取得
	/// パスは引数に書かなくていい
	/// </summary>
	/// <param name="name">ファイル名+形式</param>
	/// <param name="num">分割数</param>
	/// <param name="size">分割される画像のサイズ</param>
	/// <returns>ハンドル</returns>
	const std::vector<int>& GetImageHandle(const std::string& name, const Size& num, const Size& size);

	const std::vector<int>& GetImageHandle(const std::string& name, const Size& num);
};

