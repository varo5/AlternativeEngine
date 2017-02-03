/*************************************************************************************************/
/* @struct	aeMatrix3
/*
/* @brief	This structure is a 3x3 matrix of float values.
/*
/* @author	Alvaro Estrada
/* @date	14 / 05 / 2016
/*************************************************************************************************/

#pragma once

namespace aeEngineSDK
{
	struct AE_UTILITY_EXPORT aeMatrix3
	{
		/*************************************************************************************************/
		/* Variable declaration
		/*************************************************************************************************/
		/// Is the union between individual values and their array and matrix form.
		union {
			/// A structure meant to save the matrix as individual values.
			struct {
				float f00, f01, f02;
				float f10, f11, f12;
				float f20, f21, f22;
			};
			/// A structure meant to save the matrix as 4D vectors.
			aeVector3 v3[3];
			/// A 9 times float array.
			float v[9];
			/// A 3x3 float array
			float m[3][3];
		};

		/*************************************************************************************************/
		/* Constructors
		/*************************************************************************************************/
		aeMatrix3();
		~aeMatrix3();
		///Create a copy of another 2x2 matrix.
		aeMatrix3(const aeMatrix3& M);
		aeMatrix3(const aeMatrix4& M);
		aeMatrix3(
			const aeVector3& V0,
			const aeVector3& V1,
			const aeVector3& V2);
		///Create a new Matrix from given values.
		aeMatrix3(
			float _00, float _01 = 0, float _02 = 0,
			float _10 = 0, float _11 = 1, float _12 = 0,
			float _20 = 0, float _21 = 0, float _22 = 1);

		/*************************************************************************************************/
		/* Vectors inside the matrix related functions.
		/*************************************************************************************************/
		void SetCol(const aeVector3& V, const uint8& nCol);
		void SetRow(const aeVector3& V, const uint8& nRow);
		aeVector3 GetCol(const uint8& nCol) const;
		aeVector3 GetRow(const uint8& nRow) const;

		/*************************************************************************************************/
		/* Declaration of arithmetic operators.
		/*************************************************************************************************/
		aeMatrix3 operator+(const aeMatrix3& M) const;
		aeMatrix3 operator-(const aeMatrix3& M) const;
		aeMatrix3 operator*(const aeMatrix3& M) const;
		aeMatrix3 operator*(const float& S) const;
		aeMatrix3 operator/(const float& S)const;
		aeVector3 operator*(const aeVector3& V) const;
		///Is the same as using the inverse function.
		inline aeMatrix3 operator!() const
		{
			return Inverse();
		}
		///Is the same as using the transpose function.
		inline aeMatrix3 operator~() const
		{
			return Transpose();
		}
		///Is the same as using the det function.
		inline float operator+() const
		{
			return Det();
		}

		/*************************************************************************************************/
		/* Declaration of compound assignment operators.
		/*************************************************************************************************/
	public:
		inline aeMatrix3& operator+=(const aeMatrix3& M)
		{
			return *this = *this + M;
		}

		inline aeMatrix3& operator-=(const aeMatrix3& M)
		{
			return *this = *this - M;
		}

		inline aeMatrix3& operator*=(const aeMatrix3& M)
		{
			return *this = *this*M;
		}

		inline aeMatrix3& operator*=(const float& S)
		{
			return *this = *this * S;
		}

		inline aeMatrix3& operator/=(const float& S)
		{
			return *this = *this / S;
		}

		/*************************************************************************************************/
		/* Functions declaration.
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
		/* @fn	aeVector3 Cramer(const aeVector3& V) const;
		/*
		/* @brief	Uses Cramer's rule for the solution of an equation system.
		/*
		/* @param	V	The aeVector3 to process.
		/*
		/* @return	An aeVector3.
		/*************************************************************************************************/

		aeVector3 Cramer(const aeVector3& V) const;

		/*************************************************************************************************/
		/* @fn	inline aeMatrix3 Transpose() const
		/*
		/* @brief	Transposes the given matrix.
		/*
		/* @return	An aeMatrix3.
		/*************************************************************************************************/

		inline aeMatrix3 Transpose() const
		{
			return aeMatrix3(
				f00, f10, f20,
				f01, f11, f21,
				f02, f12, f22);
		}

		/*************************************************************************************************/
		/* @fn	aeMatrix3 Cofactor() const;
		/*
		/* @brief	Cofactors the given matrix.
		/*
		/* @return	An aeMatrix3.
		/*************************************************************************************************/

		aeMatrix3 Cofactor() const;

		/*************************************************************************************************/
		/* @fn	inline aeMatrix3 Adjunct() const
		/*
		/* @brief	Adjuncts the given matrix.
		/*
		/* @return	An aeMatrix3.
		/*************************************************************************************************/

		inline aeMatrix3 Adjunct() const
		{
			return ~Cofactor();
		}

		/*************************************************************************************************/
		/* @fn	aeMatrix3 Inverse() const;
		/*
		/* @brief	Inverses the given matrix.
		/*
		/* @return	An aeMatrix3.
		/*************************************************************************************************/

		aeMatrix3 Inverse() const;
		
		/*************************************************************************************************/
		/* @fn	static aeMatrix3 RotationX(const float& theta);
		/*
		/* @brief	Creates a rotation matrix from an angle to rotate on the X axis.
		/*
		/* @param	theta	The theta.
		/*
		/* @return	An aeMatrix3.
		/*************************************************************************************************/

		static aeMatrix3 RotationX(const float& theta);

		/*************************************************************************************************/
		/* @fn	static aeMatrix3 RotationY(const float& theta);
		/*
		/* @brief	Creates a rotation matrix from an angle to rotate on the Y axis.
		/*
		/* @param	theta	The theta.
		/*
		/* @return	An aeMatrix3.
		/*************************************************************************************************/

		static aeMatrix3 RotationY(const float& theta);

		/*************************************************************************************************/
		/* @fn	static aeMatrix3 RotationZ(const float& theta);
		/*
		/* @brief	Creates a rotation matrix from an angle to rotate on the Z axis.
		/*
		/* @param	theta	The theta.
		/*
		/* @return	An aeMatrix3.
		/*************************************************************************************************/

		static aeMatrix3 RotationZ(const float& theta);

		/*************************************************************************************************/
		/* @fn	static aeMatrix4 RotationMatrix(const aeVector3& V);
		/*
		/* @brief	Creates a rotation matrix from a vector.
		/*
		/* @param	V	The aeVector3 to process.
		/*
		/* @return	An aeMatrix4.
		/*************************************************************************************************/

		static aeMatrix3 RotationMatrix(const aeVector3& V);

		/*************************************************************************************************/
		/* @fn	static aeMatrix3 Zero();
		/*
		/* @brief	Gets an empty matrix.
		/*
		/* @return	An aeMatrix3.
		/*************************************************************************************************/

		static aeMatrix3 Zero();

		/*************************************************************************************************/
		/* @fn	static aeMatrix3 Identity();
		/*
		/* @brief	Gets the identity matrix.
		/*
		/* @return	An aeMatrix3.
		/*************************************************************************************************/

		static aeMatrix3 Identity();
	};
}



