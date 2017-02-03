#pragma once

namespace aeEngineSDK
{
	struct AE_UTILITY_EXPORT aePlane : public aeVector3
	{
		/*************************************************************************************************/
		/* Variable declaration
		/*************************************************************************************************/
	public:
		float d;

		/*************************************************************************************************/
		/* Constructors declaration
		/*************************************************************************************************/
	public:
		aePlane();
		~aePlane();

		aePlane(const aePlane& P);
		///Receives another vector and copies its values.
		aePlane(const aeVector3 & V);
		///Receives the X, Y and Z values.
		aePlane(float X, float Y = 0, float Z = 0, float D = 0);
		aePlane(const aeVector3 & A, const aeVector3 & B, const aeVector3 & C);

	public:

		/*************************************************************************************************/
		/* @fn	void Transform(const aeVector3& Rotation, const aeVector3& Translation);
		/*
		/* @brief	Transforms the plane.
		/*
		/* @param	Rotation   	The rotation in Euler terms.
		/* @param	Translation	The translation.
		/*************************************************************************************************/

		void Transform(const aeVector3& Rotation, const aeVector3& Translation);

		/*************************************************************************************************/
		/* @fn	void Transform(const aeQuaternion& Rotation, const aeVector3& Translation);
		/*
		/* @brief	Transforms.
		/*
		/* @param	Rotation   	The rotation.
		/* @param	Translation	The translation.
		/*************************************************************************************************/

		void Transform(const aeQuaternion& Rotation, const aeVector3& Translation);

		/*************************************************************************************************/
		/* @fn	void Transform(const aeMatrix3& Rotation, const aeVector3& Translation);
		/*
		/* @brief	Transforms.
		/*
		/* @param	Rotation   	The rotation.
		/* @param	Translation	The translation.
		/*************************************************************************************************/

		void Transform(const aeMatrix3& Rotation, const aeVector3& Translation);

		/*************************************************************************************************/
		/* @fn	void Transform(const aeMatrix4& Transformation);
		/*
		/* @brief	Transforms the given transformation.
		/*
		/* @param	Transformation	The transformation.
		/*************************************************************************************************/

		void Transform(const aeMatrix4& Transformation);

		/*************************************************************************************************/
		/* @fn	bool IsInFront(const aeVector3& Point);
		/*
		/* @brief	Query if 'Point' is in front.
		/*
		/* @param	Point	The point.
		/*
		/* @return	True if in front, false if not.
		/*************************************************************************************************/

		bool IsInFront(const aeVector3& Point);
	};
}
