#include "aeTransform.h"
#include "aeGameObject.h"

namespace aeEngineSDK
{
	aeTransform::aeTransform()
	{
		m_pGameObject = nullptr;
		m_pParent = nullptr;

		m_xGlobalPosition = aeVector3(0,0,0);
		m_xGlobalRotation = aeQuaternion(0,0,0);
		m_xGlobalScale = aeVector3(1, 1, 1);

		m_xLocalPosition = aeVector3(0, 0, 0);
		m_xLocalRotation = aeQuaternion(0, 0, 0);;
		m_xLocalScale = aeVector3(1, 1, 1);
	}

	aeTransform::aeTransform(aeGameObject * GO)
	{
		m_pGameObject = GO;
		m_pParent = nullptr;

		m_xGlobalPosition = aeVector3(0, 0, 0);
		m_xGlobalRotation = aeQuaternion(0, 0, 0);
		m_xGlobalScale = aeVector3(1, 1, 1);

		m_xLocalPosition = aeVector3(0, 0, 0);
		m_xLocalRotation = aeQuaternion(0, 0, 0);;
		m_xLocalScale = aeVector3(1, 1, 1);
	}

	aeTransform::aeTransform(const aeTransform & T)
	{
		*this = T;
	}

	aeTransform::~aeTransform()
	{
		m_pGameObject = nullptr;
		m_pParent = nullptr;
		for (auto child : m_aChildren)
		{
			child->m_pParent = nullptr;
		}
		m_aChildren.clear();
	}

	inline void aeTransform::Translate(const aeVector3 & Translation)
	{
		aeMatrix4 TranslationMatrix = aeMatrix4::TranslationMatrix(Translation);
		m_xGlobalPosition = TranslationMatrix * m_xGlobalPosition;
	}

	inline void aeTransform::Scale(const aeVector3 & Scalation)
	{
		aeMatrix4 ScalationMatrix = aeMatrix4::ScalingMatrix(Scalation);
		m_xGlobalScale = ScalationMatrix * m_xGlobalScale;
	}

	inline void aeTransform::Rotate(const aeVector3 & Rotation)
	{
		m_xGlobalRotation.Rotate(Rotation);
	}

	inline void aeTransform::TranslateLocal(const aeVector3 & Translation)
	{
		aeMatrix4 TranslationMatrix = aeMatrix4::TranslationMatrix(Translation);
		m_xLocalPosition = TranslationMatrix * m_xLocalPosition;
	}

	void aeTransform::ScaleLocal(const aeVector3 & Scalation)
	{
		aeMatrix4 ScalationMatrix = aeMatrix4::ScalingMatrix(Scalation);
		m_xLocalScale = ScalationMatrix * m_xLocalScale;
	}

	inline void aeTransform::RotateLocal(const aeVector3 & Rotation)
	{
		m_xLocalRotation.Rotate(Rotation);
	}

	inline void aeTransform::TranslateTo(const aeVector3 & NewPosition, float Proportion)
	{
		Translate((NewPosition - m_xGlobalPosition)*Proportion);
	}

	inline void aeTransform::ScaleTo(const aeVector3 & NewScale, float Proportion)
	{
		Scale((NewScale - m_xGlobalScale)*Proportion);
	}

	inline void aeTransform::RotateTo(const aeVector3 & NewRotation, float Proportion)
	{
		Rotate((NewRotation - m_xGlobalRotation.GetEulerAngles())*Proportion);
	}

	void aeTransform::RotateAround(const aeVector3 & Position, const aeVector3 & Rotation, float Proportion)
	{
		aeVector3 Temp =m_xGlobalPosition - Position;
		float Distance = Temp.Magnitude();
		Temp = aeMatrix3::RotationMatrix(Rotation* Proportion) * Temp;
		Temp.Normalize();
		m_xGlobalPosition = Temp*Distance;
	}

	inline void aeTransform::LookAt(const aeVector3 & Target)
	{
		m_xGlobalRotation = aeQuaternion(Target, aeVector3{ 0, 1, 0 });
	}

	inline void aeTransform::TranslateForward(float Distance)
	{
		Translate((m_xGlobalRotation.GetMatrix()*aeVector3{ 0, 0, 1}).Normalized()*Distance);
	}

	inline void aeTransform::TranslateSideWays(float Distance)
	{
		Translate(m_xGlobalRotation.GetDirection().Normalized()*Distance);
	}

	inline void aeTransform::RotateView(float roll, float pitch, float yaw)
	{
		m_xGlobalRotation.Rotate(aeVector3(roll, pitch, yaw));
	}

	inline aeMatrix4 aeTransform::GetGlobalMatrix() const
	{
		return aeMatrix4::TransformationMatrix(m_xGlobalRotation,m_xGlobalPosition,m_xGlobalScale);
	}

	inline aeMatrix4 aeTransform::GetLocalMatrix() const
	{
		return aeMatrix4::TransformationMatrix(m_xLocalRotation, m_xLocalPosition, m_xLocalScale);
	}

	inline aeMatrix4 aeTransform::GetRealMatrix() const
	{
		return GetLocalMatrix()*GetGlobalMatrix();
	}

	inline aeMatrix4 aeTransform::GetViewMatrix(aeVector3 WorldUp)
	{
		return  aeMatrix4::LookAtLH(m_xGlobalPosition, m_xGlobalRotation.GetDirection() + m_xGlobalPosition, WorldUp);
	}

	inline aeMatrix4 aeTransform::GetViewMatrix(aeVector3 Target, aeVector3 WorldUp)
	{
		return aeMatrix4::LookAtLH(m_xGlobalPosition, Target, WorldUp);
	}

	inline aeMatrix4 aeTransform::GetProjectionMatrix(float Near, float Far, float FieldOfView, float AspectRatio)
	{
		return aeMatrix4::PerspectiveFOVLH(Near, Far, FieldOfView, AspectRatio);
	}

	inline void aeTransform::SetPosition(const aeVector3 & Position)
	{
		m_xGlobalPosition = Position;
	}

	inline void aeTransform::SetRotation(const aeVector3 & Rotation)
	{
		m_xGlobalRotation = aeQuaternion(Rotation.x,Rotation.y,Rotation.z);
	}

	inline void aeTransform::SetRotation(const aeQuaternion & Rotation)
	{
		m_xGlobalRotation = Rotation;
	}

	inline void aeTransform::SetScale(const aeVector3 & S)
	{
		m_xGlobalScale = S;
	}

	inline void aeTransform::SetLocalPosition(const aeVector3 & Position)
	{
		m_xLocalPosition = Position;
	}

	inline void aeTransform::SetLocalRotation(const aeVector3 & Rotation)
	{
		m_xLocalRotation = aeQuaternion(Rotation.x, Rotation.y, Rotation.z);
	}

	inline void aeTransform::SetLocalRotation(const aeQuaternion & Rotation)
	{
		m_xLocalRotation = Rotation;
	}

	inline void aeTransform::SetLocalScale(const aeVector3 & S)
	{
		m_xLocalScale = S;
	}

	inline aeVector3 aeTransform::GetPosition()
	{
		return m_xGlobalPosition;
	}

	inline aeQuaternion aeTransform::GetRotation()
	{
		return m_xGlobalRotation;
	}

	inline aeVector3 aeTransform::GetEulerRotation()
	{
		return m_xGlobalRotation.GetEulerAngles();
	}

	inline aeVector3 aeTransform::GetScale()
	{
		return m_xGlobalScale;
	}

	inline aeVector3 aeTransform::GetLocalPosition()
	{
		return m_xLocalPosition;
	}

	inline aeQuaternion aeTransform::GetLocalRotation()
	{
		return m_xLocalRotation;
	}

	inline aeVector3 aeTransform::GetLocalEulerRotation()
	{
		return m_xLocalRotation.GetEulerAngles();
	}

	inline aeVector3 aeTransform::GetLocalScale()
	{
		return m_xLocalScale;
	}
}