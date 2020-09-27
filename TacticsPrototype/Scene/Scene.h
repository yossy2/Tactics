#pragma once

class SceneController;
class Scene
{
	friend SceneController;
protected:
	SceneController& controller_;
	Scene() = default;
	Scene(SceneController& controller);
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual ~Scene() = default;
};

