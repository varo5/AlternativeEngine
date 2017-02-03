#pragma once

namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* Forward declarations needed
	/*************************************************************************************************/
	struct aeVector3;
	struct aeMatrix3;

	/*************************************************************************************************/
	/* @struct	aeQuaternion
	/*
	/* @brief	A quaternion.
	/*************************************************************************************************/

	struct AE_UTILITY_EXPORT aeQuaternion
	{
		/*************************************************************************************************/
		/* Variables
		/*************************************************************************************************/
	public:
		float x, y, z, w;

		/*************************************************************************************************/
		/* Constructors
		/*************************************************************************************************/
	public:		
		aeQuaternion() : w(1.0f), x(), y(), z() {}
		aeQuaternion(float x, float y, float z, float w)
			: w(w), x(x), y(y), z(z)
		{
		}
		~aeQuaternion();

		aeQuaternion(const aeQuaternion& Q);

		/*************************************************************************************************/
		/* @fn	aeQuaternion(float RotX, float RotY, float RotZ);
		/*
		/* @brief	Construct from Euler angles 
		/*
		/* @param	RotX	The pitch angle.
		/* @param	RotY	The yaw angle.
		/* @param	RotZ	The roll angle.
		/*************************************************************************************************/

		aeQuaternion(float RotX, float RotY, float RotZ);

		/*************************************************************************************************/
		/* @fn	aeQuaternion(aeVector3 Axis, float Angle);
		/*
		/* @brief	Construct from an axis-angle pair 
		/*
		/* @param	Axis 	The axis.
		/* @param	Angle	The angle.
		/*************************************************************************************************/

		aeQuaternion(const aeVector3& Axis, float Angle);

		/*************************************************************************************************/
		/* @fn	aeQuaternion(const aeVector3& LookAt, aeVector3 Up = aeVector3
		/*
		/* @brief	Constructor.
		/*
		/* @param	LookAt	The look at.
		/*************************************************************************************************/

		aeQuaternion(const aeVector3& LookAt, aeVector3 Up);

		/*************************************************************************************************/
		/* @fn	explicit aeQuaternion(aeVector3 Normalized);
		/*
		/* @brief	Construct from a normalized quaternion stored in a vec3 
		/*
		/* @param	Normalized	The normalized.
		/*************************************************************************************************/

		explicit aeQuaternion(aeVector3 Normalized);


		/*************************************************************************************************/
		/* Boolean operations
		/*************************************************************************************************/
	public:
		bool operator== (const aeQuaternion& o) const;
		bool operator!= (const aeQuaternion& o) const;

		bool Equal(const aeQuaternion& o, float epsilon = aeMath::FLOAT_EPSILON) const;

	public:
		aeQuaternion operator+ (const aeQuaternion& Q);
		aeQuaternion operator- (const aeQuaternion& Q);
		aeQuaternion operator* (const aeQuaternion& Q);
		aeQuaternion operator/ (const aeQuaternion& Q);
		aeQuaternion operator* (const float& F);
		aeVector3 operator* (const aeVector3& V);	

	public:
		aeQuaternion& operator+= (const aeQuaternion& Q);
		aeQuaternion& operator-= (const aeQuaternion& Q);
		aeQuaternion& operator*= (const aeQuaternion& Q);
		aeQuaternion& operator/= (const aeQuaternion& Q);
		aeQuaternion& operator*= (const float& F);

		/*************************************************************************************************/
		/* Functions
		/*************************************************************************************************/
	public:
		/*************************************************************************************************/
		/* @fn	aeMatrix3 GetMatrix() const;
		/*
		/* @brief	Returns a matrix representation of the quaternion
		/*
		/* @return	The matrix.
		/*************************************************************************************************/

		aeMatrix3 GetMatrix() const;

		/*************************************************************************************************/
		/* @fn	aeMatrix3 GetTransposedMatrix() const;
		/*
		/* @brief	Gets transposed matrix.
		/*
		/* @return	The transposed matrix.
		/*************************************************************************************************/

		aeMatrix3 GetTransposedMatrix() const;

		/*************************************************************************************************/
		/* @fn	aeVector3 GetEulerAngles() const;
		/*
		/* @brief	Returns the Euler angles.
		/*
		/* @return	The Euler angles.
		/*************************************************************************************************/

		aeVector3 GetEulerAngles() const;

		/*************************************************************************************************/
		/* @fn	float Norm();
		/*
		/* @brief	Gets the norm.
		/*
		/* @return	A float.
		/*************************************************************************************************/

		float Norm() const;

		/*************************************************************************************************/
		/* @fn	float Magnitude();
		/*
		/* @brief	Gets the magnitude.
		/*
		/* @return	A float.
		/*************************************************************************************************/

		float Magnitude();

		/*************************************************************************************************/
		/* @fn	void Normalize();
		/*
		/* @brief	Normalizes this object.
		/*************************************************************************************************/

		void Normalize();

		/*************************************************************************************************/
		/* @fn	aeQuaternion Normalized();
		/*
		/* @brief	Returns a copy of the normalized quaternion.
		/*
		/* @return	An aeQuaternion.
		/*************************************************************************************************/

		aeQuaternion Normalized();

		/*************************************************************************************************/
		/* @fn	aeQuaternion Scale(float s);
		/*
		/* @brief	Scales.
		/*
		/* @param	s	The float to process.
		/*
		/* @return	An aeQuaternion.
		/*************************************************************************************************/

		aeQuaternion Scale(float s) const;

		/*************************************************************************************************/
		/* @fn	aeQuaternion Inverse();
		/*
		/* @brief	Gets the inverse.
		/*
		/* @return	An aeQuaternion.
		/*************************************************************************************************/

		aeQuaternion Inverse() const;

		/*************************************************************************************************/
		/* @fn	void Conjugate();
		/*
		/* @brief	Conjugates this object.
		/*************************************************************************************************/

		void Conjugate();

		/*************************************************************************************************/
		/* @fn	aeQuaternion Conjugate();
		/*
		/* @brief	Returns a copy of the quaternion conjugate.
		/*
		/* @return	An aeQuaternion.
		/*************************************************************************************************/

		aeQuaternion Conjugated() const;

		/*************************************************************************************************/
		/* @fn	aeVector3 Rotate(const aeVector3& in);
		/*
		/* @brief	Rotate a point by this quaternion
		/*
		/* @param	in	The vector rotate.
		/*
		/* @return	An aeVector3.
		/*************************************************************************************************/

		aeVector3 Rotate(const aeVector3& in);

		/*************************************************************************************************/
		/* @fn	aeVector3 GetDirection();
		/*
		/* @brief	Gets the direction.
		/*
		/* @return	The direction.
		/*************************************************************************************************/

		aeVector3 GetDirection();

	public:

		/*************************************************************************************************/
		/* @fn	static void Interpolate(aeQuaternion& pOut, const aeQuaternion& pStart, const aeQuaternion& pEnd, float pFactor);
		/*
		/* @brief	Performs a spherical interpolation between two quaternions and writes the result into
		/* 			the third.
		/*
		/* @param [in,out]	pOut	Target object to received the interpolated rotation.
		/* @param	pStart			Start rotation of the interpolation at factor == 0.
		/* @param	pEnd			End rotation, factor == 1.
		/* @param	pFactor			Interpolation factor between 0 and 1. Values outside of this range
		/* 							yield undefined results.
		/*************************************************************************************************/

		static void Interpolate(aeQuaternion& pOut, const aeQuaternion& pStart,
			const aeQuaternion& pEnd, float pFactor);
	};
}
