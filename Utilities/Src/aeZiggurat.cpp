#include "aeZiggurat.h"


namespace aeEngineSDK
{
	const uint32 aeZiggurat::ZIGGURAT_TABLE_SIZE = 256;
	const double aeZiggurat::ZIGGURAT_R = 3.6541528853610088;
	const double aeZiggurat::ZIGGURAT_INV_R = 0.27366123732975828;
	const double aeZiggurat::TWO_TO_POWER_31 = 2147483648.0;
	const double aeZiggurat::SECTION_AREA = 0.00492867323399;

	aeZiggurat::aeZiggurat()
	{
		ki.resize(ZIGGURAT_TABLE_SIZE);
		wi.resize(ZIGGURAT_TABLE_SIZE);
		fi.resize(ZIGGURAT_TABLE_SIZE);
		CreateTables();
	}

	aeZiggurat::aeZiggurat(const aeZiggurat & Z)
	{
		*this = Z;
	}

	aeZiggurat::~aeZiggurat()
	{
		ki.clear();
		wi.clear();
		fi.clear();
	}

	void aeZiggurat::Seed(uint32 S)
	{
		m_xRNG.SRand(S);
	}	double aeZiggurat::DRand()
	{
		while (true)
		{
			uint32 ri = m_xRNG.UIRand();
			uint8 idx = ri & 0x00FF;
			double x = ri * wi[idx];
			if (ri < ki[idx])
			{
				return x;		// 99.33% of the time we return here 1st try
			}
			else if (idx == 0)
			{
				/* As stated in Marsaglia and Tsang
				*
				* For the normal tail, the method of Marsaglia[5] provides:
				* generate x = -ln(U_1)/r, y = -ln(U_2), until y+y > x*x,
				* then return r+x. Except that r+x is always in the positive
				* tail!!!! Any thing random might be used to determine the
				* sign, but as we already have ri we might as well use it
				*/
				double xx, yy;
				do
				{
					xx = -ZIGGURAT_INV_R * aeMath::Loge(m_xRNG.FRand());
					yy = -aeMath::Loge(m_xRNG.FRand());
				} while (yy + yy <= xx*xx);
				return (ri < 0 ? -ZIGGURAT_R - xx : ZIGGURAT_R + xx);
			}
			else if ((fi[idx - 1] - fi[idx]) * m_xRNG.FRand() + fi[idx] <
				aeMath::Exp(-0.5*x*x))
			{
				return x;
			}
		}
	}

	double aeZiggurat::UDRand()
	{
		double x = DRand();
		return aeMath::Exp(-0.5*x*x);
	}

	void aeZiggurat::CreateTables()
	{
		double x, x1;

		x1 = ZIGGURAT_R;
		wi[255] = x1 / TWO_TO_POWER_31;
		fi[255] = aeMath::Exp(-0.5 * x1 * x1);

		/* Index zero is special for tail strip, where Marsaglia and Tsang defines
		* this as
		* k_0 = 2^31 * r * f(r) / v, w_0 = 0.5^31 * v / f(r), f_0 = 1,
		* where v is the area of each strip of the ziggurat.
		*/
		ki[0] = (uint32)(x1 * fi[255] / SECTION_AREA * TWO_TO_POWER_31);
		wi[0] = SECTION_AREA / fi[255] / TWO_TO_POWER_31;
		fi[0] = 1;

		for (int i = 254; i > 0; i--)
		{
			/* New x is given by x = f^{-1}(v/x_{i+1} + f(x_{i+1})), thus
			* need inverse operator of y = exp(-0.5*x*x) -> x = sqrt(-2*ln(y))
			*/
			x = aeMath::Sqrt(-2. * aeMath::Loge(SECTION_AREA / x1 + fi[i + 1]));
			ki[i + 1] = (uint32)(x / x1 * TWO_TO_POWER_31);
			wi[i] = x / TWO_TO_POWER_31;
			fi[i] = aeMath::Exp(-0.5 * x * x);
			x1 = x;
		}

		ki[1] = 0;
	}
}