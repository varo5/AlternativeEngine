#include "aeMath.h"


namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* Constant definitions
	/*************************************************************************************************/

	const aeVector2Int ZERO = aeVector2Int(0, 0);
	
	/*************************************************************************************************/
	/* Constructors
	/*************************************************************************************************/

	aeVector2Int::aeVector2Int()
	{
	}

	aeVector2Int::aeVector2Int(const aeVector2Int & V)
	{
		*this = V;
	}

	aeVector2Int::aeVector2Int(int32 X, int32 Y) : x(X), y(Y)
	{
	}

	aeVector2Int::~aeVector2Int()
	{
	}
}