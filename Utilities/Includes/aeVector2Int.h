#pragma once

namespace aeEngineSDK
{
	struct AE_UTILITY_EXPORT aeVector2Int
	{
		/*************************************************************************************************/
		/* Constant definitions
		/*************************************************************************************************/
		static const aeVector2Int ZERO;

		/*************************************************************************************************/
		/* Variable declaration
		/*************************************************************************************************/
		int32 x, y;

		/*************************************************************************************************/
		/* Constructors declaration
		/*************************************************************************************************/
		aeVector2Int();
		~aeVector2Int();

		///Receives another vector and copies its values.
		aeVector2Int(const aeVector2& V);
		aeVector2Int(const aeVector2Int& V);
		aeVector2Int(const aeVector3& V);
		aeVector2Int(const aeVector4& V);
		///Receives the X and Y values.
		explicit aeVector2Int(int32 X, int32 Y = 0);

		/*************************************************************************************************/
		/* Declaration of arithmetic operators
		/*************************************************************************************************/
		inline aeVector2Int operator*(const aeVector2Int& V) const
		{
			return aeVector2Int(x * V.x, y * V.y);
		}

		inline aeVector2Int operator+(const aeVector2Int& V) const
		{
			return aeVector2Int(x + V.x, y + V.y);
		}

		inline aeVector2Int operator-(const aeVector2Int& V) const
		{
			return aeVector2Int(x - V.x, y - V.y);
		}

		inline aeVector2Int operator/(const aeVector2Int& V) const
		{
			return aeVector2Int(x / V.x, y / V.y);
		}

		inline aeVector2Int operator*(const int32& S) const
		{
			return aeVector2Int(x * S, y * S);
		}

		inline aeVector2Int operator/(const int32& S) const
		{
			float f = 1.0f / S;
			return aeVector2Int((int32)(x * f), (int32)(y * f));
		}

		///Is the same as using the dot product function.
		inline int32 operator|(const aeVector2Int& V) const
		{
			return x*V.x + y*V.y;
		}

		///Is the same as using the distance function.
		inline int32 operator%(const aeVector2Int& V) const
		{
			return ~(*this - V);
		}

		///Is the same as using the magnitude function.
		inline int32 operator~() const
		{
			return aeMath::Sqrt(x*x + y*y);
		}

		///It adds up the value of all the variables.
		inline int32 operator+() const
		{
			return (x + y);
		}
		/*************************************************************************************************/
		/* Declaration of compound assignment operators
		/*************************************************************************************************/
		inline aeVector2Int& operator+=(const aeVector2Int& V)
		{
			x += V.x;
			y += V.y;
			return *this;
		}

		inline aeVector2Int& operator-=(const aeVector2Int& V)
		{
			x -= V.x;
			y -= V.y;
			return *this;
		}

		inline aeVector2Int& operator*=(const aeVector2Int& V)
		{
			x *= V.x;
			y *= V.y;
			return *this;
		}

		inline aeVector2Int& operator/=(const aeVector2Int& V)
		{
			x /= V.x;
			y /= V.y;
			return *this;
		}

		inline aeVector2Int& operator*=(const int32& S)
		{
			x *= S;
			y *= S;
			return *this;
		}

		inline aeVector2Int& operator/=(const int32& S)
		{
			float Inv = 1.0f / S;
			x = (int32)(Inv * x);
			y = (int32)(Inv * y);
			return *this;
		}

		/*************************************************************************************************/
		/* Declaration of logic operators
		/*************************************************************************************************/
		inline bool operator==(const aeVector2Int& V)  const
		{
			return x == V.x && y == V.y;
		}

		inline bool operator!=(const aeVector2Int& V)  const
		{
			return x != V.x || y != V.y;
		}

		inline bool operator<=(const aeVector2Int& V)  const
		{
			return ~*this <= ~V;
		}

		inline bool operator>=(const aeVector2Int& V)  const
		{
			return ~*this >= ~V;
		}

		inline bool operator<(const aeVector2Int& V)  const
		{
			return ~*this < ~V;
		}

		inline bool operator>(const aeVector2Int& V)  const
		{
			return ~*this > ~V;
		}

		/*************************************************************************************************/
		/* Functions declaration
		/*************************************************************************************************/
	public:

		/*************************************************************************************************/
		/* @fn	inline int32 Magnitude()
		/*
		/* @brief	Returns the scalar value of the vector in form of a int32ing number.
		/*
		/* @return	A int32.
		/*************************************************************************************************/

		inline int32 Magnitude() const
		{///The magnitude of the vector is the length of the vector, it is obtained by the square root of the addition of the squared values of x and y.
			return ~*this;
		}

		/*************************************************************************************************/
		/* @fn	inline int32 Distance(const aeVector2Int& V)
		/*
		/* @brief	Returns the scalar value of the of the difference between two vectors.
		/*
		/* @param	V	The aeVector2Int to process.
		/*
		/* @return	A int32.
		/*************************************************************************************************/

		inline int32 Distance(const aeVector2Int& V) const
		{
			return *this % V;
		}

		/*************************************************************************************************/
		/* @fn	inline int32 Dot(const aeVector2Int& V)
		/*
		/* @brief	Returns the sum of the products of the corresponding entries.
		/*
		/* @param	V	The aeVector2Int to process.
		/*
		/* @return	A int32.
		/*************************************************************************************************/

		inline int32 Dot(const aeVector2Int& V) const
		{///The dot product is the result of the sum of the products of the corresponding entries of the two sequences of numbers.
			return *this | V;
		}
	};
}