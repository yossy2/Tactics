#include "ImageManager.h"
#include <DxLib.h>
#include <cassert>

std::unique_ptr<ImageManager, ImageManager::ImageManagerDeleter>ImageManager::sInstance_(new ImageManager);

ImageManager::ImageManager()
{
}

ImageManager::~ImageManager()
{
}

const std::vector<int>& ImageManager::GetImageHandle(const std::string& name)
{
	// キーがないかチェックする
	if (imageID_.find(name) == imageID_.end())
	{
		std::string fileName = ("Resource/Image/" + name + ".png");
		int handle = LoadGraph(fileName.c_str());

		if (handle == -1)
		{
			// 失敗
			assert(!"画像読み込みエラー");
		}
		// 新しく追加
		imageID_[name].emplace_back(handle);
	}
	return imageID_[name];
}

const std::vector<int>& ImageManager::GetImageHandle(const std::string& name, const Size& num, const Size& size)
{
	// キーがないかチェックする
	if (imageID_.find(name) == imageID_.end())
	{
		std::string fileName = ("Resource/Image/" + name + ".png");
		auto allSize = num.h * num.w;

		imageID_[name].resize(allSize);
		int tmpNum = LoadDivGraph(fileName.c_str(), allSize, num.w, num.h, size.w, size.h, imageID_[name].data());

		if (tmpNum == -1)
		{
			// 失敗
			assert(!"画像読み込みエラー" + name.c_str());
		}
	}
	return imageID_[name];
}

const std::vector<int>& ImageManager::GetImageHandle(const std::string& name, const Size& num)
{
	// キーがないかチェックする
	if (imageID_.find(name) == imageID_.end())
	{
		std::string fileName = ("Resource/Image/" + name + ".png");
		auto allSize = num.h * num.w;

		imageID_[name].resize(allSize);
		int handle = LoadGraph(fileName.c_str());
		if (handle == -1)
		{
			// 失敗
			assert(!"画像読み込みエラー" + name.c_str());
		}

		Size graphSize;
		GetGraphSize(handle,&graphSize.w, &graphSize.h);
		int tmpNum = LoadDivGraph(fileName.c_str(), allSize, num.w, num.h, graphSize.w / num.w, graphSize.h / num.h, imageID_[name].data());

		if (tmpNum == -1)
		{
			// 失敗
			assert(!"画像読み込みエラー" + name.c_str());
		}
	}
	return imageID_[name];
}
