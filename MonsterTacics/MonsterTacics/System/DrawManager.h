#pragma once
#include <memory>
#include <list>
#include <vector>
#include <map>
#include "LAYER.h"
#include "../Common/Geometry.h"

/// <summary>
/// �L���[�ɕK�v�ȗv�f
/// </summary>
struct DrawQue
{
	int imageID_;		// �摜ID
	Position2f pos_;	// ���W
	LAYER layer_;		// ���C���[
	double exRate_;		// �g�嗦
	double angle_;		// �p�x
	int zOrder_;		// ���s
	int blendMode_;		// �u�����h�ݒ�
	int blendParam_;	// �u�����h�̃p�����[�^�[
	bool reverseX_;		// X���]�t���O
	bool reverseY_;		// Y���]�t���O

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	DrawQue(int id, Position2f pos, LAYER layer,
		double exRate, double angle,int zOrder,
		int blendMode = -1, int blendParam = 255,
		bool reverseX = false, bool reverseY = false);
};

class DrawManager
{
private:

	DrawManager();
	~DrawManager();

	/// <summary>
	/// �J�X�^���f���[�^�[
	/// </summary>
	struct DrawManagerDeleter
	{
		void operator()(DrawManager* manager)const
		{
			delete manager;
		}
	};

	static std::unique_ptr<DrawManager, DrawManagerDeleter> sInstance_;			// ����

	// std::map<Layer, int> layerScreen_;										// �e���C���[�̃X�N���[��
	
	/// <summary>
	/// �V�[���X�^�b�N���L���[��p�ӂ���
	/// �X�^�b�N�����������Ă������Ɨ�����`��ł���悤��
	/// </summary>
	std::list<std::vector<DrawQue>> drawQueList_;								// �`����i�[

	int screenID_;																// �`��p�X�N���[��
public:
	/// <summary>
	/// �|�C���^�[�擾
	/// </summary>
	/// <returns></returns>
	static DrawManager& GetInstance(void)
	{
		return *sInstance_;
	};

	/// <summary>
	/// ������
	/// </summary>
	void Init(void);
	/// <summary>
	/// �L���[�ɗ��܂��Ă�����̂����ׂĕ`��
	/// </summary>
	void Draw(void);
	/// <summary>
	/// �V�����L���[�����
	/// </summary>
	void AddQueList(void);
	/// <summary>
	/// �L���[�ɒǉ�����
	/// </summary>
	/// <param name="drawQue">�L���[�ɒǉ�������</param>
	/// <returns>true : ����</returns>
	bool AddDrawQue(const DrawQue& drawQue);
};

