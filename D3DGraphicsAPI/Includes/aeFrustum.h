#pragma once
#include <aeMath.h>
#include "aePrerequisitesGraphics.h"


namespace aeEngineSDK
{
	enum struct AE_FRUSTUM_DETECTIONS : uint8
	{
		AE_FRUSTUM_OUT,
		AE_FRUSTUM_INTERSECTION,
		AE_FRUSTUM_IN
	};

	class AE_GRAPHICS_EXPORT aeFrustum
	{
	public:
		aeFrustum();
		aeFrustum(const aeFrustum& F);
		aeFrustum(const float& Near, const float& Far, const float& FOV);
		~aeFrustum();

	public:
		float GetZoom();
		float GetFOV();
		float GetNearDistance();
		float GetFarDistance();

		void SetZoom(const float& Zoom);
		void SetFOV(const float& FOV);
		void SetNearDistance(const float& Near);
		void SetFarDistance(const float& Far);

	public:
		void UpdateFrustum(const aeQuaternion& Rotation, const aeVector3& Position);
		void UpdateFrustum(const aeMatrix3& Rotation, const aeVector3& Position);
		void UpdateFrustum(const aeMatrix4& Transform);

		AE_FRUSTUM_DETECTIONS DetectIntersection(const aeVector3& Point);
	private:
		float m_fNear, m_fFar, m_fFOV;
		aeMatrix4 m_xTransform;

		union 
		{
			struct  
			{
				aePlane m_xNear, m_xFar, m_xLeft, m_xRight, m_xBottom, m_xTop;
			};
			aePlane P[6];
		};
		
	};
}
