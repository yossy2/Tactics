#include "SceneController.h"
#include <cassert>
#include "Scene.h"
#include "TestScene.h"
#include "../Input/KeyState.h"
#include "../System/DrawManager.h"

SceneController::SceneController()
{
	input_ = std::make_shared<KeyState>();
	scene_.emplace_front(std::make_shared<TestScene>(*this));
	postDrawExecuter_ = []() {};
}

void SceneController::ChangeScene(std::shared_ptr<Scene> scene)
{
	postDrawExecuter_ =
		[this, scene]() {
		scene_.pop_front();
		scene_.emplace_front(scene);
	};

}

void SceneController::CleanChangeScene(std::shared_ptr<Scene> scene)
{
	postDrawExecuter_ =
		[this, scene]() {
		scene_.clear();
		scene_.emplace_front(scene);
	};

}

void SceneController::PushScene(std::shared_ptr<Scene> scene)
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
	assert(!scene_.empty());

	input_->Update();
	scene_.front()->Update(input_);
}

void SceneController::Draw()
{
	auto& drawManager = DrawManager::GetInstance();
	auto rit = scene_.rbegin();
	for (; rit != scene_.rend(); rit++)
	{
		drawManager.AddQueList();
		(*rit)->Draw();
	}

	drawManager.Draw();
	postDrawExecuter_();
	postDrawExecuter_ = []() {};
}

SceneController::~SceneController()
{
}