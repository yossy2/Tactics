#pragma once
// ���p�֐��w�b�_�[

// ���b�v�A���E���h�֐�
// value������l�ɒB�����牺���l�ɖ߂��A
// �����l�ɒB���Ă��������l�ɖ߂��B
// �߂�l�͉����l�ɂ͂Ȃ邪����l�ɂ͂Ȃ�Ȃ�
// ��1�Fwrap( 5, 0,5)->  0
// ��2�Fwrap(-5,-5,5)-> -5
// ��3�Fwrap(-6,-5,5)->  4 (5 - 1)
int Wrap(int value, int low, int high);

// �x���@�̊p�x���ʓx�@�ɕϊ�
float ConvertToRadians(float deg);

// �ʓx�@�̊p�x��x���@�ɕϊ�
float ConvertToDegrees(float rad);