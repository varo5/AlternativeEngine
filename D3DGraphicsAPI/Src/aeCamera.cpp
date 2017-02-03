#include "aeGraphicsAPI.h"

namespace aeEngineSDK
{
	aeCamera::aeCamera()
	{
	}

	aeCamera::aeCamera(const aeCamera & C)
	{
		*this = C;
	}

	aeCamera::~aeCamera()
	{
	}

	inline void aeCamera::Pan(aeVector3 NewPosition, float Speed)
	{
		m_xPosition += NewPosition*Speed;
	}

	inline void aeCamera::Rotate(aeVector3 NewDirection, float Speed)
	{
		aeVector3 v = m_xDirection.GetEulerAngles();
		v += NewDirection*Speed;
		m_xDirection = aeQuaternion(v.x,v.y,v.z);
	}

	void aeCamera::Orbit(aeVector3 LookAt, aeVector3 RotationDirection, float Distance, float Speed)
	{
	}

	inline void aeCamera::SetWorld(const aeMatrix4 & World)
	{
		m_xWorldMatrices.World = World;
	}

	inline void aeCamera::SetProjectionMatrix(const aeVector4 & ProjectionValues)
	{
		m_xWorldMatrices.Projection = aeMatrix4::PerspectiveFOVLH(ProjectionValues.x, ProjectionValues.y, ProjectionValues.z, ProjectionValues.w).Transpose();
		m_xFrustum = aeFrustum(ProjectionValues.x, ProjectionValues.y, ProjectionValues.z);
		m_xFrustum.UpdateFrustum(m_xDirection, m_xPosition);
	}

	inline void aeCamera::SetProjectionMatrix(const float & Near, const float & Far, const float & FOV, const float & AspectRatio)
	{
		m_xWorldMatrices.Projection = aeMatrix4::PerspectiveFOVLH(Near, Far, FOV, AspectRatio).Transpose();
		m_xFrustum = aeFrustum(Near, Far, FOV);
		m_xFrustum.UpdateFrustum(m_xDirection, m_xPosition);
	}

	void aeCamera::SetViewMatrix(aeVector3 Position, aeVector3 LookAt)
	{
		m_xPosition = Position;
		m_xDirection = aeQuaternion((LookAt - Position).Normalized());
		m_xWorldMatrices.View = aeMatrix4::LookAtLH(Position, LookAt).Transpose();
		m_xFrustum.UpdateFrustum(m_xDirection, m_xPosition);
	}

	void aeCamera::Init()
	{
		AEG_BUFFER_DESC ConstBuffer = { 0 };
		ConstBuffer.BindFlags = AEG_BIND_CONSTANT_BUFFER;
		ConstBuffer.ByteWidth = (sizeof(aeVector4) + 15) & 0xfffffff0; //sizeof(aeVector3);
		ConstBuffer.CPUAccessFlags = AEG_CPU_ACCESS_WRITE;
		ConstBuffer.Usage = AEG_USAGE_DYNAMIC;
		ConstBuffer.MiscFlags = 0;
		ConstBuffer.StructureByteStride = 0;

		m_pCB = aeGraphicsAPI::Instance().CreateConstantBuffer(&ConstBuffer);
	}

	void aeCamera::Release()
	{
		SAFE_RELEASE(m_pCB);
	}

	void aeCamera::Render()
	{
		void* pData = aeRenderer::Instance().MapConstantBuffer(m_pCB);
		aeVector4* pPosition = (aeVector4*)pData;
		*pPosition = aeVector4{ m_xPosition.x,m_xPosition.y,m_xPosition.z };
		aeRenderer::Instance().UnMapConstantBuffer(m_pCB);

		aeRenderer::Instance().SetVertexShaderConstantBuffer(1, 1, m_pCB, aeRenderer::Instance().GetVertexShader());
	}

	inline aeVector3 aeCamera::GetPosition()
	{
		return m_xPosition;
	}

	inline aeQuaternion aeCamera::GetDirection()
	{
		return m_xDirection;
	}

	inline aeMatrix4 aeCamera::GetWorld()
	{
		return m_xWorldMatrices.World;
	}

	inline aeMatrix4 aeCamera::GetView()
	{
		return m_xWorldMatrices.View;
	}

	inline aeMatrix4 aeCamera::GetProjection()
	{
		return m_xWorldMatrices.Projection;
	}

	void aeCamera::SetPosition(aeVector3 NewPosition)
	{
		m_xPosition = NewPosition;

		m_xWorldMatrices.View = aeMatrix4::LookAtLH(NewPosition, (m_xDirection * aeVector3(0,0,1)).Normalized()).Transpose();
		m_xFrustum.UpdateFrustum(m_xDirection, m_xPosition);
	}

	void aeCamera::SetDirection(aeVector3 NewDirection)
	{
		m_xDirection = aeQuaternion(NewDirection.Normalized());

		m_xWorldMatrices.View = aeMatrix4::LookAtLH(m_xPosition, (m_xDirection * aeVector3(0, 0, 1)).Normalized()).Transpose();
		m_xFrustum.UpdateFrustum(m_xDirection, m_xPosition);
	}

	inline void aeCamera::SetDirection(float Roll, float Pitch, float Yaw)
	{
		m_xDirection = aeQuaternion(Roll, Pitch, Yaw);
	}

	void aeCamera::Roll(float Theta, float Speed)
	{
		aeVector3 euler = m_xDirection.GetEulerAngles();

		euler.x += Theta*Speed;

		m_xDirection = aeQuaternion(euler.x, euler.y, euler.z);
	}

	void aeCamera::Pitch(float Theta, float Speed)
	{
		aeVector3 euler = m_xDirection.GetEulerAngles();

		euler.y += Theta*Speed;

		m_xDirection = aeQuaternion(euler.x, euler.y, euler.z);
	}

	void aeCamera::Yaw(float Theta, float Speed)
	{
		aeVector3 euler = m_xDirection.GetEulerAngles();

		euler.z += Theta*Speed;

		m_xDirection = aeQuaternion(euler.x, euler.y, euler.z);
	}

}
