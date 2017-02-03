#include "aeMath.h"

namespace aeEngineSDK
{
	aeSphere::aeSphere()
	{
	}

	aeSphere::aeSphere(const aeSphere & A)
	{
		*this = A;
	}

	aeSphere::aeSphere(const aeVector3 & Pos, float Radius)
	{
		m_xPosition = Pos;
		m_fRadius = Radius;
	}

	aeSphere::~aeSphere()
	{
	}

	bool aeSphere::operator^(const aeSphere & S)
	{
		return m_xPosition % S.m_xPosition <= m_fRadius;
	}
}