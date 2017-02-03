#pragma once
#include "aePrerequisitesUtil.h"

namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* Basic color types
	/*************************************************************************************************/
	class aeLinearColor;
	
	class AE_UTILITY_EXPORT aeColor
	{
	public:
		union
		{
			struct
			{
#if AE_PLATFORM == AE_PLATFORM_LINUX
				BYTE A, R, G, B;
#else
				BYTE R, G, B, A;
#endif
			};
			uint32 C;
		};
	public:
		aeColor();
		aeColor(const aeColor& Color);
		aeColor(const aeLinearColor& Color);
		aeColor(BYTE R, BYTE G, BYTE B, BYTE A);
		explicit aeColor(float R, float G, float B, float A);
		~aeColor();
	};

	class AE_UTILITY_EXPORT aeLinearColor
	{
	public:
		union
		{
			struct
			{
#if AE_PLATFORM == AE_PLATFORM_LINUX
				float A, R, G, B;
#else
				float R, G, B, A;
#endif
			};
			float f[4];
		};
	public:
		aeLinearColor();
		aeLinearColor(const aeColor& Color);
		aeLinearColor(const aeLinearColor& Color);
		aeLinearColor(float R, float G, float B, float A);
		explicit aeLinearColor(BYTE R, BYTE G, BYTE B, BYTE A);
		~aeLinearColor();
	};
}
