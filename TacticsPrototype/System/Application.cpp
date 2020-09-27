#include "Application.h"
#include <DxLib.h>
#include "../Scene/SceneController.h"
#include "../Geometry.h"

namespace
{
	bool _isExit = false;
	Size viewSize_;
}

Application& Application::Instance()
{
	static Application instance;
	return instance;
}

Application::Application()
{
}

Application::~Application()
{
}

bool Application::Initialize(void)
{
	viewSize_ = { 1280,720 };
	DxLib::SetGraphMode(viewSize_.w, viewSize_.h, 32);
	DxLib::ChangeWindowMode(true);
	DxLib::SetWindowText("Prototype");
	if (DxLib_Init()) 
	{
		return false;
	}
	sceneController_.reset(new SceneController());

	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	return true;
}

void Application::Run(void)
{
	while (DxLib::ProcessMessage() == 0) 
	{
		DxLib::ClsDrawScreen();
		sceneController_->Update();
		sceneController_->Draw(); 
		DxLib::ScreenFlip();

		if (_isExit) break;
	}

	sceneController_->ClearScene();
}

void Application::Terminate(void)
{
	DxLib_End();
}

void Application::Exit(void)
{
	_isExit = true;
}

const Viewport& Application::GetViewport() const
{
	return viewport_;
}

Size Viewport::GetSize() const
{
	return viewSize_;
}
