#include "aeGraphicsAPI.h"

namespace aeEngineSDK
{
	aeTexture2D::aeTexture2D()
	{
		m_pData = ae_new<TEXTURE2D_DATA>();
		m_pData->Texture = nullptr;
		m_xType = AE_TEXTURE_TYPE::AE_TEXTURE_TYPE_DIFFUSE;
	}

	aeTexture2D::aeTexture2D(const aeTexture2D & T)
	{
	}

	aeTexture2D::~aeTexture2D()
	{
		ae_delete(m_pData);
	}

	void aeTexture2D::Release()
	{
		SAFE_RELEASE(m_pData->Texture);
	}

	inline void aeTexture2D::SetType(AE_TEXTURE_TYPE Type)
	{
		m_xType = Type;
	}

	inline String aeTexture2D::GetName() const
	{
		return m_pszName;
	}

	inline AE_TEXTURE_TYPE aeTexture2D::GetType()
	{
		return m_xType;
	}

}