#include "TitleScene.h"
#include <DxLib.h>
#include "../System/Application.h"
#include "../Geometry.h"
#include "SceneController.h"
#include "../MapManager.h"

namespace
{
	std::shared_ptr<MapManager> mapManager_;
}

TitleScene::TitleScene(SceneController& c) :
	Scene(c)
{
	mapManager_.reset(new MapManager(8));
}

void TitleScene::Update()
{
	mapManager_->Update();

}

void TitleScene::Draw()
{
	mapManager_->Draw();

}

TitleScene::~TitleScene()
{
}
