#pragma once
#include <vector>
#include <memory>

class MouseableObject;
class Mouse;

/// <summary>
/// �}�E�X�ɔ���������́iMouseableObject�j���Ǘ�����N���X
/// �V�[���R���g���[���[�iSceneController�j������
/// </summary>
class MouseableManager
{
private:
	std::vector<std::shared_ptr<MouseableObject>> mouseables_;
public:

	/// <summary>
	/// �����Ă�I�u�W�F�N�g�ƃ}�E�X�Ƃ��ꂼ�ꓖ���蔻����s��
	/// </summary>
	void CheckHitWithMouse(const Mouse& mouse);

	/// <summary>
	/// �S�I�u�W�F�N�g�̕`��
	/// </summary>
	void Draw();

	void AddMouseableObject(std::shared_ptr<MouseableObject> mouseable);
};
