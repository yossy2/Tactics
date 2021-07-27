#pragma once
#include "Geometry.h"


/// <summary>
/// �}�b�v�̃}�X�ڈ��̃N���X
/// </summary>
class MapSquare
{
private:
	RectF rect_;			// ���W�ϊ��O�̋�`�A�����蔻��Ɏg��
	Quadrangle quad_;	// ���W�ԊҌ�̎l�p�`�A���ۂɕ`�悳���
	bool isMouseOver_ = false;
public:
	MapSquare(RectF rect,Quadrangle quad);
	void Update(Position2f mousePos);
	void Draw();
};

