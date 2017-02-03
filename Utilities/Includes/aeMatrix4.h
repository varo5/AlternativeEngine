/*************************************************************************************************/
/*  @struct	aeMatrix4
/*
/* @brief	This structure is a 4x4 matrix of float values.
/*
/* @author	Alvaro Estrada
/* @date	14/05/2016
/*************************************************************************************************/

#pragma once

namespace aeEngineSDK
{
	struct AE_UTILITY_EXPORT aeMatrix4
	{
		/*************************************************************************************************/
		/* Variable declaration
		/*************************************************************************************************/
		/// Is the union between individual values and their array and matrix form.
		union {
			/// A structure meant to save the matrix as individual values.
			struct
			{
				float f00, f01, f02, f03;
				float f10, f11, f12, f13;
				float f20, f21, f22, f23;
				float f30, f31, f32, f33;
			};
			/// A structure meant to save the matrix as 4D vectors.
			aeVector4 v4[4];
			/// A 4x4 float array
			float m[4][4];
			/// A 16 times float array.
			float v[16];
			/// A 128-bit storage.
			QWord Q;
		};

		/*************************************************************************************************/
		/* Constructors
		/*************************************************************************************************/
		aeMatrix4();
		aeMatrix4(const aeMatrix3& M);
		aeMatrix4(const aeMatrix4& M);
		aeMatrix4(
			const aeVector4& V0, 
			const aeVector4& V1, 
			const aeVector4& V2, 
			const aeVector4& V3);
		aeMatrix4(
			float _00, float _01 = 0, float _02 = 0, float _03 = 0,
			float _10 = 0, float _11 = 1, float _12 = 0, float _13 = 0,
			float _20 = 0, float _21 = 0, float _22 = 1, float _23 = 0,
			float _30 = 0, float _31 = 0, float _32 = 0, float _33 = 1);
		~aeMatrix4();

		/*************************************************************************************************/
		/* Vectors inside the matrix related functions.
		/*************************************************************************************************/
		void SetCol(const aeVector4& V, const uint8& nCol);
		void SetRow(const aeVector4& V, const uint8& nRow);
		aeVector4 GetCol(const uint8& nCol) const;
		aeVector4 GetRow(const uint8& nRow) const;

		/*************************************************************************************************/
		/* Implementation of arithmetic operators
		/*************************************************************************************************/
		aeMatrix4 operator+(const aeMatrix4& M) const;
		aeMatrix4 operator-(const aeMatrix4& M) const;
		aeMatrix4 operator*(const aeMatrix4& M) const;
		aeMatrix4 operator*(const float& S) const;
		aeMatrix4 operator/(const float& S) const;
		aeVector4 operator*(const aeVector4& V) const;
		///Is the same as using the inverse function.
		inline aeMatrix4 operator!() const
		{
			return Inverse();
		}
		///Is the same as using the transpose function.
		inline aeMatrix4 operator~() const
		{
			return Transpose();
		}
		///Is the same as using the det function.
		inline float operator+() const
		{
			return Det();
		}

		/*************************************************************************************************/
		/* Implementation of compound assignment operators
		/*************************************************************************************************/
		inline aeMatrix4& operator+=(const aeMatrix4& M)
		{
			return *this = *this + M;
		}

		inline aeMatrix4& operator-=(const aeMatrix4& M)
		{
			return *this = *this - M;
		}

		inline aeMatrix4& operator*=(const aeMatrix4& M)
		{
			return *this = *this*M;
		}

		inline aeMatrix4& operator*=(const float& S)
		{
			return *this = *this * S;
		}

		inline aeMatrix4& operator/=(const float& S)
		{
			return *this = *this / S;
		}

		/*************************************************************************************************/
		/* Functions declaration
		/*************************************************************************************************/
	public:
		/*************************************************************************************************/
		/* @fn	float Det() const;
		/*
		/* @brief	Obtains the determinant of the given matrix.
		/*
		/* @return	A float.
		/*************************************************************************************************/

		float Det() const;

		/*************************************************************************************************/
		/* @fn	aeVector4 Cramer(const aeVector4& V) const;
		/*
		/* @brief	Uses Cramer's rule for the solution of an equation system.
		/*
		/* @param	V	The aeVector4 to process.
		/*
		/* @return	An aeVector4.
		/*************************************************************************************************/

		aeVector4 Cramer(const aeVector4& V) const;

		/*************************************************************************************************/
		/* @fn	inline aeMatrix4 Transpose() const
		/*
		/* @brief	Obtains the transposed matrix of the given matrix.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		inline aeMatrix4 Transpose() const
		{
			return aeMatrix4(
				f00, f10, f20, f30,
				f01, f11, f21, f31,
				f02, f12, f22, f32,
				f03, f13, f23, f33);
		}

		/*************************************************************************************************/
		/* @fn	aeMatrix4 Cofactor() const;
		/*
		/* @brief	Obtains the cofactor matrix of the given matrix.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		aeMatrix4 Cofactor() const;

		/*************************************************************************************************/
		/* @fn	inline aeMatrix4 Adjunct() const
		/*
		/* @brief	Obtains the adjunct matrix of the given matrix.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		inline aeMatrix4 Adjunct() const
		{
			return ~Cofactor();
		}

		/*************************************************************************************************/
		/* @fn	aeMatrix4 Inverse() const;
		/*
		/* @brief	Obtains the inverse matrix of the given matrix.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		aeMatrix4 Inverse() const;

		/*************************************************************************************************/
		/* @fn	static aeMatrix4 TranslationMatrix(const aeVector3& V);
		/*
		/* @brief	Creates a translation matrix from a vector.
		/*
		/* @param	V	The aeVector3 to process.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		static aeMatrix4 TranslationMatrix(const aeVector3& V);

		/*************************************************************************************************/
		/* @fn	static inline aeMatrix4 TranslationMatrix(const float& x, const float& y, const float& z)
		/*
		/* @brief	Creates a translation matrix from 3 parameters.
		/*
		/* @param	x	The x coordinate.
		/* @param	y	The y coordinate.
		/* @param	z	The z coordinate.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		static aeMatrix4 TranslationMatrix(const float& x, const float& y, const float& z);

		/*************************************************************************************************/
		/* @fn	static inline aeMatrix4 ScalingMatrix(const float& ScaleFactor)
		/*
		/* @brief	Creates a scaling matrix from a scale factor.
		/*
		/* @param	ScaleFactor	The scale factor.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		static aeMatrix4 ScalingMatrix(const float& ScaleFactor);

		/*************************************************************************************************/
		/* @fn	static inline aeMatrix4 ScalingMatrix(const float& x, const float& y, const float& z)
		/*
		/* @brief	Creates a scaling matrix from 3 scale factors.
		/*
		/* @param	x	The x coordinate.
		/* @param	y	The y coordinate.
		/* @param	z	The z coordinate.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		static aeMatrix4 ScalingMatrix(const float& x, const float& y, const float& z);

		/*************************************************************************************************/
		/* @fn	static aeMatrix4 ScalingMatrix(const aeVector3& V);
		/*
		/* @brief	Creates a scaling matrix from a vector.
		/*
		/* @param	V	The aeVector3 to process.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		static aeMatrix4 ScalingMatrix(const aeVector3& V);

		/*************************************************************************************************/
		/* @fn	static aeMatrix4 RotationX(const float& theta);
		/*
		/* @brief	Creates a rotation matrix from an angle to rotate on the X axis.
		/*
		/* @param	theta	The theta.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		static aeMatrix4 RotationX(const float& theta);

		/*************************************************************************************************/
		/* @fn	static aeMatrix4 RotationY(const float& theta);
		/*
		/* @brief	Creates a rotation matrix from an angle to rotate on the Y axis.
		/*
		/* @param	theta	The theta.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		static aeMatrix4 RotationY(const float& theta);

		/*************************************************************************************************/
		/* @fn	static aeMatrix4 RotationZ(const float& theta);
		/*
		/* @brief	Creates a rotation matrix from an angle to rotate on the Z axis.
		/*
		/* @param	theta	The theta.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		static aeMatrix4 RotationZ(const float& theta);

		/*************************************************************************************************/
		/* @fn	static aeMatrix4 RotationMatrix(const aeVector3& V);
		/*
		/* @brief	Creates a rotation matrix from a vector.
		/*
		/* @param	V	The aeVector3 to process.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		static aeMatrix4 RotationMatrix(const aeVector3& V);

		/*************************************************************************************************/
		/* @fn	static aeMatrix4 RotationMatrix(float roll, float pitch, float yaw);
		/*
		/* @brief	Matrix rotation yaw pitch roll.
		/*
		/* @param	roll 	The roll.
		/* @param	pitch	The pitch.
		/* @param	yaw  	The yaw.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		static aeMatrix4 RotationMatrix(float roll, float pitch, float yaw);

		/*************************************************************************************************/
		/* @fn	static aeMatrix4 LookAtLH(aeVector3& EyePos, aeVector3& Target, aeVector3& Up = aeVector3
		/*
		/* @brief	Uses the left hand algorithm to build the view matrix.
		/*
		/* @param [in,out]	EyePos	The eye position.
		/* @param [in,out]	Target	Target for the.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		static aeMatrix4 LookAtLH(aeVector3& EyePos, aeVector3& Target, aeVector3& Up = aeVector3{ 0,1,0 });

		/*************************************************************************************************/
		/* @fn	static aeMatrix4 PerspectiveFOVLH(float zNear, float zFar, float FOV, float AspectRatio = 1.0f);
		/*
		/* @brief	Perspective fovlh.
		/*
		/* @param	zNear	   	The near.
		/* @param	zFar	   	The far.
		/* @param	FOV		   	The fov.
		/* @param	AspectRatio	The aspect ratio.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		static aeMatrix4 PerspectiveFOVLH(float zNear, float zFar, float FOV, float AspectRatio = 1.0f);

		/*************************************************************************************************/
		/* @fn	static aeMatrix4 MatrixOrthoLH(float w, float h, float zNear, float zFar);
		/*
		/* @brief	Matrix ortho lh.
		/*
		/* @param	w	 	The width.
		/* @param	h	 	The height.
		/* @param	zNear	The near.
		/* @param	zFar 	The far.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		static aeMatrix4 MatrixOrthoLH(float w, float h, float zNear, float zFar);

		/*************************************************************************************************/
		/* @fn	static aeMatrix4 TransformationMatrix(const aeQuaternion& Rotation, const aeVector3& Translation, const aeVector3& Scale);
		/*
		/* @brief	Transformation matrix.
		/*
		/* @param	Rotation   	The rotation.
		/* @param	Translation	The translation.
		/* @param	Scale	   	The scale.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		static aeMatrix4 TransformationMatrix(const aeQuaternion& Rotation, const aeVector3& Translation, const aeVector3& Scale);

		/*************************************************************************************************/
		/* @fn	static aeMatrix4 TransformationMatrix(const aeVector3& Rotation, const aeVector3& Translation, const aeVector3& Scale);
		/*
		/* @brief	Transformation matrix.
		/*
		/* @param	Rotation   	The rotation.
		/* @param	Translation	The translation.
		/* @param	Scale	   	The scale.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		static aeMatrix4 TransformationMatrix(const aeVector3& Rotation, const aeVector3& Translation, const aeVector3& Scale);
		

		/*************************************************************************************************/
		/* @fn	static aeMatrix4 Zero();
		/*
		/* @brief	Gets an empty matrix.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		static aeMatrix4 Zero();

		/*************************************************************************************************/
		/* @fn	static aeMatrix4 Identity();
		/*
		/* @brief	Gets the identity matrix.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		static aeMatrix4 Identity();
	};
}