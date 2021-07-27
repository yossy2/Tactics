#include <type_traits>
#include "LAYER.h"

LAYER begin(LAYER)
{
	return LAYER::BackGround;
}

LAYER end(LAYER)
{
	return LAYER::Max;
}

LAYER operator++(LAYER& layer)
{
	if (layer != LAYER::Max)
	{
		layer = static_cast<LAYER>(std::underlying_type<LAYER>::type(layer) + 1);
	}
	return layer;
}

LAYER operator*(LAYER layer)
{
	return layer;
}
