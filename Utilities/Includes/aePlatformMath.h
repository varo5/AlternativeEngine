/*************************************************************************************************/
/* @file	aePlatformMath.h
/*
/* @brief	Declares the platform mathematics class.
/*************************************************************************************************/

#pragma once
#include "aeStdHeaders.h"

namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* @class	aePlatformMath
	/*
	/* @brief	A mathematics class with static functions and constants.
	/*************************************************************************************************/

	class AE_UTILITY_EXPORT aePlatformMath
	{
	public:
		/*************************************************************************************************/
		/* Common use math constants
		/*************************************************************************************************/
		static const float SMALL_NUMBER;			/// "Small number" definition
		static const float KIND_OF_SMALL_NUMBER;	/// "Kinda small number" definition
		static const float BIG_NUMBER;			/// "Big number" definition 
		static const float KIND_OF_BIG_NUMBER;		/// "Kinda big number" definition

		static const float EULER;				/// Euler–Mascheroni constant 
		static const float INV_EULER;			/// Euler–Mascheroni constant 

		static const float PI;					/// PI constant 
		static const float INV_PI;				/// Inverse of PI (1/PI) constant 
		static const float ONE_QUARTER_PI;			/// One quarter PI constant 
		static const float THREE_QUARTER_PI;			/// Three quarter PI constant 
		static const float HALF_PI;				/// Half PI constant 
		static const float TWICE_PI;				/// Twice PI constant 

		static const float MAX_FLOAT;			/// Max value of a float
		static const float MIN_FLOAT;			/// Min value of a float
		static const float LOW_FLOAT;			/// Lowest value of a float

		static const float FLOAT_DELTA;				/// Magic number used for math precision 
		static const float FLOAT_EPSILON;				/// Epsilon constant
		static const float FLOAT_NAN;
		static const float FLOAT_INFINITY;
		static const float FLOAT_ROUND_ERROR;
		static const float FLOAT_DENORM_MIN;

		static const double MAX_DOUBLE;			/// Max value of a double
		static const double MIN_DOUBLE;			/// Min value of a double
		static const double LOW_DOUBLE;			/// Lowest value of a double

		static const double DOUBLE_DELTA;				/// Magic number used for math precision 
		static const double DOUBLE_EPSILON;				/// Epsilon constant
		static const double DOUBLE_NAN;
		static const double DOUBLE_INFINITY;
		static const double DOUBLE_ROUND_ERROR;
		static const double DOUBLE_DENORM_MIN;

		/*************************************************************************************************/
		/* Common use math functions
		/*************************************************************************************************/
		template <typename T>
		static inline bool CloseEnough(const T& A, const T& B, const float& F = FLOAT_DELTA)
		{
			return Abs(A - B) <= F;
		}

		template <typename T>
		static inline float Percentage(const T& A, const T& B)
		{
			return (A != (T)0) ? Abs(B / A) : 0;
		}
		
		template <typename T>
		static inline T Trunc(const T& Value)
		{
			return (T)((int32)Value);
		}

		template <typename T>
		static inline T Floor(const T& Value)
		{
			return (T)floorf((float)Value);
		}

		template <typename T>
		static inline T Round(const T& Value)
		{
			return (T)Floor(((float)F) + 0.5f);
		}

		template <typename T>
		static inline T Ceil(const T& Value)
		{
			return Trunc((T)ceilf((float)F));
		}

		template <typename T>
		static inline float Fractional(const T& Value)
		{
			float f = (float)Value;
			return f - Trunc(f);
		}
		
		template <typename T>
		static inline T Exp(const T& Value)
		{
			return (T)expf((float)Value);
		}

		template <typename T>
		static inline T Loge(const T& Value)
		{
			return (T)logf((float)Value);
		}

		template <typename T>
		static inline T Log10(const T& Value)
		{
			return (T)log10f((float)Value);
		}

		template <typename T>
		static inline T LogX(const T& Base, const T& Value)
		{
			return Loge(Value) / Loge(Base);
		}

		template <typename T>
		static inline float Modf(const T& X, const T& Y)
		{
			return fmodf((float)X, (float)Y);
		}

		template <typename T>
		static inline int32 Mod(const T& X, const T& Y)
		{
			return ((int32)X) % ((int32)Y);
		}

		template <typename T>
		static inline T Sqrt(const T& Value)
		{
			return (T)sqrtf((float)Value);
		}

		template <typename T>
		static inline T InvSqrt(const T& Value)
		{
			return (T)(1.0f / sqrtf((float)Value));
		}

		template <typename T>
		static inline T FastInvSqrt(const T& Value)
		{
			return InvSqrt(Value);
		}

		template <typename T>
		static inline T Pow(const T& A, const T& B)
		{
			return (T)powf((float)A, (float)B);
		}		

		template <typename T>
		static inline T Min(const T& a, const T& b)
		{
			return a < b ? a : b;
		}

		template <typename T>
		static inline T Max(const T& a, const T& b)
		{
			return a > b ? a : b;
		}

		template <typename T>
		static inline T Min3(const T& a, const T& b, const T& c)
		{
			return Min(a,Min(b,c));
		}

		template <typename T>
		static inline T Max3(const T& a, const T& b, const T& c)
		{
			return  Max(a, Max(b, c));
		}
		
		template <typename T>
		static inline T Lerp(const T& a, const T& b, const float& t)
		{
			return (T)(a + (b - a)* Clamp<float>(t,0,1));
		}

		template <typename T>
		static inline T Slerp(const T& a, const T& b, const float& t)
		{
			return (T)((a*Sin((1.0f-t)) + b*t));
		}

		template <typename T>
		static inline T Clamp(const T& a, const T& lower, const T& higher)
		{
			return Max(Min(a, higher), lower);
		}
		
		template <typename T>
		static inline bool Sign(const T& Value)
		{
			return ((int32)Value) > -1;
		}

		template <typename T>
		static inline T Abs(const T& Value)
		{
			return (T)fabs((float)Value);
		}

		template <typename T>
		static inline T FastAbs(const T& Value)
		{
			float f = (float)Value;
			return (((*(uint32*)&f) >= (uint32)0x80000000)) ? -Value : Value;
		}

		/*************************************************************************************************/
		/* Trigonometric functions
		/*************************************************************************************************/
		static inline float Sin(const float& Value)
		{
			return sinf(Value);
		}

		static inline float ArcSin(const float& Value)
		{
			return asinf((Value < -1.f) ? -1.f : ((Value < 1.f) ? Value : 1.f));
		}

		static inline float Cos(const float& Value)
		{
			return cosf(Value);
		}

		static inline float ArcCos(const float& Value)
		{
			return acosf((Value < -1.f) ? -1.f : ((Value < 1.f) ? Value : 1.f));
		}

		static inline float Tan(const float& Value)
		{
			return tanf(Value);
		}

		static inline float ArcTan(const float& Value)
		{
			return atanf(Value);
		}

		static inline float ArcTan2(const float& Y, const float& X)
		{
			return atan2f(Y, X);
		}

		/*************************************************************************************************/
		/* Fast math functions using Taylor series
		/*************************************************************************************************/
		static float FastSin(const float& Value);	///For minus infinity to infinity
		static float FastCos(const float& Value);	///For minus infinity to infinity
		static float FastTan(const float& Value);	///For minus infinity to infinity
		static float FastCot(const float& Value);	///For minus one to one
		static float FastSec(const float& Value);	///For minus one to one
		static float FastCsc(const float& Value);	///For minus one to one

		static float FastArcSin(const float& Value);	///For minus one to one
		static float FastArcCos(const float& Value);	///For minus one to one
		static float FastArcTan(const float& Value);	///For minus one to one

		static float FastArcTan2(const float& Y, const float& X);

		/*************************************************************************************************/
		/* Value checking functions
		/*************************************************************************************************/
		static inline bool IsNaN(const float& Value)
		{
			return ((*(uint32*)&Value) & 0x7FFFFFFF) > 0x7F800000;
		}

		static inline bool IsFinite(const float& Value)
		{
			return ((*(uint32*)&Value) & 0x7F800000) != 0x7F800000;
		}

		static inline bool IsNegativeFloat(const float& Value)
		{
			return ((*(uint32*)&Value) >= (uint32)0x80000000);
		}
	};
}



