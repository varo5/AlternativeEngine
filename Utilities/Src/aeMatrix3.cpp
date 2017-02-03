#include "aeMath.h"

namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* Constructors 
	/*************************************************************************************************/
	aeMatrix3::aeMatrix3()
	{
	}


	aeMatrix3::~aeMatrix3()
	{
	}

	aeMatrix3::aeMatrix3(const aeMatrix3& M)
	{
		*this = M;
	}

	aeMatrix3::aeMatrix3(const aeVector3 & V0, const aeVector3 & V1, const aeVector3 & V2)
	{
		v3[0] = V0;
		v3[1] = V1;
		v3[2] = V2;
	}

	aeMatrix3::aeMatrix3(
		float _00, float _01, float _02,
		float _10, float _11, float _12,
		float _20, float _21, float _22)
	{
		f00 = _00; f01 = _01; f02 = _02;
		f10 = _10; f11 = _11; f12 = _12;
		f20 = _20; f21 = _21; f22 = _22;
	}

	/*************************************************************************************************/
	/* Vectors inside the matrix related functions.
	/*************************************************************************************************/
	void aeMatrix3::SetCol(const aeVector3 & V, const uint8& nCol) 
	{
		aeMatrix3 M = ~*this;
		M.v3[nCol] = V;
		*this = ~M;
	}

	void aeMatrix3::SetRow(const aeVector3 & V, const uint8& nRow) 
	{
		v3[nRow] = V;
	}

	aeVector3 aeMatrix3::GetCol(const uint8& nCol) const
	{
		aeMatrix3 M = ~*this;
		return M.v3[nCol];
	}

	aeVector3 aeMatrix3::GetRow(const uint8& nRow) const
	{
		return v3[nRow];
	}

	/*************************************************************************************************/
	/* Implementation of arithmetic operators
	/*************************************************************************************************/
	aeMatrix3 aeMatrix3::operator+(const aeMatrix3& M) const
	{
		aeMatrix3 T = ~M;
		return aeMatrix3(v3[0] + T.v3[0], v3[1] + T.v3[1], v3[2] + T.v3[2]);
	}

	aeMatrix3 aeMatrix3::operator-(const aeMatrix3& M) const
	{
		aeMatrix3 T = ~M;
		return aeMatrix3(v3[0] - T.v3[0], v3[1] - T.v3[1], v3[2] - T.v3[2]);
	}

	aeMatrix3 aeMatrix3::operator*(const aeMatrix3& M) const
	{
		aeMatrix3 T = ~M;
		return aeMatrix3(v3[0] * T.v3[0], v3[1] * T.v3[1], v3[2] * T.v3[2]);
	}

	aeMatrix3 aeMatrix3::operator*(const float& S) const
	{
		return aeMatrix3(v3[0] * S, v3[1] * S, v3[2] * S);
	}

	aeMatrix3 aeMatrix3::operator/(const float& S) const
	{
		float Inv = 1.0f / S;
		return *this*Inv;
	}

	aeVector3 aeMatrix3::operator*(const aeVector3& V) const
	{
		aeMatrix3 M = ~*this;
		M.v3[0] *= V.x;
		M.v3[1] *= V.y;
		M.v3[2] *= V.z;
		M = ~M;
		return aeVector3(+M.v3[0], +M.v3[1], +M.v3[2]);
	}

	/*************************************************************************************************/
	/* Functions Implementation
	/*************************************************************************************************/
	float aeMatrix3::Det() const
	{
		return f00*(f11*f22 - f12*f21) - f01*(f10*f22 - f12*f20) + f02*(f10*f21 - f11*f20);
	}

	aeVector3 aeMatrix3::Cramer(const aeVector3 & V) const
	{
		float DetM = +*this;
		if (DetM != 0)
		{
			aeMatrix3 D0 = { 
				V.x, f01, f02,
				V.y, f11, f12,
				V.z, f21, f22 };
			aeMatrix3 D1 = { 
				f00, V.x, f02,
				f10, V.y, f12,
				f20, V.z, f22 };
			aeMatrix3 D2 = { 
				f00, f01, V.x,
				f10, f11, V.y,
				f20, f21, V.z };
			float d0 = +D0;
			float d1 = +D1;
			float d2 = +D2;

			return aeVector3{ d0 / DetM, d1 / DetM, d2 / DetM };
		}
		return aeVector3{ -1,-1,-1 };
	}
	
	aeMatrix3 aeMatrix3::Cofactor() const
	{
		aeMatrix3 B;
		B.f00 = (f11*f22 - f12*f21);
		B.f01 = -(f10*f22 - f12*f20);
		B.f02 = (f10*f21 - f11*f20);

		B.f10 = -(f01*f22 - f02*f21);
		B.f11 = (f00*f22 - f02*f20);
		B.f12 = -(f00*f21 - f01*f20);

		B.f20 = (f01*f12 - f02*f11);
		B.f21 = -(f00*f12 - f02*f10);
		B.f22 = (f00*f11 - f01*f10);
		return B;
	}

	aeMatrix3 aeMatrix3::Inverse() const
	{
		float DetA = +*this;
		if (DetA != 0)
		{
			aeMatrix3 B = Adjunct();
			B = B / DetA;
			return B;
		}
		return aeMatrix3{ -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	}

	aeMatrix3 aeMatrix3::RotationX(const float& theta)
	{
		aeMatrix3 R(1);
		R.f00 = R.f22 = cosf(theta);
		R.f12 = -sinf(theta);
		R.f21 = -R.f12;
		return R;
	}

	aeMatrix3 aeMatrix3::RotationY(const float& theta)
	{
		aeMatrix3 R(1);
		R.f00 = R.f22 = cosf(theta);
		R.f20 = -sinf(theta);
		R.f02 = -R.f20;
		return R;
	}

	aeMatrix3 aeMatrix3::RotationZ(const float& theta)
	{
		aeMatrix3 R(1);
		R.f11 = R.f00 = cosf(theta);
		R.f01 = -sinf(theta);
		R.f10 = -R.f01;
		return R;
	}

	inline aeMatrix3 aeMatrix3::RotationMatrix(const aeVector3 & V)
	{
		return RotationX(V.x)*RotationY(V.y)*RotationZ(V.z);
	}

	inline aeMatrix3 aeMatrix3::Zero()
	{
		return aeMatrix3(0, 0, 0, 0, 0, 0, 0, 0, 0);
	}

	inline aeMatrix3 aeMatrix3::Identity()
	{
		return aeMatrix3(1, 0, 0, 0, 1, 0, 0, 0, 1);
	}
}