/**********************************************************************************************//**
* @struct	aeVector2
*
* @brief	This structure purpose is to make mathematical operations in a 2 dimensional space.
*
* @author	Alvaro Estrada
* @date	14/05/2016
**************************************************************************************************/
#pragma once

namespace aeEngineSDK
{	
	struct AE_UTILITY_EXPORT aeVector2
	{
		/*************************************************************************************************/
		/* Constant definitions
		/*************************************************************************************************/
		static const aeVector2 ZERO;

		/*************************************************************************************************/
		/* Variable declaration	
		/*************************************************************************************************/
		float x, y;

		/*************************************************************************************************/
		/* Constructors declaration 
		/*************************************************************************************************/
		aeVector2();
		~aeVector2();

		///Receives another vector and copies its values.
		aeVector2(const aeVector2& V);
		aeVector2(const aeVector2Int& V);
		aeVector2(const aeVector3& V);
		aeVector2(const aeVector4& V);
		///Receives the X and Y values.
		explicit aeVector2(float X, float Y = 0);

		/*************************************************************************************************/
		/* Declaration of arithmetic operators
		/*************************************************************************************************/
		inline aeVector2 operator*(const aeVector2& V) const
		{
			return aeVector2(x * V.x, y * V.y);
		}

		inline aeVector2 operator+(const aeVector2& V) const
		{
			return aeVector2(x + V.x, y + V.y);
		}

		inline aeVector2 operator-(const aeVector2& V) const
		{
			return aeVector2(x - V.x, y - V.y);
		}

		inline aeVector2 operator/(const aeVector2& V) const
		{
			return aeVector2(x / V.x, y / V.y);
		}

		inline aeVector2 operator*(const float& S) const
		{
			return aeVector2(x * S, y * S);
		}

		inline aeVector2 operator/(const float& S) const
		{
			return *this*(1.0f / S);
		}

		///Is the same as using the normalize function.
		inline aeVector2 operator!() const
		{
			return *this * (1.0f / ~*this);
		}

		///Is the same as using the dot product function.
		inline float operator|(const aeVector2& V) const
		{
			return x*V.x + y*V.y;
		}

		///Is the same as using the cross product function.
		inline float operator^(const aeVector2& V) const
		{
			return (x*V.y) - (y*V.x);
		}
		
		///Is the same as using the distance function.
		inline float operator%(const aeVector2& V) const
		{
			return ~(*this - V);
		}

		///Is the same as using the magnitude function.
		inline float operator~() const
		{
			return aeMath::Sqrt(x*x + y*y);
		}

		///It adds up the value of all the variables.
		inline float operator+() const
		{
			return (x + y);
		}
		/*************************************************************************************************/
		/* Declaration of compound assignment operators
		/*************************************************************************************************/
		inline aeVector2& operator+=(const aeVector2& V)
		{
			x += V.x;
			y += V.y;
			return *this;
		}

		inline aeVector2& operator-=(const aeVector2& V)
		{
			x -= V.x;
			y -= V.y;
			return *this;
		}

		inline aeVector2& operator*=(const aeVector2& V)
		{
			x *= V.x;
			y *= V.y;
			return *this;
		}

		inline aeVector2& operator/=(const aeVector2& V)
		{
			x /= V.x;
			y /= V.y;
			return *this;
		}

		inline aeVector2& operator*=(const float& S)
		{
			x *= S;
			y *= S;
			return *this;
		}

		inline aeVector2& operator/=(const float& S)
		{
			float Inv = 1.0f / S;
			x *= Inv;
			y *= Inv;
			return *this;
		}

		/*************************************************************************************************/
		/* Declaration of logic operators
		/*************************************************************************************************/
		inline bool operator==(const aeVector2& V)  const
		{
			return x == V.x && y == V.y;
		}

		inline bool operator!=(const aeVector2& V)  const
		{
			return x != V.x || y != V.y;
		}

		inline bool operator<=(const aeVector2& V)  const
		{
			return ~*this <= ~V;
		}

		inline bool operator>=(const aeVector2& V)  const
		{
			return ~*this >= ~V;
		}

		inline bool operator<(const aeVector2& V)  const
		{
			return ~*this < ~V;
		}

		inline bool operator>(const aeVector2& V)  const
		{
			return ~*this > ~V;
		}

		/*************************************************************************************************/
		/* Functions declaration
		/*************************************************************************************************/
	public:
		/*************************************************************************************************/
		/* @fn	inline float Cross(const aeVector2& V)
		/*
		/* @brief	Returns the value of the resulting vector that is perpendicular to both entries, with a direction given by the
		/* right - hand rule and a magnitude equal to the area of the parallelogram that the vectors span.
		/*
		/* @param	V	The aeVector2 to process.
		/*
		/* @return	A float.
		/*************************************************************************************************/

		inline float Cross(const aeVector2& V) const
		{///The cross product is the value of the resulting vector that is perpendicular to both entries, with a direction given by the right - hand rule and a magnitude equal to the area of the parallelogram that the vectors span.
			return *this ^ V;
		}

		/*************************************************************************************************/
		/* @fn	inline bool CloseEnough(const aeVector2& V, const float& Range)
		/*
		/* @brief	Evaluates if a point is close enough of another point.
		/*
		/* @param	V	 	The aeVector2 to process.
		/* @param	Range	The range.
		/*
		/* @return	true if it succeeds, false if it fails.
		/*************************************************************************************************/

		inline bool CloseEnough(const aeVector2& V, const float& Range) const
		{///Returns true if the magnitude between vectors is lower than the asked range.
			return *this % V < Range;
		}
		/*************************************************************************************************/
		/* @fn	inline float Magnitude()
		/*
		/* @brief	Returns the scalar value of the vector in form of a floating number.
		/*
		/* @return	A float.
		/*************************************************************************************************/

		inline float Magnitude() const
		{///The magnitude of the vector is the length of the vector, it is obtained by the square root of the addition of the squared values of x and y.
			return ~*this;
		}

		/*************************************************************************************************/
		/* @fn	inline float Distance(const aeVector2& V)
		/*
		/* @brief	Returns the scalar value of the of the difference between two vectors.
		/*
		/* @param	V	The aeVector2 to process.
		/*
		/* @return	A float.
		/*************************************************************************************************/

		inline float Distance(const aeVector2& V) const
		{
			return *this % V;
		}

		/*************************************************************************************************/
		/* @fn	inline float Dot(const aeVector2& V)
		/*
		/* @brief	Returns the sum of the products of the corresponding entries.
		/*
		/* @param	V	The aeVector2 to process.
		/*
		/* @return	A float.
		/*************************************************************************************************/

		inline float Dot(const aeVector2& V) const
		{///The dot product is the result of the sum of the products of the corresponding entries of the two sequences of numbers.
			return *this | V;
		}		

		/*************************************************************************************************/
		/* @fn	inline aeVector2 Normalize()
		/*
		/* @brief	Returns the direction of this vector.
		/*
		/* @return	An aeVector2.
		/*************************************************************************************************/

		inline void Normalize()
		{///The normalized vector is a vector in the same direction but with a magnitude equals to one
			*this = !*this;
		}

		/*************************************************************************************************/
		/* @fn	inline aeVector2 Normalized()
		/*
		/* @brief	Gets the normalized.
		/*
		/* @return	An aeVector2.
		/*************************************************************************************************/

		inline aeVector2 Normalized()
		{///The normalized vector is a vector in the same direction but with a magnitude equals to one
			return !*this;
		}

		/*************************************************************************************************/
		/* @fn	inline aeVector2 VectorProjection(const aeVector2& V) const
		/*
		/* @brief	Returns the shadow left by another vector on top of this vector.
		/*
		/* @param	V	The aeVector2 to process.
		/*
		/* @return	An aeVector2.
		/*************************************************************************************************/

		inline aeVector2 VectorProjection(const aeVector2& V) const
		{///The vector projection of A on B is a vector whose magnitude is the scalar projection of A on B and whose angle against B.
			return !*this *  this->ScalarProjection(V);
		}

		/*************************************************************************************************/
		/* @fn	float AngleBetweenVectors(const aeVector2& A, const aeVector2& B);
		/*
		/* @brief	Returns the angle between vectors in rads.
		/*
		/* @param	A	The aeVector2 to process.
		/* @param	B	The aeVector2 to process.
		/*
		/* @return	A float.
		/*************************************************************************************************/

		float AngleBetweenVectors(const aeVector2& V) const;

		/*************************************************************************************************/
		/* @fn	float ScalarProjection(const aeVector2& A, const aeVector2& B);
		/*
		/* @brief	Returns the magnitude of the shadow left by another vector on top of this vector.
		/*
		/* @param	A	The aeVector2 to process.
		/* @param	B	The aeVector2 to process.
		/*
		/* @return	A float.
		/*************************************************************************************************/

		inline float ScalarProjection(const aeVector2& V) const
		{///The scalar projection is a scalar, equal to the length of the orthogonal projection of A on B, with a negative sign if the projection has an opposite direction with respect to B.
			return (*this | V) / ~*this;
		}
	};
}
