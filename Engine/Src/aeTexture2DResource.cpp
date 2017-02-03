#include "aeResourceManager.h"

namespace aeEngineSDK
{
	aeTexture2DResource::aeTexture2DResource()
	{
	}

	aeTexture2DResource::aeTexture2DResource(const aeTexture2DResource &TR)
	{
		*this = TR;
	}

	aeTexture2DResource::~aeTexture2DResource()
	{
	}

	void aeTexture2DResource::Release()
	{
	}

	inline void aeTexture2DResource::SetType(AE_TEXTURE_TYPE Type)
	{
		return m_pTexture->SetType(Type);
	}

	inline AE_ENGINE_RESOURCE_ID aeTexture2DResource::GetID() const
	{
		return AE_ENGINE_RESOURCE_ID::AE_ENGINE_RESOURCE_TEXTURE_2D;
	}

	inline String aeTexture2DResource::GetName() const
	{
		return m_pTexture->GetName();
	}

	inline AE_TEXTURE_TYPE aeTexture2DResource::GetType()
	{
		return m_pTexture->GetType();
	}
}