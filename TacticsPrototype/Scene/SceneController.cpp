#include "SceneController.h"
#include <cassert>
#include "Scene.h"
#include "TitleScene.h"

SceneController::SceneController()
{
	scene_.emplace_front(new TitleScene(*this));
	postDrawExecuter_ = []() {};
}

void SceneController::ChangeScene(Scene* scene)
{
	postDrawExecuter_ =
		[this,scene]() {
		scene_.pop_front();
		scene_.emplace_front(scene);
	};
	
}

void SceneController::CleanChangeScene(Scene* scene)
{
	postDrawExecuter_ =
		[this, scene]() {
		scene_.clear();
		scene_.emplace_front(scene);
	};
	
}

void SceneController::PushScene(Scene* scene)
{
	postDrawExecuter_ =
		[this, scene]() {
		scene_.emplace_front(scene);
	};
	
}

void SceneController::PopScene()
{
	postDrawExecuter_ =
		[this]() {
		scene_.pop_front();
		assert(!scene_.empty());
	};
	
}

void SceneController::ClearScene() 
{
	scene_.clear();
}


void SceneController::Update()
{
	assert (!scene_.empty());
	scene_.front()->Update();
}

void SceneController::Draw()
{
	auto rit = scene_.rbegin();
	for (; rit != scene_.rend(); rit++)
	{
		(*rit)->Draw();
	}
	postDrawExecuter_();
	postDrawExecuter_ = []() {};
}

SceneController::~SceneController()
{
}
