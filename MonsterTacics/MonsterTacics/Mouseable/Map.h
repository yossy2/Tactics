#pragma once
#include <memory>
#include "../Common/Geometry.h"
#include "../Game/TEAM_TAG.h"

class GameObject;
class Character;
class Mouse;

enum class MAP_STATE
{
	CLICK_UP = 0,
	MOUSE_OVER = 3
};

/// <summary>
/// �Q�[���v���C���̃}�X�̃N���X
/// �n�`����Q�[���I�u�W�F�N�g�̏�������
/// </summary>
class Map
{
private:
	int zOrder_;
	Position2f pos_;
	Vector2 mapNum_;	// �}�b�v�̍s��ԍ�
	MAP_STATE state_;

	std::weak_ptr<GameObject> gameObject_;

	/// <summary>
	/// �N���b�N���ꂽ���̏���
	/// </summary>
	/// <param name="mouse">�}�E�X</param>
	/// <returns>�}�E�X�ɕR�Â��邩�ǂ���</returns>
	bool OnClickDown(const Mouse& mouse);

	

public:
	Map(const Position2f& pos,const Vector2 mapNum,int zOrder);

	static int GetGridSquareSize();

	/// <summary>
	/// �}�E�X�Ƃ̓����蔻��
	/// </summary>
	/// <param name="mouse"></param>
	/// <returns></returns>
	bool IsHitWithMousePoint(const Mouse& mouse);

	/// <summary>
	/// �}�E�X���I�u�W�F�N�g�̏�ɂ���Ƃ��̏���
	/// </summary>
	/// <param name="mouse">�}�E�X</param>
	/// <returns>�}�E�X�ɕR�Â��邩�ǂ���</returns>
	bool MouseOver();

	std::shared_ptr<Character> HasCharacter();

	/// <summary>
	/// �}�E�X�ƂԂ����Ă��Ȃ��������̏���
	/// </summary>
	void NotHitWithMouse();

	/// <summary>
	/// �`��֐�
	/// </summary>
	void Draw();

	void SetObject(std::shared_ptr<GameObject> object);
	std::shared_ptr<GameObject> GetGameObject();
	const Position2f& GetPosition()const;
	const Vector2& GetMapNum()const;

	/// <summary>
	/// ���̃}�b�v�̈ړ��R�X�g��Ԃ�
	/// �����Ă���Object��L�����̈ړ����\�i��s�Ƃ��j�ŕς���Ă���
	/// ���̂�������������
	/// </summary>
	/// <param name="tag"></param>
	/// <returns></returns>
	int GetMoveCost(TEAM_TAG tag)const;
};