/*************************************************************************************************/
/* @struct	aeVector3
/*
/* @brief	This structure purpose is to make mathematical operations in a 3 dimensional space.
/*
/* @author	Alvaro Estrada
/* @date	14/05/2016
 /*************************************************************************************************/

#pragma once

namespace aeEngineSDK
{
	struct AE_UTILITY_EXPORT aeVector3
	{
		/*************************************************************************************************/
		/* Variable declaration
		/*************************************************************************************************/
		float x, y, z;

		/*************************************************************************************************/
		/* Constructors
		/*************************************************************************************************/
		aeVector3();
		~aeVector3();

		///Receives another vector and copies its values.
		aeVector3(const aeVector2& V);
		aeVector3(const aeVector2Int& V);
		aeVector3(const aeVector3& V);
		aeVector3(const aeVector4& V);
		///Receives the X, Y and Z values.
		explicit aeVector3(float X, float Y = 0, float Z = 0);

		/*************************************************************************************************/
		/* Declaration of arithmetic operators
		/*************************************************************************************************/
		inline aeVector3 operator*(const aeVector3& V) const
		{
			return aeVector3(x * V.x, y * V.y, z * V.z);
		}

		inline aeVector3 operator+(const aeVector3& V) const
		{
			return aeVector3(x + V.x, y + V.y, z + V.z);
		}

		inline aeVector3 operator-(const aeVector3& V) const
		{
			return aeVector3(x - V.x, y - V.y, z - V.z);
		}

		inline aeVector3 operator/(const aeVector3& V) const
		{
			return aeVector3(x / V.x, y / V.y, z / V.z);
		}

		inline aeVector3 operator*(const float& S) const
		{
			return aeVector3(x * S, y * S, z * S);
		}

		inline aeVector3 operator/(const float& S) const
		{
			return *this*(1.0f / S);
		}

		///Is the same as using the cross3 product function.
		inline aeVector3 operator^(const aeVector3& V) const
		{
			return aeVector3(y*V.z - V.y*z, z*V.x - V.z*x, x*V.y - V.x*y);
		}

		///Is the same as using the normalize function.
		inline aeVector3 operator!() const
		{
			return *this * (1.0f / ~*this);
		}		

		///Is the same as using the distance function.
		inline float operator%(const aeVector3& V) const
		{
			return ~(*this - V);
		}

		///Is the same as using the dot product function.
		inline float operator|(const aeVector3& V) const
		{
			return this->x*V.x + this->y*V.y + this->z*V.z;
		}

		///Is the same as using the magnitude function.
		inline float operator~() const
		{
			return aeMath::Sqrt(x*x + y*y + z*z);
		}

		///It adds up the value of all the variables.
		inline float operator+() const
		{
			return (x + y + z);
		}

		/*************************************************************************************************/
		/* Declaration of logic operators
		/*************************************************************************************************/
		inline bool operator==(const aeVector3& V) const
		{
			return x == V.x && y == V.y && z == V.z;
		}

		inline bool operator!=(const aeVector3& V) const
		{
			return x != V.x || y != V.y || z != V.z;
		}

		inline bool operator<=(const aeVector3& V)  const
		{
			return ~*this <= ~V;
		}

		inline bool operator>=(const aeVector3& V)  const
		{
			return ~*this >= ~V;
		}

		inline bool operator<(const aeVector3& V)  const
		{
			return ~*this < ~V;
		}

		inline bool operator>(const aeVector3& V)  const
		{
			return ~*this > ~V;
		}

		/*************************************************************************************************/
		/* Declaration of compound assignment operators	
		/*************************************************************************************************/
		inline aeVector3& operator+=(const aeVector3& V)
		{
			x += V.x;
			y += V.y;
			z += V.z;
			return *this;
		}

		inline aeVector3& operator-=(const aeVector3& V)
		{
			x -= V.x;
			y -= V.y;
			z -= V.z;
			return *this;
		}

		inline aeVector3& operator*=(const aeVector3& V)
		{
			x *= V.x; 
			y *= V.y;
			z *= V.z;
			return *this;
		}

		inline aeVector3& operator/=(const aeVector3& V)
		{
			x /= V.x; 
			y /= V.y;
			z /= V.z;
			return *this;
		}

		inline aeVector3& operator*=(const float& S)
		{
			x *= S; 
			y *= S;
			z *= S;
			return *this;
		}

		inline aeVector3& operator/=(const float& S)
		{
			float Inv = 1.0f / S;
			x *= Inv;
			y *= Inv;
			z *= Inv;
			return *this;
		}

		/*************************************************************************************************/
		/* Functions declaration                                            												
		/*************************************************************************************************/
	public:
		
		/*************************************************************************************************/
		/* @fn	inline float Distance(const aeVector3& V) const
		/*
		/* @brief	Returns the scalar value of the of the difference between two vectors.
		/*
		/* @param	V	The aeVector3 to process.
		/*
		/* @return	A float.
		/*************************************************************************************************/

		inline float Distance(const aeVector3& V) const
		{
			return *this % V;
		}

		/*************************************************************************************************/
		/* @fn	inline bool CloseEnough(const aeVector3& V, const float& Range) const
		/*
		/* @brief	Evaluates if a point is close enough of another point.
		/*
		/* @param	V	 	The aeVector3 to process.
		/* @param	Range	The range.
		/*
		/* @return	True if it succeeds, false if it fails.
		/*************************************************************************************************/

		inline bool CloseEnough(const aeVector3& V, const float& Range) const
		{///Returns true if the magnitude between vectors is lower than the asked range.
			return *this % V < Range;
		}

		/*************************************************************************************************/
		/* @fn	inline float Magnitude() const
		/*
		/* @brief	Return the scalar value of the vector in form of a floating number.
		/*
		/* @return	A float.
		/*************************************************************************************************/

		inline float Magnitude() const
		{
			return ~*this;
		}

		/*************************************************************************************************/
		/* @fn	inline float Dot(const aeVector3& V) const
		/*
		/* @brief	Returns the dot product between this vector and the input.
		/*
		/* @param	V	The aeVector3 to process.
		/*
		/* @return	A float.
		/*************************************************************************************************/

		inline float Dot(const aeVector3& V) const
		{
			return *this | V;
		}

		/*************************************************************************************************/
		/* @fn	inline aeVector3 Cross(const aeVector3& V) const
		/*
		/* @brief	Returns the cross product between vectors.
		/*
		/* @param	V	The aeVector3 to process.
		/*
		/* @return	An aeVector3.
		/*************************************************************************************************/

		inline aeVector3 Cross(const aeVector3& V) const
		{
			return *this ^ V;
		}

		/*************************************************************************************************/
		/* @fn	float ScalarProjection(const aeVector3& V) const
		/*
		/* @brief	Returns the magnitude of the shadow left by another vector on top of this vector.
		/*
		/* @param	V	The aeVector3 to process.
		/*
		/* @return	A float.
		/*************************************************************************************************/

		inline float ScalarProjection(const aeVector3& V) const
		{
			return (*this | V) / ~*this;
		}

		/*************************************************************************************************/
		/* @fn	inline void Normalize()
		/*
		/* @brief	Normalizes this object.
		/*************************************************************************************************/

		inline void Normalize()
		{
			*this = !*this;
		}

		/*************************************************************************************************/
		/* @fn	inline aeVector3 Normalized() const
		/*
		/* @brief	Gets the normalized version of this vector.
		/*
		/* @return	An aeVector3.
		/*************************************************************************************************/

		inline aeVector3 Normalized()
		{
			return !*this;
		}

		/*************************************************************************************************/
		/* @fn	aeVector3 VectorProjection(const aeVector3& V) const;
		/*
		/* @brief	Returns the shadow left by another vector on top of this vector.
		/*
		/* @param	V	The aeVector3 to process.
		/*
		/* @return	An aeVector3.
		/*************************************************************************************************/

		inline aeVector3 VectorProjection(const aeVector3& V) const
		{///The vector projection of A on B is a vector whose magnitude is the scalar projection of A on B and whose angle against B.
			return !*this *  this->ScalarProjection(V);
		}

		/*************************************************************************************************/
		/* @fn	float AngleBetweenVectors(const aeVector3& V) const;
		/*
		/* @brief	Returns the angle between vectors.
		/*
		/* @param	V	The aeVector3 to process.
		/*
		/* @return	A float.
		/*************************************************************************************************/

		float AngleBetweenVectors(const aeVector3& V) const;

		/*************************************************************************************************/
		/* @fn	void OrthoNormalize(aeVector3& V);
		/*
		/* @brief	Ortho normalizes both vectors.
		/*
		/* @param [in,out]	V	The aeVector3 to process.
		/*************************************************************************************************/

		void OrthoNormalize(aeVector3& V);

	};
}