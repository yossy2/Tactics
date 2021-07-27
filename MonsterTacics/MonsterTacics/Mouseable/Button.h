#pragma once
#include "MouseableObject.h"
#include <memory>
#include <functional>
#include <unordered_map>
#include <string>


class Button :public MouseableObject
{
	std::shared_ptr<Shape> shape_;
	std::unordered_map<MOUSEABLE_STATE,std::function<void()>> functionMap_;
	std::vector<int> imageHandle_;
	MOUSEABLE_STATE state_;

	/// <summary>
	/// �N���b�N���ꂽ���̏���
	/// </summary>
	/// <param name="mouse">�}�E�X</param>
	/// <returns>�}�E�X�ɕR�Â��邩�ǂ���</returns>
	bool OnClickDown(const Mouse& mouse)override;

	/// <summary>
	/// ����������Ă���Ƃ��̏���
	/// </summary>
	/// <param name="mouse">�}�E�X</param>
	void OnClickHold(const Mouse& mouse)override;

	/// <summary>
	/// �{�^���������ꂽ���̏���
	/// </summary>
	/// <param name="mouse">�}�E�X</param>
	void OnClickUp(const Mouse& mouse)override;

	/// <summary>
	/// �}�E�X���I�u�W�F�N�g�̏�ɂ���Ƃ��̏���
	/// </summary>
	/// <param name="mouse">�}�E�X</param>
	/// <returns>�}�E�X�ɕR�Â��邩�ǂ���</returns>
	bool MouseOver(const Mouse& mouse)override;

public:
	Button(std::shared_ptr<Shape> shape, std::unordered_map<MOUSEABLE_STATE, std::function<void()>>& func,std::string fileName);
	/// <summary>
	/// �}�E�X�Ƃ̓����蔻��
	/// </summary>
	/// <param name="mouse"></param>
	/// <returns></returns>
	bool IsHitWithMousePoint(const Mouse& mouse)override;

	/// <summary>
	/// �}�E�X�ƂԂ����Ă��Ȃ��������̏���
	/// </summary>
	void NotHitWithMouse()override;

	/// <summary>
	/// �`��֐�
	/// </summary>
	void Draw()override;
};