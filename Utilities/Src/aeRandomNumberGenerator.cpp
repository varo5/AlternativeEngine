#include "aeRandomNumberGenerator.h"
#include "aePrerequisitesUtil.h"

namespace aeEngineSDK
{
	const uint32 aeRNG::RandomConstantA = 196314165;
	const uint32 aeRNG::RandomConstantB = 907633515;
	const uint32 aeRNG::RandMax = 0x7fff;

	aeRNG::aeRNG()
	{
	}

	aeRNG::aeRNG(const aeRNG & RNG)
	{
		*this = RNG;
	}

	aeRNG::~aeRNG()
	{
	}
}