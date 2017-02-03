/*************************************************************************************************/
/* @file	aeRandomNumberGenerator.h
/*
/* @brief	Declares the random number generator class.
/*************************************************************************************************/

#pragma once
#include "aePrerequisitesUtil.h"
#include "aeMath.h"

namespace aeEngineSDK
{
	class AE_UTILITY_EXPORT aeRNG
	{
		/*************************************************************************************************/
		/* Values used for random number generation
		/*************************************************************************************************/
	public:
		static const uint32 RandomConstantA;
		static const uint32 RandomConstantB;

		static const uint32 RandMax;
	private:
		uint32 m_nRandomSeed;

		/*************************************************************************************************/
		/* Default constructor and destructor
		/*************************************************************************************************/
	public:
		aeRNG();
		aeRNG(const aeRNG& RNG);
		~aeRNG();

		/*************************************************************************************************/
		/* Basic random functions	
		/*************************************************************************************************/
	public:
		void SRand(const int32& Seed)
		{
			m_nRandomSeed = static_cast<uint32>(Seed);
		}

		void SRand(const uint32& Seed)
		{
			m_nRandomSeed = static_cast<uint32>(Seed);
		}

		uint32 UIRand()
		{
			return m_nRandomSeed = ((m_nRandomSeed * RandomConstantA) + RandomConstantB);
		}

		uint32 UIRandHelper(const uint32& A)
		{
			return A > 0 ? (uint32)aeMath::Trunc((float)IRand() / (float)(RandMax + 1) * A) : 0;
		}

		uint32 UIRandRange(const uint32& Min, const uint32& Max)
		{
			return Min + UIRandHelper(Max);
		}
		
		int32 IRand()
		{
			return static_cast<int32>(UIRand());
		}

		int32 IRandHelper(const int32& A)
		{
			return static_cast<int32>(UIRandHelper(A));
		}

		int32 IRandRange(const int32& Min, const int32& Max)
		{
			return static_cast<int32>(UIRandRange(Min, Max));
		}

		float FRand()
		{
			return 0.5f*(((float)IRand() / (float)0x7fffffff) + 1);
		}

		float FRandRange(const float& Min, const float& Max) 
		{
			return Min + IRandHelper(static_cast<int32>((Max - Min) + 1));
		}
	};
}

