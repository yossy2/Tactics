#pragma once
#include "Scene.h"

class SceneController;

class TitleScene :
	public Scene
{
	friend SceneController;

private:
	TitleScene(SceneController& c);
public:

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="input">入力</param>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
	~TitleScene();
};

