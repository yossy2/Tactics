#pragma once

/// <summary>
/// �������ق�������
/// </summary>
enum class LAYER
{
	BackGround,
	Char,
	UI,
	Max
};

LAYER begin(LAYER);
LAYER end(LAYER);
LAYER operator++(LAYER& layer);
LAYER operator*(LAYER layer);