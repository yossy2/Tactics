#pragma once

/// <summary>
/// è¨Ç≥Ç¢ÇŸÇ§Ç™Ç®Ç≠
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