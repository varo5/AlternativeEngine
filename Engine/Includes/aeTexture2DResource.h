#pragma once
#include "aeEngineResource.h"

namespace aeEngineSDK
{
	class AE_ENGINE_EXPORT aeTexture2DResource : public aeEngineResource
	{
	private:		
		friend class aeResourceManager;
	public:
		aeTexture2DResource();
		aeTexture2DResource(const aeTexture2DResource& TR);
		~aeTexture2DResource();
	public:
		void Release() override;
		void SetType(AE_TEXTURE_TYPE Type);
		AE_ENGINE_RESOURCE_ID GetID() const override;

		String GetName() const override;
		AE_TEXTURE_TYPE GetType();
	private:
		SPtr<aeTexture2D> m_pTexture;
	};
}