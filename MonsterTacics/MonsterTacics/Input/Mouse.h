#pragma once
#include <memory>
#include <vector>
#include "../Common/Geometry.h"

class MouseableObject;

/// <summary>
/// �}�E�X�{�^��
/// ���l��DxLib�̎d�l�Ɋ�Â�
/// </summary>
enum class MOUSE_BUTTON
{
	LEFT = 0x0001,	// ��
	RIGHT = 0x0002,	// �E
	MIDDLE = 0x0004,	// ����
};

/// <summary>
/// �}�E�X�̓��͏󋵂��Ǘ�����N���X
/// </summary>
class Mouse
{
private:
	Vector2 pos_;
	int buttonState_[2];
	int currentBufferNum_ = 0;
	int wheelRotateVolume_ = 0;

	mutable std::vector<std::weak_ptr<MouseableObject>> holdingObjects_;	// �R�Â��Ă���I�u�W�F�N�g

	/// <summary>
	/// ���݂�buttonState��Ԃ�
	/// </summary>
	/// <returns>���݂�buttonState</returns>
	int CurrentButtonState()const;

	/// <summary>
	/// 1�t���[���O��buttonState��Ԃ�
	/// </summary>
	/// <returns>1�t���[���O��buttonState</returns>
	int OldButtonState()const;
public:
	void Update();

	/// <summary>
	/// �{�^���������ꂽ�u�Ԃ����肷��֐�
	/// </summary>
	/// <param name="button">���肵�����{�^���̎��</param>
	/// <returns>�w�肵���{�^���������ꂽ�u�Ԃ�</returns>
	bool GetButtonDown(MOUSE_BUTTON button)const;

	/// <summary>
	/// �{�^����������Ă��邩���肷��֐�
	/// </summary>
	/// <param name="button">���肵�����{�^���̎��</param>
	/// <returns>�w�肵���{�^����������Ă��邩</returns>
	bool GetButton(MOUSE_BUTTON button)const;

	/// <summary>
	/// �{�^���������ꂽ�u�Ԃ�����
	/// </summary>
	/// <param name="button">���肵�����{�^���̎��</param>
	/// <returns>�w�肵���{�^���������ꂽ�u�Ԃ�</returns>
	bool GetButtonUp(MOUSE_BUTTON button)const;

	Position2 GetPosition()const;

	/// <summary>
	/// �}�E�X�ɕR�Â���I�u�W�F�N�g�̃Z�b�g
	/// �h���b�O�ňړ���������̂ȂǂɎg��
	/// MouseableObject����Ăяo���̂�const
	/// </summary>
	/// <param name="obj">�R�Â������I�u�W�F�N�g�̃|�C���^</param>
	void Hold(std::shared_ptr<MouseableObject> obj)const;

	/// <summary>
	/// �������}�E�X�ƕR�Â��Ă�I�u�W�F�N�g�Ɠ�����������
	/// </summary>
	/// <param name="obj">���肵�����I�u�W�F�N�g</param>
	/// <returns>�������Ftrue</returns>
	bool EqualHoldingObject(std::shared_ptr<MouseableObject> obj) const;

	std::vector<std::weak_ptr<MouseableObject>>& GetHoldingObjects()const;

	/// <summary>
	/// �}�E�X�ɕR�Â���I�u�W�F�N�g�̃N���A
	/// MouseableObject����Ăяo���̂�const
	/// </summary>
	void ClearHoldingObject()const;

	/// <summary>
	/// �}�E�X�z�C�[���̉�]�ʂ𓾂�
	/// ��O�F�}�C�i�X�l�A���F�v���X�l
	/// </summary>
	/// <returns>�z�C�[���̉�]�ʁ@��O�F�}�C�i�X�l�A���F�v���X�l</returns>
	int GetWheelRotateVolume()const;
};