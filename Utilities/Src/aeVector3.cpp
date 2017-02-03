#include "aeMath.h"

namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* Constructors
	/*************************************************************************************************/
	aeVector3::aeVector3()
	{
	}

	aeVector3::~aeVector3()
	{
	}

	aeVector3::aeVector3(const aeVector3 & V)
	{
		*this = V;
	}

	aeVector3::aeVector3(float X, float Y, float Z) : x(X), y(Y), z(Z)
	{
	}

	/*************************************************************************************************/
	/* Functions implementation
	/*************************************************************************************************/

	float aeVector3::AngleBetweenVectors(const aeVector3 & V) const
	{
		if (*this == V)
			return 0;
		return aeMath::ArcCos((*this|V) / (~(*this) * ~(V)));
	}

	void aeVector3::OrthoNormalize(aeVector3 & V)
	{
		aeVector3 normal = *this;
		*this = Normalized();

		aeVector3 proj = *this * (V | *this);

		V -= proj;
		V = V.Normalized();
	}
}