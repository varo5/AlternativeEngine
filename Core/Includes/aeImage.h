#pragma once
#include "aePrerequisitesCore.h"
#include <aePrerequisitesUtil.h>
#include <aeString.h>

namespace aeEngineSDK
{
	class AE_CORE_EXPORT aeImage
	{
	private:
		void* m_pData;

		uint32 m_nWidth, m_nHeight;

		uint32 m_nBPP;
	public:
		aeImage();
		aeImage(const aeImage& I);
		~aeImage();

		void LoadFromFilePath(const String& pszFileName);
		void Unload();

		uint32 GetWidth();
		uint32 GetHeight();
		uint32 GetBitsPerPixel();

		void ConvertTo32Bits();

		void FlipHorizontal();
		void FlipVertical();

		bool IsLoaded();
		
		BYTE* GetBits();
	};
}