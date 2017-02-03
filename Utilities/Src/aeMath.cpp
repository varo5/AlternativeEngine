#include "aeMath.h"

#include "aeVector2.h"
#include "aeVector2Int.h"
#include "aeVector3.h"
#include "aeVector4.h"
#include "aeQuaternion.h"
#include "aeMatrix3.h"
#include "aeMatrix4.h"

#include "aeRay.h"
#include "aeSphere.h"
#include "aeAABB.h"
#include "aePlane.h"

namespace aeEngineSDK
{
	bool CollisionRayToPlane(const aePlane& P, const aeRay& R, float& F, aeVector3& V)
	{
		aeVector3 NV = R.m_xDirection*R.m_fDistance;
		F = (P.d - (P | R.m_xPosition)) / (P | NV);
		if (F >= 0.0f && F <= 1.0f)
		{
			V = R.m_xPosition + NV*F;
			return true;
		}
		return false;
	}

	bool operator^(const aeVector3 & V, const aeAABB & AB)
	{
		return (
			V.x > AB.m_xMin.x && V.x < AB.m_xMax.x &&
			V.y > AB.m_xMin.y && V.y < AB.m_xMax.y &&
			V.z > AB.m_xMin.z && V.z < AB.m_xMax.z);
	}

	bool operator^(const aeSphere & S, const aeVector3 & V)
	{
		return (S.m_xPosition % V) <= S.m_fRadius;
	}

	bool operator^(const aeVector3 & V, const aeSphere & S)
	{
		return (S.m_xPosition % V) <= S.m_fRadius;
	}
	bool operator^(const aeSphere & S, const aePlane & P)
	{
		// Calculate a vector from the point on the plane to the center of the sphere
			aeVector3 vecTemp(S.m_xPosition - P);

		//Calculate the distance: dot product of the new vector with the plane's normal
		float fDist(vecTemp | P);

		if (fDist > S.m_fRadius)
		{
			//The sphere is not touching the plane
			return false;
		}

		//Else, the sphere is colliding with the plane
		return true;
	}

	bool operator^(const aePlane & P, const aeSphere & S)
	{
		// Calculate a vector from the point on the plane to the center of the sphere
		aeVector3 vecTemp(S.m_xPosition - P);

		//Calculate the distance: dot product of the new vector with the plane's normal
		float fDist(vecTemp | P);

		if (fDist > S.m_fRadius)
		{
			//The sphere is not touching the plane
			return false;
		}

		//Else, the sphere is colliding with the plane
		return true;
	}

	/*************************************************************************************************/
	/* Combined constructors
	/*************************************************************************************************/

	aeVector2::aeVector2(const aeVector2Int & V)
	{
		x = V.x;
		y = V.y;
	}

	aeVector2::aeVector2(const aeVector3 & V)
	{
		x = V.x;
		y = V.y;
	}

	aeVector2::aeVector2(const aeVector4 & V)
	{
		x = V.x;
		y = V.y;
	}

	aeVector2Int::aeVector2Int(const aeVector2 & V)
	{
		x = V.x;
		y = V.y;
	}

	aeVector2Int::aeVector2Int(const aeVector3 & V)
	{
		x = V.x;
		y = V.y;
	}

	aeVector2Int::aeVector2Int(const aeVector4 & V)
	{
		x = V.x;
		y = V.y;
	}

	aeVector3::aeVector3(const aeVector2 & V)
	{
		x = V.x;
		y = V.y;
		z = 0;
	}

	aeVector3::aeVector3(const aeVector2Int & V)
	{
		x = V.x;
		y = V.y;
		z = 0;
	}	

	aeVector3::aeVector3(const aeVector4 & V)
	{
		x = V.x;
		y = V.y;
		z = V.z;
	}

	aeVector4::aeVector4(const aeVector2 & V)
	{
		x = V.x;
		y = V.y;
		z = 0;
		w = 0;
	}

	aeVector4::aeVector4(const aeVector2Int & V)
	{
		x = V.x;
		y = V.y;
		z = 0;
		w = 0;
	}

	aeVector4::aeVector4(const aeVector3 & V)
	{
		x = V.x;
		y = V.y;
		z = V.z;
		w = 0;
	}

	aeMatrix3::aeMatrix3(const aeMatrix4& M)
	{
		f00 = M.f00; f01 = M.f01; f02 = M.f02;
		f10 = M.f10; f11 = M.f11; f12 = M.f12;
		f20 = M.f20; f21 = M.f21; f22 = M.f22;
	}

	aeMatrix4::aeMatrix4(const aeMatrix3& M)
	{
		f00 = M.f00; f01 = M.f01; f02 = M.f02; f03 = 0;
		f10 = M.f10; f11 = M.f11; f12 = M.f12; f13 = 0;
		f20 = M.f20; f21 = M.f21; f22 = M.f22; f23 = 0;
		f30 = 0; f31 = 0; f32 =0; f33 = 1;
	}
}