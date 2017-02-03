#pragma once

namespace aeEngineSDK
{
	struct AE_UTILITY_EXPORT aeAABB
	{
		/*************************************************************************************************/
		/* Constructors declaration
		/*************************************************************************************************/
	public:
		aeAABB();
		aeAABB(const aeAABB& A);
		aeAABB(const aeVector3& A, const aeVector3& B);
		~aeAABB();

		/*************************************************************************************************/
		/* Variable declaration
		/*************************************************************************************************/
	public:
		aeVector3 m_xMax;
		aeVector3 m_xMin;

		/*************************************************************************************************/
		/* Functions declaration
		/*************************************************************************************************/
	public:
		bool operator^(const aeAABB& AB);
		bool operator^(const aeVector3& V);
	};
}
