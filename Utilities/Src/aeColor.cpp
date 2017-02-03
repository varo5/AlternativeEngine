#include "aeColor.h"
#include "aeMath.h"

namespace aeEngineSDK
{
	const float LAMBDA = 1.0f / 2.2f;

	aeColor::aeColor()
	{
	}

	aeColor::aeColor(const aeColor & Color)
	{
		*this = Color;
	}

	aeColor::aeColor(const aeLinearColor & Color)
	{
		
		this->R = (BYTE)aeMath::Pow(Color.R, LAMBDA )*255;
		this->G = (BYTE)aeMath::Pow(Color.G, LAMBDA )*255;
		this->B = (BYTE)aeMath::Pow(Color.B, LAMBDA )*255;
		this->A = (BYTE)aeMath::Pow(Color.A, LAMBDA )*255;
	}

	aeColor::aeColor(BYTE R, BYTE G, BYTE B, BYTE A) : R(R), G(G), B(B), A(A)
	{
	}

	aeColor::aeColor(float R, float G, float B, float A)
	{
		this->R = (BYTE)aeMath::Pow(R, LAMBDA) * 255;
		this->G = (BYTE)aeMath::Pow(G, LAMBDA) * 255;
		this->B = (BYTE)aeMath::Pow(B, LAMBDA) * 255;
		this->A = (BYTE)aeMath::Pow(A, LAMBDA) * 255;
	}

	aeColor::~aeColor()
	{
	}

	aeLinearColor::aeLinearColor()
	{
	}

	aeLinearColor::aeLinearColor(const aeColor & Color)
	{
		this->R = aeMath::Pow((float)Color.R / 255, 2.2f);
		this->G = aeMath::Pow((float)Color.G / 255, 2.2f);
		this->B = aeMath::Pow((float)Color.B / 255, 2.2f);
		this->A = aeMath::Pow((float)Color.A / 255, 2.2f);
	}

	aeLinearColor::aeLinearColor(const aeLinearColor & Color)
	{
		*this = Color;
	}

	aeLinearColor::aeLinearColor(float R, float G, float B, float A) : R(R), G(G), B(B), A(A)
	{
	}

	aeLinearColor::aeLinearColor(BYTE R, BYTE G, BYTE B, BYTE A)
	{
		this->R = aeMath::Pow((float)R / 255, 2.2f);
		this->G = aeMath::Pow((float)G / 255, 2.2f);
		this->B = aeMath::Pow((float)B / 255, 2.2f);
		this->A = aeMath::Pow((float)A / 255, 2.2f);
	}

	aeLinearColor::~aeLinearColor()
	{
	}
}