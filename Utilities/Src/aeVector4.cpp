#include "aeMath.h"

namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* Constant definitions
	/*************************************************************************************************/
	const aeVector4 ZERO = aeVector4(0, 0, 0, 0);

	/*************************************************************************************************/
	/* Constructors
	/*************************************************************************************************/
	aeVector4::aeVector4() 
	{
	}

	aeVector4::~aeVector4()
	{
	}

	aeVector4::aeVector4(const aeVector4& V)
	{
		*this = V;
	}

	aeVector4::aeVector4(float X, float Y, float Z, float W) : x(X), y(Y), z(Z), w(W)
	{
	}

	/*************************************************************************************************/
	/* Static functions implementation
	/*************************************************************************************************/

	float aeVector4::AngleBetweenVectors(const aeVector4 & V) const
	{
		if (*this == V)
			return 0;
		return aeMath::ArcCos((*this | V) / (~(*this)* ~(V)));
	}
}