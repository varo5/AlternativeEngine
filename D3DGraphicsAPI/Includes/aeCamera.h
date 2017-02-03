#pragma once
#include <aeMath.h>
#include "aeFrustum.h"

namespace aeEngineSDK
{
	struct AE_GRAPHICS_EXPORT aeWorldMatrices
	{
		aeMatrix4 World;
		aeMatrix4 View;
		aeMatrix4 Projection;
	};

	/*************************************************************************************************/
	/* @class	aeCamera
	/*
	/* @brief	A camera.
	/*************************************************************************************************/

	class AE_GRAPHICS_EXPORT aeCamera
	{
	public:
		aeCamera();
		aeCamera(const aeCamera& C);
		~aeCamera();
	private:
		aeWorldMatrices m_xWorldMatrices;

		aeVector3 m_xPosition;
		aeQuaternion m_xDirection;
		aeFrustum m_xFrustum;

		aeConstantBuffer* m_pCB;
	public:
		aeVector3 GetPosition();
		aeQuaternion GetDirection();

		aeMatrix4 GetWorld();
		aeMatrix4 GetView();
		aeMatrix4 GetProjection();	

		void SetPosition(aeVector3 NewPosition);
		void SetDirection(aeVector3 NewDirection);
		void SetDirection(float Roll, float Pitch, float Yaw);
	public:

		/*************************************************************************************************/
		/* @fn	void aeCamera::Roll(float Theta, float Speed);
		/*
		/* @brief	Rolls.
		/*
		/* @param	Theta	The theta.
		/* @param	Speed	The speed.
		/*************************************************************************************************/

		void Roll(float Theta, float Speed);

		/*************************************************************************************************/
		/* @fn	void aeCamera::Pitch(float Theta, float Speed);
		/*
		/* @brief	Pitches.
		/*
		/* @param	Theta	The theta.
		/* @param	Speed	The speed.
		/*************************************************************************************************/

		void Pitch(float Theta, float Speed);

		/*************************************************************************************************/
		/* @fn	void aeCamera::Yaw(float Theta, float Speed);
		/*
		/* @brief	Yaws.
		/*
		/* @param	Theta	The theta.
		/* @param	Speed	The speed.
		/*************************************************************************************************/

		void Yaw(float Theta, float Speed);

		/*************************************************************************************************/
		/* @fn	void aeCamera::Pan(aeVector3 NewPosition);
		/*
		/* @brief	Pans the given new position.
		/*
		/* @param	NewPosition	The new position.
		/*************************************************************************************************/

		void Pan(aeVector3 NewPosition, float Speed);

		/*************************************************************************************************/
		/* @fn	void aeCamera::Rotate(aeVector3 NewDirection);
		/*
		/* @brief	Rotates the given new direction.
		/*
		/* @param	NewDirection	The new direction in Euler space.
		/*************************************************************************************************/

		void Rotate(aeVector3 NewDirection, float Speed);

		/*************************************************************************************************/
		/* @fn	void aeCamera::Orbit(aeVector3 LookAt, aeVector3 RotationDirection, float Distance, float Speed);
		/*
		/* @brief	Orbits.
		/*
		/* @param	LookAt			 	The look at.
		/* @param	RotationDirection	The rotation direction.
		/* @param	Distance		 	The distance.
		/* @param	Speed			 	The speed.
		/*************************************************************************************************/

		void Orbit(aeVector3 LookAt, aeVector3 RotationDirection, float Distance, float Speed);

	public:

		/*************************************************************************************************/
		/* @fn	void aeCamera::SetWorld(aeMatrix4 & World);
		/*
		/* @brief	Sets a world.
		/*
		/* @param [in,out]	World	The world.
		/*************************************************************************************************/

		void SetWorld(const aeMatrix4 & World);

		/*************************************************************************************************/
		/* @fn	void aeCamera::SetProjectionMatrix(aeVector4 ProjectionValues);
		/*
		/* @brief	Sets projection matrix.
		/*
		/* @param	ProjectionValues	The projection values: near, far, field of view and aspect ratio.
		/*************************************************************************************************/

		void SetProjectionMatrix(const aeVector4 & ProjectionValues);

		/*************************************************************************************************/
		/* @fn	void aeCamera::SetProjectionMatrix(const float & Near, const float & Far, const float & FOV, const float & AspecRatio);
		/*
		/* @brief	Sets projection matrix.
		/*
		/* @param	Near	  	The near.
		/* @param	Far		  	The far.
		/* @param	FOV		  	The fov.
		/* @param	AspecRatio	The aspect ratio.
		/*************************************************************************************************/

		void SetProjectionMatrix(const float & Near, const float & Far, const float & FOV, const float & AspectRatio);

		/*************************************************************************************************/
		/* @fn	void aeCamera::SetViewMatrix(aeVector3 Position, aeVector4);
		/*
		/* @brief	Sets view matrix.
		/*
		/* @param	Position  	The position.
		/* @param	parameter2	The second parameter.
		/*************************************************************************************************/

		void SetViewMatrix(aeVector3 Position, aeVector3 LookAt);

	public:

		/*************************************************************************************************/
		/* @fn	void aeCamera::Init();
		/*
		/* @brief	S this object.
		/*************************************************************************************************/

		void Init();

		/*************************************************************************************************/
		/* @fn	void aeCamera::Release();
		/*
		/* @brief	Releases this object.
		/*************************************************************************************************/

		void Release();

		/*************************************************************************************************/
		/* @fn	void aeCamera::Render();
		/*
		/* @brief	Renders this object.
		/*************************************************************************************************/

		void Render();
	};
}