#pragma once
#include <memory>
#include <deque>
#include <functional>

class Scene;
class Application;
struct InputState;

class SceneController
{
	friend Application;
private:
	std::shared_ptr<InputState> input_;
	std::deque<std::shared_ptr<Scene>> scene_;
	SceneController();
	std::function<void(void)> postDrawExecuter_;
public:
	/// <summary>
	/// �V�[���̐؂�ւ����s��
	/// </summary>
	/// <param name="scene">�V�����؂�ւ���V�[��</param>
	/// <attention>�O�̃V�[���͌ďo����ɍ폜�����ׁA
	/// ���̊֐��̌Ăяo�������폜�Ώۂ������ꍇ�ɂ́A
	/// ���̊֐��̌Ăяo����ɏ������s���Ă͂Ȃ�Ȃ�</attention>
	void ChangeScene(std::shared_ptr<Scene> scene);

	/// <summary>
	/// �V�[���X�^�b�N��S�폜���A�V�����V�[���ɐ؂�ւ���
	/// </summary>
	/// <param name="scene">�V�����؂�ւ���V�[��</param>
	/// <attention>�O�̃V�[���͌ďo����ɍ폜�����ׁA
	/// ���̊֐��̌Ăяo�������폜�Ώۂ������ꍇ�ɂ́A
	/// ���̊֐��̌Ăяo����ɏ������s���Ă͂Ȃ�Ȃ�</attention>
	void CleanChangeScene(std::shared_ptr<Scene> scene);

	/// <summary>
	/// �V�[�����V�[���X�^�b�N�ɐς�
	/// </summary>
	/// <param name="scene">�ςރV�[��</param>
	void PushScene(std::shared_ptr<Scene> scene);

	/// <summary>
	/// �V�[�����V�[���X�^�b�N����폜����
	/// </summary>
	void PopScene();

	/// <summary>
	/// �V�[���X�^�b�N��S�폜����
	/// </summary>
	void ClearScene();

	/// <summary>
	/// �V�[���X�^�b�N�̐擪�̃V�[���̍X�V���s��
	/// </summary>
	void Update();

	/// <summary>
	/// �V�[���X�^�b�N�ɂ���V�[�������ׂĕ`�悷��
	/// </summary>
	void Draw();

	~SceneController();
};