#pragma once

namespace aeEngineSDK
{
	struct AE_UTILITY_EXPORT aeRay
	{
		/*************************************************************************************************/
		/* Constructors declaration
		/*************************************************************************************************/
	public:
		aeRay();
		aeRay(const aeRay& A);
		~aeRay();

		/*************************************************************************************************/
		/* Variable declaration
		/*************************************************************************************************/
	public:
		aeVector3 m_xPosition;
		aeVector3 m_xDirection;
		float m_fDistance;
	};
}

