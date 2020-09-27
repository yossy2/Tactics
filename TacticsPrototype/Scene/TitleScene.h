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
	/// �X�V
	/// </summary>
	/// <param name="input">����</param>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;
	~TitleScene();
};

