#pragma once
#include <cmath>

//vector2�e���v���[�g
template <class T>
class Vector2D
{
public:
	T x;
	T y;
	Vector2D(T inx,T iny):x(inx),y(iny){}
	Vector2D() :x(0), y(0) {}

	Vector2D operator+(const Vector2D& rval)const
	{
		return Vector2D(x + rval.x, y + rval.y);
	};
	Vector2D operator-(const Vector2D& rval)const
	{
		return Vector2D(x - rval.x, y - rval.y);
	};
	void operator+=(const Vector2D v)
	{
		x += v.x;
		y += v.y;
	};

	void operator-=(const Vector2D v)
	{
		x -= v.x;
		y -= v.y;
	};

	void operator*=(T rval)
	{
		x *= rval;
		y *= rval;
	};

	bool operator == (const Vector2D v)
	{
		return (x == v.x) && (y == v.y);
	}

	bool operator != (const Vector2D v)
	{
		return !((x == v.x) && (y == v.y));
	}

	// �x�N�g���̑傫����Ԃ�
	T Magnitude()const
	{
		return std::hypot(x, y);
	}

	// �x�N�g���̒�����2���Ԃ�
	T SQMagnitude()const
	{
		return x*x + y*y;
	}

	void Normalize()
	{
		auto len = Magnitude();
		if (len == 0) return;

		x /= len;
		y /= len;
	}

	// ���K�����ꂽ�x�N�g����Ԃ�
	Vector2D Normalized()const
	{
		auto len = Magnitude();
		
		if (len == 0) return { 0,0 };

		Vector2D vec = { x / len,y / len };
		return vec;
	}

	static const Vector2D<float> ZERO;
	static const Vector2D<float> NIL;

	bool IsNil()const
	{
		return isnan(x) || isnan(y);
	}

	bool IsZero()const
	{
		return (x == 0) && (y == 0);
	}
};

// �x�N�g�����g��
template <class T>
Vector2D<T> operator * (const Vector2D<T>& lval, T rval)
{
	Vector2D<T> vec;
	vec.x = lval.x * rval;
	vec.y = lval.y * rval;
	return vec;
}

// ����
template <class T>
T operator * (const Vector2D<T>& lval, const Vector2D<T>& rval)
{
	return lval.x * rval.x + lval.y * rval.y;
}

template <class T>
T Dot (const Vector2D<T>& lval, const Vector2D<T>& rval)
{
	return lval.x * rval.x + lval.y * rval.y;
}

template <class T>
T Cross (const Vector2D<T>& lval, const Vector2D<T>& rval)
{
	return lval.x * rval.y - lval.y * rval.x;
}

using Vector2 = Vector2D<int>;
using Vector2f = Vector2D<float>;
using Position2 = Vector2;
using Position2f = Vector2f;

/// <summary>
/// ���˃x�N�g�������߂�
/// </summary>
/// <param name="ref">���˂��������x�N�g��</param>
/// <param name="wall">�Ǘp�̃x�N�g��</param>
Vector2f Reflected(Vector2f ref,Vector2f wall);

// �T�C�Y
struct Size
{
	int w, h;
	Size() :w(0), h(0) {};
	Size(int inw,int inh) :w(inw), h(inh) {};
};

// Rect
struct Rect
{
	Position2 pos;
	Size size;

	Rect() :pos(0,0), size(0,0) {};
	Rect(const Position2& p, const Size& s) :pos(p), size(s) {};
	Rect(int inx,int iny,int inw,int inh) :pos(inx,iny), size(inw,inh) {};

	int Top()const
	{
		return pos.y;
	}

	int Bottom()const
	{
		return pos.y + size.h;
	}

	int Left()const
	{
		return pos.x;
	}

	int Right()const 
	{
		return pos.x + size.w;
	}

	int Width()const
	{
		return size.w;
	}

	int Highth()const
	{
		return size.h;
	}

	Position2 Center()
	{
		return Position2(pos.x + size.w / 2,pos.y + size.h / 2);
	}
};

struct RectF
{
	Position2f pos;
	Size size;

	RectF() :pos(0, 0), size(0, 0) {};
	RectF(const Position2f& p, const Size& s) :pos(p), size(s) {};
	RectF(float inx, float iny, float inw, float inh) :pos(inx, iny), size(inw, inh) {};

	float Top()const
	{
		return pos.y;
	}

	float Bottom()const
	{
		return pos.y + static_cast<float>(size.h);
	}

	float Left()const
	{
		return pos.x;
	}

	float Right()const
	{
		return pos.x + static_cast<float>(size.w);
	}

	float Width()const
	{
		return static_cast<float>(size.w);
	}

	float Highth()const
	{
		return static_cast<float>(size.h);
	}

	Position2f Center()
	{
		return Position2f(pos.x + static_cast<float>(size.w / 2), pos.y + static_cast<float>(size.h / 2));
	}
};

/// <summary>
/// �_�̈ʒu�����R�Ȏl�p�`
/// </summary>
struct Quadrangle
{
	Position2f pos1;
	Position2f pos2;
	Position2f pos3;
	Position2f pos4;

	Quadrangle() :pos1(0, 0), pos2(0, 0), pos3(0, 0), pos4(0, 0) {};
	Quadrangle(const Position2f& p1, const Position2f& p2, const Position2f& p3, const Position2f&p4) 
		:pos1(p1), pos2(p2), pos3(p3), pos4(p4) {};

	void Draw(Vector2f offset, int color, bool fill);
};

struct Circle
{
	Position2f center;	// ���S
	float radius;		// ���a

	Circle() :center(0, 0), radius(0) {};
	Circle(const Position2f& c, float r) :center(c), radius(r) {};
};

struct Capsule
{
	Position2f start;		// �N�_
	Vector2f vec;			// �N�_��������P�[�_�܂ł̃x�N�g��
	float radius;
};

/// <summary>
/// ����
/// </summary>
struct Segment 
{
	Position2f start;//�N�_
	Vector2f vec;//�N�_��������P�[�_�܂ł̃x�N�g��
	Segment() {}
	Segment(const Position2f& s, const Position2f& v) :start(s), vec(v) {}
	Segment(float x, float y, float vx, float vy) :start(x, y), vec(vx, vy) {}
	static const Segment ZERO;
	static const Segment NIL;
	bool IsNil();
	Position2f End();
};

struct Matrix
{
	float m[3][3];
};

Matrix IdentityMat();

///���s�ړ��s���Ԃ�
///@param x X�������s�ړ���
///@param y Y�������s�ړ���
Matrix TranslateMat(float x, float y);

///��]�s���Ԃ�
///@param angle ��]�p�x
Matrix RotateMat(float angle);

///�Q�̍s��̏�Z��Ԃ�
///@param lmat ���Ӓl(�s��)
///@param rmat �E�Ӓl(�s��)
///@attention ��Z�̏����ɒ��ӂ��Ă�������
Matrix MultipleMat(const Matrix& lmat, const Matrix& rmat);

///�x�N�g���ɑ΂��čs���Z��K�p���A���ʂ̃x�N�g����Ԃ�
///@param mat �s��
///@param vec �x�N�g��
Vector2f MultipleVec(const Matrix& mat, const Vector2f& vec);