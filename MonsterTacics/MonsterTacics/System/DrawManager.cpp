#include "DrawManager.h"
#include <cassert>
#include <algorithm>
#include <DxLib.h>
#include "Application.h"

std::unique_ptr<DrawManager, DrawManager::DrawManagerDeleter> DrawManager::sInstance_(new DrawManager());

DrawManager::DrawManager()
{
	screenID_ = -1;
}

DrawManager::~DrawManager()
{
}

void DrawManager::AddQueList(void)
{
	drawQueList_.emplace_back();
}

void DrawManager::Init(void)
{
	Size size = Application::Instance().GetViewport().GetSize();
	screenID_ = MakeScreen(size.w, size.h, true);
}

void DrawManager::Draw()
{
	if (!drawQueList_.size())
	{
		return;
	}

	// スクリーン初期化
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	// 描画
	// 下のシーンから描画する
	for (auto& list : drawQueList_)
	{
		std::sort(list.begin(), list.end(),
			[](DrawQue& que1, DrawQue& que2) {
				return 	std::tie(que1.layer_, que1.zOrder_) < std::tie(que2.layer_, que2.zOrder_);
		});

		LAYER drawLayer = begin(LAYER());
		int blendMode = DX_BLENDMODE_NOBLEND;
		int blendParam = 255;
		Size size = Application::Instance().GetViewport().GetSize();

		SetDrawScreen(screenID_);
		ClsDrawScreen();

		for (auto& que : list)
		{
			// Old
			int blendModeOld = blendMode;
			int blendParamOld = blendParam;
			// New
			blendMode = que.blendMode_;
			blendParam = que.blendParam_;

			if ((blendMode != blendModeOld) || (blendParam != blendParamOld))
			{
				SetDrawScreen(DX_SCREEN_BACK);
				SetDrawBlendMode(blendModeOld, blendParamOld);
				DrawRotaGraph(size.w / 2, size.h / 2, 1.0, 0, screenID_, true);

				SetDrawScreen(screenID_);
				SetDrawBlendMode(blendMode, blendParam);
				ClsDrawScreen();

				drawLayer = que.layer_;
			}

			DrawRotaGraphF(que.pos_.x, que.pos_.y, que.exRate_, que.angle_, que.imageID_, true, que.reverseX_, que.reverseY_);
		}

		// それぞれのレイヤーを描画する
		SetDrawScreen(DX_SCREEN_BACK);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		DrawRotaGraph(size.w / 2, size.h / 2, 1.0, 0, screenID_, true);

		list.clear();
	}

	drawQueList_.clear();
}

bool DrawManager::AddDrawQue(const DrawQue& drawQue)
{
	if (!(drawQue.layer_ >= begin(LAYER()) && drawQue.layer_ < end(LAYER())))
	{
		// 失敗
		assert(!"レイヤー範囲外");
		return false;
	}

	if (!drawQueList_.size())
	{
		return false;
	}

	drawQueList_.back().emplace_back(drawQue);
	return true;
}

DrawQue::DrawQue(int id, Position2f pos, LAYER layer,
	double exRate, double angle,
	int zOrder, int blendMode, int blendParam,
	bool reverseX, bool reverseY)
{
	if (blendMode == -1)
	{
		blendMode_ = DX_BLENDMODE_NOBLEND;
	}
	else
	{
		blendMode_ = blendMode;
	}
	imageID_ = id;
	pos_ = pos;
	layer_ = layer;
	exRate_ = exRate;
	angle_ = angle;
	zOrder_ = zOrder;
	blendParam_ = blendParam;
	reverseX_ = reverseX;
	reverseY_ = reverseY;
}