#include "aeMath.h"
#include "..\Includes\aePlane.h"

namespace aeEngineSDK
{
	aePlane::aePlane()
	{
	}

	aePlane::~aePlane()
	{
	}

	aePlane::aePlane(const aePlane & P)
	{
		*this = P;
	}

	aePlane::aePlane(const aeVector3 & V)
	{
		x = V.x;
		y = V.y;
		z = V.z;
	}

	aePlane::aePlane(float X, float Y, float Z, float D)
	{
		x = X;
		y = Y;
		z = Z;
		d = D;
	}

	aePlane::aePlane(const aeVector3 & A, const aeVector3 & B, const aeVector3 & C)
	{
		*this = !((B - A) ^ (C - A));
		d = *this | A;
	}

	void aePlane::Transform(const aeVector3 & Rotation, const aeVector3 & Translation)
	{
		aeMatrix4 M = aeMatrix4::RotationMatrix(Rotation);

		aeVector4 N = *this * d;
		aeVector4 O = N; O.w = 1;

		O = M*O;
		N = ~(!M) * N;
		*this = aeVector3(N);
		d = *this | aeVector3(O);
	}

	void aePlane::Transform(const aeQuaternion & Rotation, const aeVector3 & Translation)
	{
		aeMatrix4 M = Rotation.GetMatrix();

		aeVector4 N = *this * d;
		aeVector4 O = N; O.w = 1;

		O = M*O;
		N = ~(!M) * N;
		*this = aeVector3(N);
		d = *this | aeVector3(O);
	}

	void aePlane::Transform(const aeMatrix3 & Rotation, const aeVector3 & Translation)
	{
		aeMatrix4 M = Rotation;

		aeVector4 N = *this * d;
		aeVector4 O = N; O.w = 1;

		O = M*O;
		N = ~(!M) * N;
		*this = aeVector3(N);
		d = *this | aeVector3(O);
	}

	void aePlane::Transform(const aeMatrix4 & Transformation)
	{
		aeVector4 N = *this * d;
		aeVector4 O = N; O.w = 1;

		O = Transformation*O;
		N = ~(!Transformation) * N;
		*this = aeVector3(N);
		d = *this | aeVector3(O);
	}

	inline bool aePlane::IsInFront(const aeVector3 & Point)
	{
		return (*this|Point) >= 0;
	}
}