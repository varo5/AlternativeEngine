#include "aeMath.h"

namespace aeEngineSDK
{
	aeQuaternion::~aeQuaternion()
	{

	}

	aeQuaternion::aeQuaternion(const aeQuaternion & Q)
	{
		*this = Q;
	}

	aeQuaternion::aeQuaternion(float rotx, float roty, float rotz)
	{
		const float fSinPitch(aeMath::Sin(rotx*0.5f));
		const float fCosPitch(aeMath::Cos(rotx*0.5f));
		const float fSinYaw(aeMath::Sin(roty*0.5f));
		const float fCosYaw(aeMath::Cos(roty*0.5f));
		const float fSinRoll(aeMath::Sin(rotz*0.5f));
		const float fCosRoll(aeMath::Cos(rotz*0.5f));
		const float fCosPitchCosYaw(fCosPitch*fCosYaw);
		const float fSinPitchSinYaw(fSinPitch*fSinYaw);
		x = fSinRoll * fCosPitchCosYaw - fCosRoll * fSinPitchSinYaw;
		y = fCosRoll * fSinPitch * fCosYaw + fSinRoll * fCosPitch * fSinYaw;
		z = fCosRoll * fCosPitch * fSinYaw - fSinRoll * fSinPitch * fCosYaw;
		w = fCosRoll * fCosPitchCosYaw + fSinRoll * fSinPitchSinYaw;
	}

	aeQuaternion::aeQuaternion(const aeVector3& axis, float angle)
	{
		aeVector3 v3 = axis;
		v3.Normalize();

		const float sin_a = aeMath::Sin(angle / 2);
		const float cos_a = aeMath::Cos(angle / 2);
		x = v3.x * sin_a;
		y = v3.y * sin_a;
		z = v3.z * sin_a;
		w = cos_a;
	}

	aeQuaternion::aeQuaternion(const aeVector3 & LookAt, aeVector3 up)
	{
		aeVector3 forward = LookAt;
		forward.Normalize();
		up.OrthoNormalize(forward); // Keeps up the same, make forward orthogonal to up
		aeVector3 right = up^forward;

		aeQuaternion ret;
		ret.w = sqrtf(1.0f + right.x + up.y + forward.z) * 0.5f;
		float w4_recip = 1.0f / (4.0f * ret.w);
		ret.x = (forward.y - up.z) * w4_recip;
		ret.y = (right.z - forward.x) * w4_recip;
		ret.z = (up.x - right.y) * w4_recip;

		*this = ret;
	}

	aeQuaternion::aeQuaternion(aeVector3 Normalized)
	{
		x = Normalized.x;
		y = Normalized.y;
		z = Normalized.z;

		const float t = 1.0f - (x*x) - (y*y) - (z*z);

		if (t < 0.0f)
			w = 0.0f;
		else 
			w = aeMath::Sqrt(t);
	}

	aeMatrix3 aeQuaternion::GetMatrix() const
	{
		aeMatrix3 resMatrix;
		resMatrix.f00 = 1.0f - 2.0f * (y * y + z * z);
		resMatrix.f01 = 2.0f * (x * y - z * w);
		resMatrix.f02 = 2.0f * (x * z + y * w);
		resMatrix.f10 = 2.0f * (x * y + z * w);
		resMatrix.f11 = 1.0f - 2.0f * (x * x + z * z);
		resMatrix.f12 = 2.0f * (y * z - x * w);
		resMatrix.f20 = 2.0f * (x * z - y * w);
		resMatrix.f21 = 2.0f * (y * z + x * w);
		resMatrix.f22 = 1.0f - 2.0f * (x * x + y * y);

		return resMatrix;
	}

	aeMatrix3 aeQuaternion::GetTransposedMatrix() const
	{
		aeMatrix3 resMatrix;
		resMatrix.f00 = 1.0f - 2.0f * (y * y + z * z);
		resMatrix.f10 = 2.0f * (x * y - z * w);
		resMatrix.f20 = 2.0f * (x * z + y * w);
		resMatrix.f01 = 2.0f * (x * y + z * w);
		resMatrix.f11 = 1.0f - 2.0f * (x * x + z * z);
		resMatrix.f21 = 2.0f * (y * z - x * w);
		resMatrix.f02 = 2.0f * (x * z - y * w);
		resMatrix.f12 = 2.0f * (y * z + x * w);
		resMatrix.f22 = 1.0f - 2.0f * (x * x + y * y);

		return resMatrix;
	}

	aeVector3 aeQuaternion::GetEulerAngles() const
	{
		aeVector3 v;

		float ysqr = y * y;

		// roll (x-axis rotation)
		float t0 = +2.0f * (w * x + y * z);
		float t1 = +1.0f - 2.0f * (x * x + ysqr);
		v.x = aeMath::ArcTan2(t0, t1);

		// pitch (y-axis rotation)
		float t2 = +2.0f * (w * y - z * x);
		t2 = t2 > 1.0f ? 1.0f : t2;
		t2 = t2 < -1.0f ? -1.0f : t2;
		v.y = aeMath::ArcSin(t2);

		// yaw (z-axis rotation)
		float t3 = +2.0f * (w * z + x *y);
		float t4 = +1.0f - 2.0f * (ysqr + z * z);
		v.z = aeMath::ArcTan2(t3, t4);

		return v;
	}

	inline float aeQuaternion::Norm() const
	{
		return x*x + y*y + z*z + w*w;
	}

	inline float aeQuaternion::Magnitude()
	{
		return aeMath::Sqrt(x*x + y*y + z*z + w*w);
	}

	inline void aeQuaternion::Normalize()
	{
		*this = Normalized();
	}

	bool aeQuaternion::operator==(const aeQuaternion & o) const
	{
		return x == o.x && y == o.y && z == o.z && w == o.w;
	}

	bool aeQuaternion::operator!=(const aeQuaternion & o) const
	{
		return !(*this == o);
	}

	bool aeQuaternion::Equal(const aeQuaternion & o, float epsilon) const
	{
		return
			aeMath::Abs(x - o.x) <= epsilon &&
			aeMath::Abs(y - o.y) <= epsilon &&
			aeMath::Abs(z - o.z) <= epsilon &&
			aeMath::Abs(w - o.w) <= epsilon;
	}

	inline aeQuaternion aeQuaternion::Normalized()
	{
		return (*this).Scale(1/(*this).Magnitude());
	}

	aeQuaternion aeQuaternion::Scale(float s) const
	{
		return aeQuaternion( x*s, y*s, z*s, w*s);
	}

	aeQuaternion aeQuaternion::Inverse() const
	{
		return Conjugated().Scale(1/Norm());
	}

	void aeQuaternion::Conjugate()
	{
		x = -x;
		y = -y;
		z = -z;
	}

	aeQuaternion aeQuaternion::Conjugated() const
	{
		aeQuaternion result;
		result.x = -x;
		result.y = -y;
		result.z = -z;
		return result;
	}

	aeVector3 aeQuaternion::Rotate(const aeVector3 & v)
	{
		aeQuaternion q2(0.0f, v.x, v.y, v.z), q = *this, qinv = q;
		qinv.Conjugate();

		q = q*q2*qinv;
		return aeVector3(q.x, q.y, q.z);
	}

	inline aeVector3 aeQuaternion::GetDirection()
	{
		return GetMatrix()*aeVector3 { 1, 0, 0 };
	}

	inline aeQuaternion aeQuaternion::operator+(const aeQuaternion & Q)
	{
		return aeQuaternion(x + Q.x, y + Q.y, z + Q.z, w + Q.w);
	}

	inline aeQuaternion aeQuaternion::operator-(const aeQuaternion & Q)
	{
		return aeQuaternion(x - Q.x, y - Q.y, z - Q.z, w - Q.w);
	}

	inline aeQuaternion aeQuaternion::operator*(const aeQuaternion & t)
	{
		return aeQuaternion(
			w*t.x + x*t.w + y*t.z - z*t.y,
			w*t.y + y*t.w + z*t.x - x*t.z,
			w*t.z + z*t.w + x*t.y - y*t.x,
			w*t.w - x*t.x - y*t.y - z*t.z);
	}

	inline aeQuaternion aeQuaternion::operator/(const aeQuaternion & Q)
	{
		return ((*this)*(Q.Inverse()));
	}

	inline aeQuaternion aeQuaternion::operator*(const float & F)
	{
		return aeQuaternion(F*x, F*y, F*z, F*w);
	}

	aeVector3 aeQuaternion::operator*(const aeVector3 & v)
	{
		/*float num1 = x * 2.0f;
		float num2 = y * 2.0f;
		float num3 = z * 2.0f;
		float num4 = x * num1;
		float num5 = y * num2;
		float num6 = z * num3;
		float num7 = x * num2;
		float num8 = x * num3;
		float num9 = y * num3;
		float num10 = w * num1;
		float num11 = w * num2;
		float num12 = w * num3;
		aeVector3 result;
		result.x = (1.0f - (num5 + num6)) * v.x + (num7 - num12) * v.y + (num8 + num11) * v.z;
		result.y = (num7 + num12) * v.x + (1.0f - (num4 + num6)) * v.y + (num9 - num10) * v.z;
		result.z = (num8 - num11) * v.x + (num9 + num10) * v.y + (1.0f - (num4 + num5)) * v.z;
		return result;*/
		aeVector3 uv, uuv;
		aeVector3 qvec(x, y, z);
		uv = qvec.Cross(v);
		uuv = qvec.Cross(uv);
		uv *= (2.0f * w);
		uuv *= 2.0f;
		
		return v + uv + uuv;
	}

	inline aeQuaternion & aeQuaternion::operator+=(const aeQuaternion & Q)
	{
		w += Q.w;
		x += Q.x;
		y += Q.y;
		z += Q.z;

		return (*this);
	}

	inline aeQuaternion & aeQuaternion::operator-=(const aeQuaternion & Q)
	{
		w -= Q.w;
		x -= Q.x;
		y -= Q.y;
		z -= Q.z;

		return (*this);
	}

	inline aeQuaternion & aeQuaternion::operator*=(const aeQuaternion & Q)
	{
		float w_val = w*Q.w - x*Q.x - y*Q.y - z*Q.z;
		float x_val = w*Q.x + x*Q.w + y*Q.z - z*Q.y;
		float y_val = w*Q.y + y*Q.w + z*Q.x - x*Q.z;
		float z_val = w*Q.z + z*Q.w + x*Q.y - y*Q.x;

		w = w_val;
		x = x_val;
		y = y_val;
		z = z_val;

		return (*this);
	}

	inline aeQuaternion & aeQuaternion::operator/=(const aeQuaternion & Q)
	{
		(*this) = (*this)*Q.Inverse();
		return (*this);
	}

	aeQuaternion & aeQuaternion::operator*=(const float & F)
	{
		w *= F;
		x *= F;
		y *= F;
		z *= F;

		return (*this);
	}

	void aeQuaternion::Interpolate(aeQuaternion & pOut, const aeQuaternion & pStart, const aeQuaternion & pEnd, float pFactor)
	{
		// calc cosine theta
		float cosom = pStart.x * pEnd.x + pStart.y * pEnd.y + pStart.z * pEnd.z + pStart.w * pEnd.w;

		// adjust signs (if necessary)
		aeQuaternion end = pEnd;
		if (cosom < 0.0f)
		{
			cosom = -cosom;
			end.x = -end.x;   // Reverse all signs
			end.y = -end.y;
			end.z = -end.z;
			end.w = -end.w;
		}

		// Calculate coefficients
		float sclp, sclq;
		if ((1.0f - cosom) > 0.0001f) // 0.0001 -> some epsillon
		{
			// Standard case (slerp)
			float omega, sinom;
			omega = aeMath::ArcCos(cosom); // extract theta from dot product's cos theta
			sinom = aeMath::Sin(omega);
			sclp = aeMath::Sin((1.0f - pFactor) * omega) / sinom;
			sclq = aeMath::Sin(pFactor * omega) / sinom;
		}
		else
		{
			// Very close, do linear interp (because it's faster)
			sclp = 1.0f - pFactor;
			sclq = pFactor;
		}

		pOut.x = sclp * pStart.x + sclq * end.x;
		pOut.y = sclp * pStart.y + sclq * end.y;
		pOut.z = sclp * pStart.z + sclq * end.z;
		pOut.w = sclp * pStart.w + sclq * end.w;
	}


}