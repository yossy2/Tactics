#pragma once
#include <memory>

class SceneController;
struct Size;


// �\�����ׂ���ʂ̏�������
class Viewport
{
public:
	Size GetSize()const;
};

/// <summary>
/// Application(�V���O���g���N���X)
/// main�֐�����Ă΂�邽����̃N���X
/// �Q�[���̏������A�N���A�I���������s���B
/// �Q�[�����n�܂��ďI���܂ŋ��ʂŎg�p����v�f��
/// ���̃N���X�̎������Ƃ���
/// </summary>
class Application
{
private:
	// �����֎~
	Application();

	// �R�s�[�A����֎~
	Application(const Application&) = delete;
	void operator=(const Application&) = delete;

	std::unique_ptr<SceneController> sceneController_;
	Viewport viewport_;
public:
	static Application& Instance();

	~Application();

	/// <summary>
	/// ������
	/// </summary>
	bool Initialize(void);

	/// <summary>
	/// �Q�[���N��
	/// </summary>
	void Run(void);

	/// <summary>
	/// �I������
	/// </summary>
	void Terminate(void);

	/// <summary>
	/// �A�v���P�[�V�������I������
	/// </summary>
	void Exit(void);

	const Viewport& GetViewport()const;
};