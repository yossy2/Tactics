#pragma once
#include "../Common/Geometry.h"

class Mouse;

enum class MOUSEABLE_STATE
{
	CLICK_DOWN,
	CLICK_HOLD,
	CLICK_UP,
	MOUSE_OVER
};

/// <summary>
/// �}�E�X�ɔ�������I�u�W�F�N�g�̊��N���X
/// </summary>
class MouseableObject
{
protected:
	bool isRelease_ = false;
	bool isDeletable_ = false;
	/// <summary>
	/// �N���b�N���ꂽ���̏���
	/// </summary>
	/// <param name="mouse">�}�E�X</param>
	/// <returns>�}�E�X�ɕR�Â��邩�ǂ���</returns>
	virtual bool OnClickDown(const Mouse& mouse) = 0;

	/// <summary>
	/// ����������Ă���Ƃ��̏���
	/// </summary>
	/// <param name="mouse">�}�E�X</param>
	virtual void OnClickHold(const Mouse& mouse) = 0;

	/// <summary>
	/// �{�^���������ꂽ���̏���
	/// </summary>
	/// <param name="mouse">�}�E�X</param>
	virtual void OnClickUp(const Mouse& mouse) = 0;

	/// <summary>
	/// �}�E�X���I�u�W�F�N�g�̏�ɂ���Ƃ��̏���
	/// </summary>
	/// <param name="mouse">�}�E�X</param>
	/// <returns>�}�E�X�ɕR�Â��邩�ǂ���</returns>
	virtual bool MouseOver(const Mouse& mouse) = 0;

public:
	virtual ~MouseableObject() = default;

	/// <summary>
	/// �}�E�X�Ƃ̓����蔻��
	/// </summary>
	/// <param name="mouse"></param>
	/// <returns></returns>
	virtual bool IsHitWithMousePoint(const Mouse& mouse) = 0;

	/// <summary>
	/// �}�E�X�̏�Ԃ����āA
	/// ���s����֐������߂�
	/// �}�E�X���I�u�W�F�N�g�̏�ɂ���̑O��
	/// </summary>
	/// <param name="mouse"></param>
	/// <returns>�}�E�X�ɕR�Â��邩�ǂ���</returns>
	bool SelectFuncWithMouseState(const Mouse& mouse);

	/// <summary>
	/// �}�E�X�ƕR�Â��Ă���Ƃ��̏���
	/// </summary>
	/// <param name="mouse"></param>
	void Holded(const Mouse& mouse);

	/// <summary>
	/// �}�E�X�Ɠ������Ă��Ȃ��������̏���
	/// </summary>
	virtual void NotHitWithMouse() = 0;

	/// <summary>
	/// �`��֐�
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// ������Ă�����̂�������邩�ǂ����̃t���O��Ԃ�
	/// </summary>
	/// <returns></returns>
	bool IsRelease();

	/// <summary>
	/// �폜�\��
	/// </summary>
	/// <returns></returns>
	bool IsDeletable();

	/// <summary>
	/// �}�E�X�ɂ������Ƃ��ɌĂ΂��
	/// �Œ�ł�isRelease��false�ɂ���
	/// </summary>
	virtual void Hold();
};

