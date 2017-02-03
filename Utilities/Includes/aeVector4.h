/*************************************************************************************************/
/* @struct	aeVector4
/*
/* @brief	This structure purpose is to make mathematical operations in a 4 dimensional space.
/*
/* @author	Alvaro Estrada
/* @date	14 / 05 / 2016
/*************************************************************************************************/

#pragma once

namespace aeEngineSDK
{
	struct AE_UTILITY_EXPORT aeVector4
	{
		/*************************************************************************************************/
		/* Constant definitions
		/*************************************************************************************************/
		static const aeVector4 ZERO;

		/*************************************************************************************************/
		/* Variable declaration
		/*************************************************************************************************/
		/// Is the union between X,Y and Z values and a 3D array.
		union
		{
			/// A structure meant to save the array as individual values.
			struct
			{
				float x, y, z, w;
			};
			/// A 4D float array.
			float v[4];
			QWord Q;
		};

		/*************************************************************************************************/
		/* Constructors
		/*************************************************************************************************/
		aeVector4();
		~aeVector4();
		///Receives another vector and copies its values.
		aeVector4(const aeVector2& V);
		aeVector4(const aeVector2Int& V);
		aeVector4(const aeVector3& V);
		aeVector4(const aeVector4& V);
		///Receives the X, Y, Z and W values.
		explicit aeVector4(float X, float Y = 0, float Z = 0, float W = 0);

		/*************************************************************************************************/
		/* Declaration of arithmetic operators
		/*************************************************************************************************/
		inline aeVector4 operator+(const aeVector4& V) const
		{
			return aeVector4(x + V.x, y + V.y, z + V.z, w + V.w);
		}

		inline aeVector4 operator-(const aeVector4& V) const
		{
			return aeVector4::aeVector4(x - V.x, y - V.y, z - V.z, w - V.w);
		}

		inline aeVector4 operator/(const aeVector4& V) const
		{
			return aeVector4(x / V.x, y / V.y, z / V.z, w / V.w);
		}

		inline aeVector4 operator*(const aeVector4& V) const
		{
			return aeVector4(x * V.x, y * V.y, z * V.z, w * V.w);
		}

		inline aeVector4 operator*(const float& S) const
		{
			return aeVector4(x * S, y * S, z * S, w * S);
		}

		inline aeVector4 operator/(const float& S) const
		{
			return *this*(1.0f / S);
		}

		///Is the same as using the cross3 product function.
		inline aeVector4 operator^(const aeVector4& V) const
		{
			return aeVector4(y*V.z - V.y*z, z*V.x - V.z*x, x*V.y - V.x*y, 0);
		}

		///Is the same as using the normalize function.
		inline aeVector4 operator!() const
		{
			return *this * (1.0f / ~*this);
		}

		///Is the same as using the dot product function.
		inline float operator|(const aeVector4& V) const
		{
			return x*V.x + y*V.y + z*V.z + w*V.w;
		}

		///Is the same as using the distance function.
		inline float operator%(const aeVector4& V) const
		{
			return ~(*this - V);
		}

		///Is the same as using the magnitude function.
		inline float operator~() const
		{
			return aeMath::Sqrt(x*x + y*y + z*z + w*w);
		}

		///It adds up the value of all the variables.
		inline float operator+() const
		{
			return (x+y+z+w);
		}

		/*************************************************************************************************/
		/* Declaration of compound assignment operators
		/*************************************************************************************************/
		inline aeVector4& operator+=(const aeVector4& V)
		{
			x += V.x;
			y += V.y;
			z += V.z;
			w += V.w;
			return *this;
		}

		inline aeVector4& operator-=(const aeVector4& V)
		{
			x -= V.x;
			y -= V.y;
			z -= V.z;
			w -= V.w;
			return *this;
		}

		inline aeVector4& operator*=(const aeVector4& V)
		{
			x *= V.x;
			y *= V.y;
			z *= V.z;
			w *= V.w;
			return *this;
		}

		inline aeVector4& operator/=(const aeVector4& V)
		{
			x /= V.x;
			y /= V.y;
			z /= V.z;
			w /= V.w;
			return *this;
		}

		inline aeVector4& operator*=(const float& S)
		{
			x *= S;
			y *= S;
			z *= S;
			w *= S;
			return *this;
		}

		inline aeVector4& operator/=(const float& S)
		{
			float Inv = 1.0f / S;
			x *= Inv;
			y *= Inv;
			z *= Inv;
			w *= Inv;
			return *this;
		}

		/*************************************************************************************************/
		/* Declaration of logic operators
		/*************************************************************************************************/
		inline bool operator==(const aeVector4& V) const
		{
			return (x == V.x &&	y == V.y && z == V.z && w == V.w);
		}

		inline bool operator!=(const aeVector4& V) const
		{
			return (x != V.x || y != V.y || z != V.z || w != V.w);
		}

		inline bool operator<=(const aeVector4& V)  const
		{
			return ~*this <= ~V;
		}

		inline bool operator>=(const aeVector4& V)  const
		{
			return ~*this >= ~V;
		}

		inline bool operator<(const aeVector4& V)  const
		{
			return ~*this < ~V;
		}

		inline bool operator>(const aeVector4& V)  const
		{
			return ~*this > ~V;
		}
		/*************************************************************************************************/
		/* Static functions declaration
		/*************************************************************************************************/
	public:

		/*************************************************************************************************/
		/* @fn	inline float Distance(const aeVector4& V) const
		/*
		/* @brief	Returns the scalar value of the of the difference between two vectors.
		/*
		/* @param	V	The aeVector4 to process.
		/*
		/* @return	A float.
		/*************************************************************************************************/

		inline float Distance(const aeVector4& V) const
		{
			return *this % V;
		}

		/*************************************************************************************************/
		/* @fn	inline bool CloseEnough(const aeVector4& V, const float& Range) const
		/*
		/* @brief	Evaluates if a point is close enough of another point.
		/*
		/* @param	V	 	The aeVector4 to process.
		/* @param	Range	The range.
		/*
		/* @return	True if it succeeds, false if it fails.
		/*************************************************************************************************/

		inline bool CloseEnough(const aeVector4& V, const float& Range) const
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
		/* @fn	inline float Dot(const aeVector4& V) const
		/*
		/* @brief	Returns the dot product between this vector and the input.
		/*
		/* @param	V	The aeVector4 to process.
		/*
		/* @return	A float.
		/*************************************************************************************************/

		inline float Dot(const aeVector4& V) const
		{
			return *this | V;
		}

		/*************************************************************************************************/
		/* @fn	inline aeVector4 Cross(const aeVector4& V) const
		/*
		/* @brief	Returns the cross product between vectors as they were 2D.
		/*
		/* @param	V	The aeVector4 to process.
		/*
		/* @return	An aeVector4.
		/*************************************************************************************************/

		inline aeVector4 Cross(const aeVector4& V) const
		{
			return *this ^ V;
		}

		/*************************************************************************************************/
		/* @fn	inline float ScalarProjection(const aeVector4& V) const
		/*
		/* @brief	Returns the magnitude of the shadow left by another vector on top of this vector.
		/*
		/* @param	V	The aeVector4 to process.
		/*
		/* @return	A float.
		/*************************************************************************************************/

		inline float ScalarProjection(const aeVector4& V) const
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
			*this = *this * (1.0f / ~*this);
		}

		/*************************************************************************************************/
		/* @fn	inline aeVector4 Normalized()
		/*
		/* @brief	Gets the normalized.
		/*
		/* @return	An aeVector4.
		/*************************************************************************************************/

		inline aeVector4 Normalized()
		{
			return *this * (1.0f / ~*this);
		}

		/*************************************************************************************************/
		/* @fn	inline aeVector4 VectorProjection(const aeVector4& V) const
		/*
		/* @brief	Returns the shadow left by another vector on top of this vector.
		/*
		/* @param	V	The aeVector4 to process.
		/*
		/* @return	An aeVector4.
		/*************************************************************************************************/

		inline aeVector4 VectorProjection(const aeVector4& V) const
		{///The vector projection of A on B is a vector whose magnitude is the scalar projection of A on B and whose angle against B.
			return !*this *  this->ScalarProjection(V);
		}

		/*************************************************************************************************/
		/* @fn	float AngleBetweenVectors(const aeVector4& V) const;
		/*
		/* @brief	Returns the angle between vectors.
		/*
		/* @param	V	The aeVector4 to process.
		/*
		/* @return	A float.
		/*************************************************************************************************/

		float AngleBetweenVectors(const aeVector4& V) const;
	};
}

