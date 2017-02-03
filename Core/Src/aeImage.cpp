#include "aeImage.h"
#include <FreeImage.h>

namespace aeEngineSDK
{
	aeImage::aeImage()
	{
		m_pData = nullptr;
		m_nHeight = 0;
		m_nWidth = 0;
	}

	aeImage::aeImage(const aeImage & I)
	{
		*this = I;
	}

	aeImage::~aeImage()
	{
	}

	void aeImage::LoadFromFilePath(const String& pszFileName)
	{
		FREE_IMAGE_FORMAT format = FreeImage_GetFileType(pszFileName.c_str(),pszFileName.size());
		FIBITMAP* bitmap = FreeImage_Load(format, pszFileName.c_str(), pszFileName.size());

		m_nWidth = FreeImage_GetWidth(bitmap);
		m_nHeight = FreeImage_GetHeight(bitmap);
		m_nBPP = FreeImage_GetBPP(bitmap);

		m_pData = bitmap;
	}

	void aeImage::Unload()
	{
		FreeImage_Unload((FIBITMAP*)m_pData);
	}
	
	inline uint32 aeImage::GetWidth()
	{
		return m_nWidth;
	}

	inline uint32 aeImage::GetHeight()
	{
		return m_nHeight;
	}

	inline uint32 aeImage::GetBitsPerPixel()
	{
		return m_nBPP;
	}

	void aeImage::ConvertTo32Bits()
	{
		uint32 BPP = FreeImage_GetBPP((FIBITMAP*)m_pData);
		FIBITMAP* temp = nullptr;
		if (BPP != 32)
			temp = FreeImage_ConvertTo32Bits((FIBITMAP*)m_pData);

		FreeImage_Unload((FIBITMAP*)m_pData);
		m_nBPP = FreeImage_GetBPP(temp);

		m_pData = temp;
	}

	void aeImage::FlipHorizontal()
	{
		FreeImage_FlipHorizontal((FIBITMAP*)m_pData);
	}

	void aeImage::FlipVertical()
	{
		FreeImage_FlipVertical((FIBITMAP*)m_pData);
	}

	inline bool aeImage::IsLoaded()
	{
		return m_pData != nullptr;
	}

	BYTE * aeImage::GetBits()
	{
		return FreeImage_GetBits((FIBITMAP*)m_pData);
	}
}