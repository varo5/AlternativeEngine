#include "aeMath.h"

namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* Constant definitions
	/*************************************************************************************************/

	const aeVector2 ZERO = aeVector2(0.0f, 0.0f);


	/*************************************************************************************************/
	/* Constructors
	/*************************************************************************************************/

	aeVector2::aeVector2()
	{
	}

	aeVector2::aeVector2(const aeVector2 & V)
	{
		*this = V;
	}

	aeVector2::aeVector2(float X, float Y) : x(X), y(Y)
	{
	}

	aeVector2::~aeVector2()
	{
	}

	/*************************************************************************************************/
	/* Static functions implementation
	/*************************************************************************************************/
	
	float aeVector2::AngleBetweenVectors(const aeVector2 & V) const
	{///It gets the angle by using the definition of the dot product, and gives it direction getting the orientation given by the sign of the cross product.
		if (*this == V)
			return 0;
		float fAngle = aeMath::FastArcCos((*this | V) / (~(*this) * ~(V)));
		if ((*this^V) < 0)
		{
			fAngle *= -1;
		}
		return fAngle;
	}
}