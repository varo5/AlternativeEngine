#include "aeFrustum.h"

namespace aeEngineSDK
{
	aeFrustum::aeFrustum()
	{
		m_xTransform = aeMatrix4::Identity();
		m_xNear = aePlane(0, 0, -1, -(m_fNear = 1));
		m_xFar = aePlane(0, 0, -1, -(m_fFar = 1000));

		float e = 1.0f / aeMath::Tan((m_fFOV = aeMath::Deg2Rad(60)) * 0.5f);

		float oose1 = 1.0f / aeMath::Sqrt(e*e + 1);
		float oosea = 1.0f / aeMath::Sqrt(e*e + m_fFOV*m_fFOV);

		m_xLeft = aePlane(e*oose1, 0, -oose1, 0);
		m_xRight = aePlane(-e*oose1, 0, -oose1, 0);
		m_xBottom = aePlane(0, e*oosea, -m_fFOV*oosea, 0);
		m_xTop = aePlane(0, -e*oosea, -m_fFOV*oosea, 0);
	}

	aeFrustum::aeFrustum(const aeFrustum & F)
	{
		*this = F;
	}

	aeFrustum::aeFrustum(const float & Near, const float & Far, const float & FOV)
	{
		m_xTransform = aeMatrix4::Identity();

		m_xNear = aePlane(0, 0, -1, -(m_fNear = Near));
		m_xFar = aePlane(0, 0, -1, -(m_fFar = Far));

		float e = 1.0f / aeMath::Tan((m_fFOV = FOV) * 0.5f);

		float oose1 = 1.0f / aeMath::Sqrt(e*e + 1);
		float oosea = 1.0f / aeMath::Sqrt(e*e + m_fFOV*m_fFOV);

		m_xLeft = aePlane(e*oose1, 0, -oose1, 0);
		m_xRight = aePlane(-e*oose1, 0, -oose1, 0);
		m_xBottom = aePlane(0,e*oosea,-m_fFOV*oosea,0);
		m_xTop = aePlane(0, -e*oosea, -m_fFOV*oosea, 0);
	}

	aeFrustum::~aeFrustum()
	{
	}

	inline float aeFrustum::GetZoom()
	{
		return 1.0f / aeMath::Tan(m_fFOV * 0.5f);
	}

	inline float aeFrustum::GetFOV()
	{
		return m_fFOV;
	}

	inline float aeFrustum::GetNearDistance()
	{
		return m_fNear;
	}

	inline float aeFrustum::GetFarDistance()
	{
		return m_fFar;
	}

	void aeFrustum::SetZoom(const float & Zoom)
	{
		m_fFOV = 2.0f * aeMath::ArcTan(1 / Zoom);

		float e = 1.0f / aeMath::Tan((m_fFOV) * 0.5f);

		float oose1 = 1.0f / aeMath::Sqrt(e*e + 1);
		float oosea = 1.0f / aeMath::Sqrt(e*e + m_fFOV*m_fFOV);

		m_xLeft = aePlane(e*oose1, 0, -oose1, 0);
		m_xRight = aePlane(-e*oose1, 0, -oose1, 0);
		m_xBottom = aePlane(0, e*oosea, -m_fFOV*oosea, 0);
		m_xTop = aePlane(0, -e*oosea, -m_fFOV*oosea, 0);
	}

	void aeFrustum::SetFOV(const float & FOV)
	{
		float e = 1.0f / aeMath::Tan((m_fFOV = FOV) * 0.5f);

		float oose1 = 1.0f / aeMath::Sqrt(e*e + 1);
		float oosea = 1.0f / aeMath::Sqrt(e*e + m_fFOV*m_fFOV);

		m_xLeft = aePlane(e*oose1, 0, -oose1, 0);
		m_xRight = aePlane(-e*oose1, 0, -oose1, 0);
		m_xBottom = aePlane(0, e*oosea, -m_fFOV*oosea, 0);
		m_xTop = aePlane(0, -e*oosea, -m_fFOV*oosea, 0);
	}

	void aeFrustum::SetNearDistance(const float & Near)
	{
		m_xNear = aePlane(0, 0, -1, -(m_fNear = Near));
	}

	void aeFrustum::SetFarDistance(const float & Far)
	{
		m_xFar = aePlane(0, 0, -1, -(m_fFar = Far));
	}

	void aeFrustum::UpdateFrustum(const aeQuaternion & Rotation, const aeVector3 & Position)
	{
		m_xNear = aePlane(0, 0, -1, -(m_fNear));
		m_xFar = aePlane(0, 0, -1, -(m_fFar));

		float e = 1.0f / aeMath::Tan((m_fFOV) * 0.5f);

		float oose1 = 1.0f / aeMath::Sqrt(e*e + 1);
		float oosea = 1.0f / aeMath::Sqrt(e*e + m_fFOV*m_fFOV);

		m_xLeft = aePlane(e*oose1, 0, -oose1, 0);
		m_xRight = aePlane(-e*oose1, 0, -oose1, 0);
		m_xBottom = aePlane(0, e*oosea, -m_fFOV*oosea, 0);
		m_xTop = aePlane(0, -e*oosea, -m_fFOV*oosea, 0);

		for (int i = 0; i < 6; ++i)
		{
			P[i].Transform(Rotation, Position);
		}
	}

	void aeFrustum::UpdateFrustum(const aeMatrix3 & Rotation, const aeVector3 & Position)
	{
		m_xNear = aePlane(0, 0, -1, -(m_fNear));
		m_xFar = aePlane(0, 0, -1, -(m_fFar));

		float e = 1.0f / aeMath::Tan((m_fFOV) * 0.5f);

		float oose1 = 1.0f / aeMath::Sqrt(e*e + 1);
		float oosea = 1.0f / aeMath::Sqrt(e*e + m_fFOV*m_fFOV);

		m_xLeft = aePlane(e*oose1, 0, -oose1, 0);
		m_xRight = aePlane(-e*oose1, 0, -oose1, 0);
		m_xBottom = aePlane(0, e*oosea, -m_fFOV*oosea, 0);
		m_xTop = aePlane(0, -e*oosea, -m_fFOV*oosea, 0);

		for (int i = 0; i < 6; ++i)
		{
			P[i].Transform(Rotation, Position);
		}
	}

	void aeFrustum::UpdateFrustum(const aeMatrix4& Transform)
	{
		m_xNear = aePlane(0, 0, -1, -(m_fNear));
		m_xFar = aePlane(0, 0, -1, -(m_fFar));

		float e = 1.0f / aeMath::Tan((m_fFOV) * 0.5f);

		float oose1 = 1.0f / aeMath::Sqrt(e*e + 1);
		float oosea = 1.0f / aeMath::Sqrt(e*e + m_fFOV*m_fFOV);

		m_xLeft = aePlane(e*oose1, 0, -oose1, 0);
		m_xRight = aePlane(-e*oose1, 0, -oose1, 0);
		m_xBottom = aePlane(0, e*oosea, -m_fFOV*oosea, 0);
		m_xTop = aePlane(0, -e*oosea, -m_fFOV*oosea, 0);

		for (int i = 0; i < 6; ++i) 
		{
			P[i].Transform(Transform);
		}
	}

	AE_FRUSTUM_DETECTIONS aeFrustum::DetectIntersection(const aeVector3 & Point)
	{
		// various distances
		float fDistance;

		// calculate our distances to each of the planes
		for (int i = 0; i < 6; ++i)
		{

			// find the distance to this plane
			fDistance = (P[i]|(Point)) + P[i].d;

			// if this distance is < -sphere.radius, we are outside
			if (fDistance < 0)
				return(AE_FRUSTUM_DETECTIONS::AE_FRUSTUM_OUT);
		}

		// otherwise we are fully in view
		return AE_FRUSTUM_DETECTIONS::AE_FRUSTUM_IN;
	}
}