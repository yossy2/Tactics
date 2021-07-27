#pragma once
#include <memory>

struct InputState;
class SceneController;

class Scene
{
	friend SceneController;
protected:
	SceneController& controller_;
	Scene() = default;
	Scene(SceneController& controller);
public:
	virtual void Update(std::shared_ptr<InputState> input) = 0;
	virtual void Draw() = 0;
	virtual ~Scene() = default;
};