#include "aeMath.h"


namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* Constructors                                                        													*/
	/*************************************************************************************************/
	aeMatrix4::aeMatrix4()
	{
	}

	aeMatrix4::aeMatrix4(const aeMatrix4& M)
	{
		*this = M;
	}

	aeMatrix4::aeMatrix4(
		const aeVector4& V0,
		const aeVector4& V1,
		const aeVector4& V2,
		const aeVector4& V3)
	{
		v4[0] = V0;
		v4[1] = V1;
		v4[2] = V2;
		v4[3] = V3;
	}

	aeMatrix4::aeMatrix4(
		float _00, float _01, float _02, float _03,
		float _10, float _11, float _12, float _13,
		float _20, float _21, float _22, float _23,
		float _30, float _31, float _32, float _33)
	{
		f00 = _00; f01 = _01; f02 = _02; f03 = _03;
		f10 = _10; f11 = _11; f12 = _12; f13 = _13;
		f20 = _20; f21 = _21; f22 = _22; f23 = _23;
		f30 = _30; f31 = _31; f32 = _32; f33 = _33;
	}

	aeMatrix4::~aeMatrix4()
	{
	}

	/*************************************************************************************************/
	/* Vectors inside the matrix related functions.					          												*/
	/*************************************************************************************************/
	void aeMatrix4::SetCol(const aeVector4 & V, const uint8& nCol)
	{
		aeMatrix4 M = ~*this;
		M.v4[nCol] = V;
		*this = ~M;
	}

	void aeMatrix4::SetRow(const aeVector4 & V, const uint8& nRow)
	{
		v4[nRow] = V;
	}

	aeVector4 aeMatrix4::GetCol(const uint8& nCol) const
	{
		aeMatrix4 M = ~*this;
		return M.v4[nCol];
	}

	aeVector4 aeMatrix4::GetRow(const uint8& nRow) const
	{
		return v4[nRow];
	}

	/*************************************************************************************************/
	/* Implementation of arithmetic operators						          												*/
	/*************************************************************************************************/
	aeMatrix4 aeMatrix4::operator+(const aeMatrix4 & M) const
	{
		aeMatrix4 T = ~M;
		return aeMatrix4(v4[0] + T.v4[0], v4[1] + T.v4[1], v4[2] + T.v4[2], v4[3] + T.v4[3]);
	}

	aeMatrix4 aeMatrix4::operator-(const aeMatrix4 & M) const
	{
		aeMatrix4 T = ~M;
		return aeMatrix4(v4[0] - T.v4[0], v4[1] - T.v4[1], v4[2] - T.v4[2], v4[3] - T.v4[3]);
	}

	aeMatrix4 aeMatrix4::operator*(const aeMatrix4 & M) const
	{
		aeMatrix4 T = ~M;
		return aeMatrix4(v4[0] * M.v4[0], v4[1] * M.v4[1], v4[2] * M.v4[2], v4[3] * M.v4[3]);
	}

	aeMatrix4 aeMatrix4::operator*(const float& S) const
	{
		return aeMatrix4(v4[0] * S, v4[1] * S, v4[2] * S, v4[3] * S);
	}

	aeMatrix4 aeMatrix4::operator/(const float& S) const
	{
		float Inv = 1.0f / S;
		return *this*Inv;
	}

	aeVector4 aeMatrix4::operator*(const aeVector4& V) const
	{
		aeMatrix4 M = ~*this;
		M.v4[0] *= V.x;
		M.v4[1] *= V.y;
		M.v4[2] *= V.z;
		M.v4[3] *= V.w;
		M = ~M;
		return aeVector4(+M.v4[0], +M.v4[1], +M.v4[2], +M.v4[3]);
	}

	/*************************************************************************************************/
	/* Functions Implementation                                            													*/
	/*************************************************************************************************/

	float aeMatrix4::Det() const
	{
		return
			f00*(f11*(f22*f33 - f23*f32)
				- f12*(f21*f33 - f23*f31)
				+ f13*(f21*f32 - f22*f31))
			- f01*(f10*(f22*f33 - f23*f32)
				- f12*(f20*f33 - f23*f30)
				+ f13*(f20*f32 - f22*f30))
			+ f02*(f10*(f21*f33 - f23*f31)
				- f11*(f20*f33 - f23*f30)
				+ f13*(f20*f31 - f21*f30))
			- f03*(f10*(f21*f32 - f22*f31)
				- f11*(f20*f32 - f22*f30)
				+ f12*(f20*f31 - f21*f30));
	}

	aeMatrix4 aeMatrix4::Cofactor() const
	{
		aeMatrix4 B;
		B.f00 = (f11*(f22*f33 - f23*f32)
			- f12*(f21*f33 - f23*f31)
			+ f13*(f21*f32 - f22*f31));
		B.f01 = -(f10*(f22*f33 - f23*f32)
			- f12*(f20*f33 - f23*f30)
			+ f13*(f20*f32 - f22*f30));
		B.f02 = (f10*(f21*f33 - f23*f31)
			- f11*(f20*f33 - f23*f30)
			+ f13*(f20*f31 - f21*f30));
		B.f03 = -(f10*(f21*f32 - f22*f31)
			- f11*(f20*f32 - f22*f30)
			+ f12*(f20*f31 - f21*f30));

		B.f10 = -(f01*(f22*f33 - f23*f32)
			- f02*(f21*f33 - f23*f31)
			+ f03*(f21*f32 - f22*f31));
		B.f11 = (f00*(f22*f33 - f23*f32)
			- f02*(f20*f33 - f23*f30)
			+ f03*(f20*f32 - f22*f30));
		B.f12 = -(f00*(f21*f33 - f23*f31)
			- f01*(f20*f33 - f23*f30)
			+ f03*(f20*f31 - f21*f30));
		B.f13 = (f00*(f21*f32 - f22*f31)
			- f01*(f20*f32 - f22*f30)
			+ f02*(f20*f31 - f21*f30));

		B.f20 = (f01*(f12*f33 - f13*f32)
			- f02*(f11*f33 - f13*f31)
			+ f03*(f11*f32 - f12*f31));
		B.f21 = -(f00*(f12*f33 - f13*f32)
			- f02*(f10*f33 - f13*f30)
			+ f03*(f10*f32 - f12*f30));
		B.f22 = (f00*(f11*f33 - f13*f31)
			- f01*(f10*f33 - f13*f30)
			+ f03*(f10*f31 - f11*f30));
		B.f23 = -(f00*(f11*f32 - f12*f31)
			- f01*(f10*f32 - f12*f30)
			+ f02*(f10*f31 - f11*f30));

		B.f30 = -(f01*(f12*f23 - f13*f22)
			- f02*(f11*f23 - f13*f21)
			+ f03*(f11*f22 - f12*f21));
		B.f31 = (f00*(f12*f23 - f13*f22)
			- f02*(f10*f23 - f13*f20)
			+ f03*(f10*f22 - f12*f20));
		B.f32 = -(f00*(f11*f23 - f13*f21)
			- f01*(f10*f23 - f13*f20)
			+ f03*(f10*f21 - f11*f20));
		B.f33 = (f00*(f11*f22 - f12*f21)
			- f01*(f10*f22 - f12*f20)
			+ f02*(f10*f21 - f11*f20));
		return B;
	}

	aeMatrix4 aeMatrix4::Inverse() const
	{
		float DetA = (+*this);
		if (DetA != 0)
		{
			aeMatrix4 B = Adjunct();
			B = B / DetA;
			return B;
		}
		return aeMatrix4{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	}

	aeVector4 aeMatrix4::Cramer(const aeVector4& V) const
	{
		float DetM = (+*this);
		if (DetM != 0)
		{
			aeMatrix4 D0 = { V.x, f01, f02, f03,
				V.y, f11, f12, f13,
				V.z, f21, f22, f23,
				V.w, f31, f32, f33 };
			aeMatrix4 D1 = { f00, V.x, f02, f03,
				f10, V.y, f12, f13,
				f20, V.z, f22, f23,
				f30, V.w, f32, f33 };
			aeMatrix4 D2 = { f00, f01, V.x, f03,
				f10, f11, V.y, f13,
				f20, f21, V.z, f23,
				f30, f31, V.w, f33 };
			aeMatrix4 D3 = { f00, f01, f02, V.x,
				f10, f11, f12, V.y,
				f20, f21, f22, V.z,
				f30, f31, f32, V.w };
			float d0 = (+D0);
			float d1 = (+D1);
			float d2 = (+D2);
			float d3 = (+D3);

			return aeVector4{ d0 / DetM, d1 / DetM, d2 / DetM, d3 / DetM };
		}
		return aeVector4{ -1,-1,-1,-1 };
	}

	inline aeMatrix4 aeMatrix4::TranslationMatrix(const aeVector3& V)
	{
		return aeMatrix4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			V.x, V.y, V.z, 1);
	}

	inline aeMatrix4 aeMatrix4::TranslationMatrix(const float& x, const float& y, const float& z)
	{
		return aeMatrix4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			x, y, z, 1);
	}

	inline aeMatrix4 aeMatrix4::ScalingMatrix(const float& ScaleFactor)
	{
		return aeMatrix4(
			ScaleFactor, 0, 0, 0,
			0, ScaleFactor, 0, 0,
			0, 0, ScaleFactor, 0,
			0, 0, 0, 1);
	}

	inline aeMatrix4 aeMatrix4::ScalingMatrix(const float& x, const float& y, const float& z)
	{
		return aeMatrix4(
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1);
	}

	inline aeMatrix4 aeMatrix4::ScalingMatrix(const aeVector3& V)
	{
		return aeMatrix4(
			V.x, 0, 0, 0,
			0, V.y, 0, 0,
			0, 0, V.z, 0,
			0, 0, 0, 1);
	}

	aeMatrix4 aeMatrix4::RotationX(const float& theta)
	{
		aeMatrix4 R(1);
		R.f00 = R.f22 = aeMath::Cos(theta);
		R.f12 = -aeMath::Sin(theta);
		R.f21 = -R.f12;
		return R;
	}

	aeMatrix4 aeMatrix4::RotationY(const float& theta)
	{
		aeMatrix4 R(1);
		R.f00 = R.f22 = aeMath::Cos(theta);
		R.f20 = -aeMath::Sin(theta);
		R.f02 = -R.f20;
		return R;
	}

	aeMatrix4 aeMatrix4::RotationZ(const float& theta)
	{
		aeMatrix4 R(1);
		R.f11 = R.f00 = aeMath::Cos(theta);
		R.f01 = -aeMath::Sin(theta);
		R.f10 = -R.f01;
		return R;
	}

	inline aeMatrix4 aeMatrix4::RotationMatrix(const aeVector3 & V)
	{
		return RotationMatrix(V.x, V.y, V.z);
	}

	aeMatrix4 aeMatrix4::LookAtLH(aeVector3 & EyePos, aeVector3 & Target, aeVector3 & Up)
	{
		aeVector3 xDir, yDir, zDir;
		zDir = Target - EyePos;
		zDir.Normalize();
		xDir = Up.Cross(zDir);
		xDir.Normalize();
		yDir = zDir.Cross(xDir);
		yDir.Normalize();
		return aeMatrix4(xDir.x, yDir.x, zDir.x, 0,
			xDir.y, yDir.y, zDir.y, 0,
			xDir.z, yDir.z, zDir.z, 0,
			xDir.Dot(EyePos), -yDir.Dot(EyePos), -zDir.Dot(EyePos), 1);
	}

	aeMatrix4 aeMatrix4::PerspectiveFOVLH(float zNear, float zFar, float FOV, float AspectRatio)
	{
		float yScale = 1.0f / aeMath::Tan(FOV * 0.5f);
		float xScale = yScale / AspectRatio;
		return aeMatrix4(
			xScale, 0, 0, 0,
			0, yScale, 0, 0,
			0, 0, zFar*zNear / (zFar - zNear), 1,
			0, 0, -zNear*zFar / (zFar - zNear), 0);
	}

	aeMatrix4 aeMatrix4::MatrixOrthoLH(float w, float h, float zNear, float zFar)
	{
		return aeMatrix4(2.0f / w, 0, 0, 0,
			0, 2.0f / h, 0, 0,
			0, 0, zFar*zNear / (zFar - zNear), 1,
			0, 0, -zNear*zFar / (zFar - zNear), 0);
	}	

	aeMatrix4 aeMatrix4::RotationMatrix(float roll, float pitch, float yaw)
	{
		aeMatrix4 out = { 0 };
		out.f00 = (aeMath::Cos(roll) * aeMath::Cos(yaw)) + (aeMath::Sin(roll) * aeMath::Sin(pitch) * aeMath::Sin(yaw));
		out.f01 = (aeMath::Sin(roll) * aeMath::Cos(pitch));
		out.f02 = (aeMath::Cos(roll) * -aeMath::Sin(yaw)) + (aeMath::Sin(roll) * aeMath::Sin(pitch) * aeMath::Cos(yaw));
		out.f10 = (-aeMath::Sin(roll) * aeMath::Cos(yaw)) + (aeMath::Cos(roll) * aeMath::Sin(pitch) * aeMath::Sin(yaw));
		out.f11 = (aeMath::Cos(roll) * aeMath::Cos(pitch));
		out.f12 = (aeMath::Sin(roll) * aeMath::Sin(yaw)) + (aeMath::Cos(roll) * aeMath::Sin(pitch) * aeMath::Cos(yaw));
		out.f20 = (aeMath::Cos(pitch) * aeMath::Sin(yaw));
		out.f21 = -aeMath::Sin(pitch);
		out.f22 = (aeMath::Cos(pitch) * aeMath::Cos(yaw));
		out.f33 = 1;
		return out;
	}

	aeMatrix4 aeMatrix4::TransformationMatrix(const aeQuaternion & Rotation, const aeVector3 & Translation, const aeVector3 & Scale)
	{
		return TranslationMatrix(Translation) * Rotation.GetMatrix() * ScalingMatrix(Scale);
	}

	aeMatrix4 aeMatrix4::TransformationMatrix(const aeVector3 & Rotation, const aeVector3 & Translation, const aeVector3 & Scale)
	{
		return TranslationMatrix(Translation) * RotationMatrix(Rotation) * ScalingMatrix(Scale);;
	}

	inline aeMatrix4 aeMatrix4::Zero()
	{
		return aeMatrix4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);;
	}

	inline aeMatrix4 aeMatrix4::Identity()
	{
		return aeMatrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	}
}