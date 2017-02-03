#include "aeMath.h"


namespace aeEngineSDK
{
	aeAABB::aeAABB()
	{
		m_xMin = aeVector3(aeMath::LOW_FLOAT, aeMath::LOW_FLOAT, aeMath::LOW_FLOAT);
		m_xMax = aeVector3(aeMath::MAX_FLOAT, aeMath::MAX_FLOAT, aeMath::MAX_FLOAT);
	}

	aeAABB::aeAABB(const aeAABB & A)
	{
		*this = A;
	}

	aeAABB::aeAABB(const aeVector3 & A, const aeVector3 & B)
	{
		m_xMin = aeVector3(aeMath::MAX_FLOAT, aeMath::MAX_FLOAT, aeMath::MAX_FLOAT);
		m_xMax = aeVector3(aeMath::LOW_FLOAT, aeMath::LOW_FLOAT, aeMath::LOW_FLOAT);

		m_xMin.x = aeMath::Min(m_xMin.x, A.x);
		m_xMin.y = aeMath::Min(m_xMin.y, A.x);
		m_xMin.z = aeMath::Min(m_xMin.z, A.x);
		m_xMin.x = aeMath::Min(m_xMin.x, B.x);
		m_xMin.y = aeMath::Min(m_xMin.y, B.y);
		m_xMin.z = aeMath::Min(m_xMin.z, B.z);

		m_xMax.x = aeMath::Max(m_xMax.x, A.x);
		m_xMax.y = aeMath::Max(m_xMax.y, A.x);
		m_xMax.z = aeMath::Max(m_xMax.z, A.x);
		m_xMax.x = aeMath::Max(m_xMax.x, B.x);
		m_xMax.y = aeMath::Max(m_xMax.y, B.y);
		m_xMax.z = aeMath::Max(m_xMax.z, B.z);
	}

	aeAABB::~aeAABB()
	{
	}

	inline bool aeAABB::operator^(const aeAABB& AB)
	{
		return(
			m_xMax.x > AB.m_xMin.x &&
			m_xMin.x < AB.m_xMax.x &&
			m_xMax.y > AB.m_xMin.y &&
			m_xMin.y < AB.m_xMax.y &&
			m_xMax.z > AB.m_xMin.z &&
			m_xMin.z < AB.m_xMax.z);
	}

	inline bool aeAABB::operator^(const aeVector3 & V)
	{
		return (
			V.x >= m_xMin.x && V.x <= m_xMax.x &&
			V.y >= m_xMin.y && V.y <= m_xMax.y &&
			V.z >= m_xMin.z && V.z <= m_xMax.z);
	}
}
