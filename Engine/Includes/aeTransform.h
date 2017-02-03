#pragma once
#include <aePrerequisitesUtil.h>
#include "aePrerequisitesEngine.h"
#include <aeMath.h>

namespace aeEngineSDK
{
	class aeGameObject;
	class AE_ENGINE_EXPORT aeTransform
	{
	private:		
		aeQuaternion m_xGlobalRotation;
		aeVector3 m_xGlobalPosition;
		aeVector3 m_xGlobalScale;

		aeQuaternion m_xLocalRotation;
		aeVector3 m_xLocalPosition;
		aeVector3 m_xLocalScale;

	public:
		aeTransform();
		aeTransform(aeGameObject* GO);
		aeTransform(const aeTransform& T);
		~aeTransform();

	public:
		aeGameObject* m_pGameObject;
		aeTransform* m_pParent;
		Vector<aeTransform*> m_aChildren;

	public:
		void SetPosition(const aeVector3& Position);
		void SetRotation(const aeVector3& Rotation);
		void SetRotation(const aeQuaternion& Rotation);
		void SetScale(const aeVector3& Scale);
		void SetLocalPosition(const aeVector3& Position);
		void SetLocalRotation(const aeVector3& Rotation);
		void SetLocalRotation(const aeQuaternion& Rotation);
		void SetLocalScale(const aeVector3& Scale);

		aeVector3 GetPosition();
		aeQuaternion GetRotation();
		aeVector3 GetEulerRotation();
		aeVector3 GetScale();
		aeVector3 GetLocalPosition();
		aeQuaternion GetLocalRotation();
		aeVector3 GetLocalEulerRotation();
		aeVector3 GetLocalScale();

		void Translate(const aeVector3& Translation);
		void Scale(const aeVector3& Scalation);
		void Rotate(const aeVector3& Rotation);

		void TranslateLocal(const aeVector3& Translation);
		void ScaleLocal(const aeVector3& Scalation);
		void RotateLocal(const aeVector3& Rotation);

		void TranslateTo(const aeVector3& NewPosition, float Proportion = 1.0f);
		void ScaleTo(const aeVector3& NewScale, float Proportion = 1.0f);
		void RotateTo(const aeVector3& NewRotation, float Proportion = 1.0f);
		void RotateAround(const aeVector3& Position, const aeVector3& Rotation, float Proportion = 1.0f);
		void LookAt(const aeVector3& Target);

		void TranslateForward(float Distance);
		void TranslateSideWays(float Distance);
		void RotateView(float roll, float pitch, float yaw);

		aeMatrix4 GetGlobalMatrix() const;
		aeMatrix4 GetLocalMatrix() const;
		aeMatrix4 GetRealMatrix() const;
		aeMatrix4 GetViewMatrix(aeVector3 Up);
		aeMatrix4 GetViewMatrix(aeVector3 Target, aeVector3 Up);
		aeMatrix4 GetProjectionMatrix(float Near, float Far, float FieldOfView, float AspectRatio);
	};
}
