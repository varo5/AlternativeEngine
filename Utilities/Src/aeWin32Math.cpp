#include "aeWin32Math.h"
#include "aePrerequisitesUtil.h"

namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* Common use math constants
	/*************************************************************************************************/
	const float aeWin32Math::SMALL_NUMBER = 1.e-8f;										/// "Small number" definition 
	const float aeWin32Math::KIND_OF_SMALL_NUMBER = 1.e-4f;								/// "Kinda small number" definition
	const float aeWin32Math::BIG_NUMBER = 3.4e+38f;										/// "Big number" definition 
	const float aeWin32Math::KIND_OF_BIG_NUMBER = 3.4e+19f;								/// "Kinda big number" definition

	const float aeWin32Math::EULER = aeWin32Math::Exp(1.0f);							/// Euler–Mascheroni constant
	const float aeWin32Math::INV_EULER = 1.0f / aeWin32Math::Exp(1.0f);					/// Inverse Euler–Mascheroni constant

	const float aeWin32Math::PI = aeWin32Math::ArcTan(1.0f) * 4.0f;						/// PI constant 
	const float aeWin32Math::INV_PI = 0.25f / (aeWin32Math::ArcTan(1.0f));				/// Inverse of PI (1/PI) 
	const float aeWin32Math::ONE_QUARTER_PI = aeWin32Math::ArcTan(1.0f);				/// One quarter PI 
	const float aeWin32Math::THREE_QUARTER_PI = aeWin32Math::ArcTan(1.0f)*3.0f;			/// Three quarter PI 
	const float aeWin32Math::HALF_PI = aeWin32Math::ArcTan(1.0f) * 2.0f;				/// Half PI 
	const float aeWin32Math::TWICE_PI = aeWin32Math::ArcTan(1.0f) * 8.0f;				/// Twice PI	

	const float aeWin32Math::MAX_FLOAT = NumericLimits<float>::max();					/// Max value of a float
	const float aeWin32Math::MIN_FLOAT = NumericLimits<float>::min();					/// Min value of a float
	const float aeWin32Math::LOW_FLOAT = NumericLimits<float>::lowest();				/// Lowest value of a float

	const float aeWin32Math::FLOAT_DELTA = 0.00001f;									/// Magic number used for math precision 
	const float aeWin32Math::FLOAT_EPSILON = NumericLimits<float>::epsilon();
	const float aeWin32Math::FLOAT_NAN = NumericLimits<float>::quiet_NaN();
	const float aeWin32Math::FLOAT_INFINITY = NumericLimits<float>::infinity();
	const float aeWin32Math::FLOAT_ROUND_ERROR = NumericLimits<float>::round_error();
	const float aeWin32Math::FLOAT_DENORM_MIN = NumericLimits<float>::denorm_min();

	const double aeWin32Math::MAX_DOUBLE = NumericLimits<double>::max();				/// Max value of a double
	const double aeWin32Math::MIN_DOUBLE = NumericLimits<double>::min();				/// Min value of a double
	const double aeWin32Math::LOW_DOUBLE = NumericLimits<double>::lowest();				/// Lowest value of a double

	const double aeWin32Math::DOUBLE_DELTA = 0.00001;									/// Magic number used for math precision 
	const double aeWin32Math::DOUBLE_EPSILON = NumericLimits<double>::epsilon();
	const double aeWin32Math::DOUBLE_NAN = NumericLimits<double>::quiet_NaN();
	const double aeWin32Math::DOUBLE_INFINITY = NumericLimits<double>::infinity();
	const double aeWin32Math::DOUBLE_ROUND_ERROR = NumericLimits<double>::round_error();
	const double aeWin32Math::DOUBLE_DENORM_MIN = NumericLimits<double>::denorm_min();

	const float aeWin32Math::DEG_2_RAD = aeWin32Math::PI/180;
	const float aeWin32Math::RAD_2_DEG = 180/ aeWin32Math::PI;

	/*************************************************************************************************/
	/* Fast math functions using Taylor series
	/*************************************************************************************************/
	float aeWin32Math::FastSin(const float& Value)
	{
		float Result = Value;
		float f = Value*Value*Value;
		Result -= f * 0.166666667f;
		f *= Value*Value;
		return Result += f *  0.008333333f;
		/*return Value - ((Value*Value*Value) * 0.166666667f)
			+ ((Value*Value*Value*Value*Value) * 0.008333333f);*/
	}

	float aeWin32Math::FastCos(const float& Value)
	{
		float Result = 1.0f;
		float f1 = Value*Value;
		Result -= f1 * 0.5f;
		float f2 = f1 * f1;
		Result += f2 * 0.041666667f;
		f2 *= f1;
		Result -= f2 * 0.001388889f;
		f2 *= f1;
		return Result += f2 * 0.000024801f;
		/*return 1.0f - (Value*Value*0.5f) + ((Value*Value*Value*Value) * 0.041666667f)
			- ((Value*Value*Value*Value*Value*Value) * 0.001388889f)
			+ ((Value*Value*Value*Value*Value*Value*Value*Value)* 0.000024801f);*/
	}

	float aeWin32Math::FastTan(const float& Value)
	{
		float Result = Value;
		float f1 = Value*Value*Value;
		Result += f1 * 0.333333333f;
		float f2 = Value*Value;
		f1 *= f2;
		Result += f1 * 0.133333333f;
		f1 *= f2;
		return Result += f1 * 0.053968253f;
		/*return Value + ((Value*Value*Value) * 0.333333333f)
			+ ((Value*Value*Value*Value*Value)*0.133333333f)
			+ ((Value*Value*Value*Value*Value*Value*Value)*0.053968253f);*/
	}

	float aeWin32Math::FastCot(const float& Value)
	{
		float Result = 1.0f / Value;
		float f1 = Value;
		Result -= f1 * 0.333333333f;
		float f2 = f1 * f1 * f1;
		f1 *= f1;
		Result -= f2 * 0.022222222f;
		f2 *= f1;
		Result -= f2 * 0.002116402f;
		f2 *= f1;
		return Result -= f2 * 0.000211640f;
		/*return 1.0f / Value - (Value * 0.333333333f)
			- ((Value*Value*Value) * 0.022222222f)
			- ((Value*Value*Value*Value*Value) * 0.002116402f)
			- ((Value*Value*Value*Value*Value*Value*Value) * 0.000211640f);*/
	}

	float aeWin32Math::FastSec(const float& Value)
	{
		float Result = 1.0f;
		float f1 = Value*Value;
		Result += f1 * 0.5f;
		float f2 = f1 * f1;
		Result += f2 * 0.208333333f;
		f2 *= f1;
		Result += f2 * 0.084722222f;
		f2 *= f1;
		return Result += f2 * 0.034350198f;
		/*return 1.0f + (Value*Value*0.5f)
			+ ((Value*Value*Value*Value) * 0.208333333f)
			+ ((Value*Value*Value*Value*Value*Value) * 0.084722222f)
			+ ((Value*Value*Value*Value*Value*Value*Value*Value) * 0.034350198f);*/
	}

	float aeWin32Math::FastCsc(const float& Value)
	{
		float Result = 1.0f / Value;
		float f1 = Value;
		Result += f1 * 0.166666667f;
		f1 *= f1;
		float f2 = f1 * Value;		
		Result += f2 * 0.019444444f;
		f2 *= f1;
		Result += f2 * 0.002050264f;
		f2 *= f1;
		return Result += f2 * 0.000209987f;
		/*return 1.0f / Value + (Value * 0.166666667f)
			+ ((Value*Value*Value) * 0.019444444f)
			+ ((Value*Value*Value*Value*Value) * 0.002050264f)
			+ ((Value*Value*Value*Value*Value*Value*Value) * 0.000209987f);*/
	}

	float aeWin32Math::FastArcSin(const float& Value)
	{
		float Result = Value;
		float f2 = Value*Value;
		float f1 = Value*f2;
		Result += f1 * 0.166666667f;		
		f1 *= f2;
		Result += f1 * 0.075f;
		f1 *= f2;
		Result += f1 * 0.044642857f;
		f1 *= f2;
		return Result += f1 * 0.030381944f;
		/*return Value + ((Value*Value*Value) * 0.166666667f)
			+ ((Value*Value*Value*Value*Value) * 0.075f)
			+ ((Value*Value*Value*Value*Value*Value*Value) * 0.044642857f)
			+ ((Value*Value*Value*Value*Value*Value*Value*Value*Value) * 0.030381944f);*/
	}

	float aeWin32Math::FastArcCos(const float& Value)
	{
		float Result = Value;
		float f2 = Value*Value;
		float f1 = Value*f2;
		Result += f1 * 0.166666667f;		
		f1 *= f2;
		Result += f1 * 0.075f;
		f1 *= f2;
		Result += f1 * 0.044642857f;
		f1 *= f2;
		Result += f1 * 0.030381944f;
		return HALF_PI - Result;
		/*return HALF_PI - (Value + ((Value*Value*Value) * 0.166666667f)
			+ ((Value*Value*Value*Value*Value) * 0.075f)
			+ ((Value*Value*Value*Value*Value*Value*Value) * 0.044642857f)
			+ ((Value*Value*Value*Value*Value*Value*Value*Value*Value) * 0.030381944f));*/
	}

	float aeWin32Math::FastArcTan(const float& Value)
	{
		float Result = Value;
		float f2 = Value*Value;
		float f1 = Value*f2;
		Result -= f1 * 0.333333333f;
		f1 *= f2;
		Result += f1 *  0.2f;
		f1 *= f2;
		Result -= f1 *  0.142857142f;
		f1 *= f2;
		return Result += f1 *  0.111111111f;
		/*return Value - ((Value*Value*Value) *0.333333333f)
			+ (Value*Value*Value*Value*Value*0.2f)
			- ((Value*Value*Value*Value*Value*Value*Value) *0.142857142f)
			+ (Value*Value*Value*Value*Value*Value*Value*Value*Value*0.111111111f);*/
	}

	float aeWin32Math::FastArcTan2(const float & Y, const float & X)
	{
		float r, angle;
		float abs_y = ((((*(uint32*)&Y) >= (uint32)0x80000000)) ? -Y : Y) + 1e-10f;      // kludge to prevent 0/0 condition
		if (X < 0.0f)
		{
			r = (X + abs_y) / (abs_y - X);
			angle = THREE_QUARTER_PI;
		}
		else
		{
			r = (X - abs_y) / (X + abs_y);
			angle = ONE_QUARTER_PI;
		}
		angle += (0.1963f * r * r - 0.9817f) * r;
		if (Y < 0.0f)
			return(-angle);     // negate if in quad III or IV
		else
			return(angle);
		/*if (X == 0.0f)
		{
			if (Y > 0.0f) return HALF_PI;
			return (Y == 0.0f) ? 0.0f : -HALF_PI;
		}
		float atan;
		float z = Y / X;
		if (/ *Abs(z) < 1.0f* / z < 1.0f && z > -1.0f)
		{
			atan = z / (1.0f + 0.28f*z*z);
			if (X < 0.0f)
			{
				return (Y < 0.0f) ? atan - PI : atan + PI;
			}
		}
		else
		{
			atan = HALF_PI - z / (z*z + 0.28f);
			if (Y < 0.0f) return atan - PI;
		}
		return atan;*/
	}
}