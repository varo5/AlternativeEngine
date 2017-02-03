#pragma once
#include "aeTexture2DResource.h"

namespace aeEngineSDK
{
	struct aeMaterialProperty
	{
	};

	class AE_ENGINE_EXPORT aeMaterial
	{
	private:
		friend class aeResourceManager;
	public:
		aeMaterial();
		aeMaterial(const aeMaterial& M);
		~aeMaterial();
		
		String GetName();
	private:
		Vector<aeTexture2DResource> m_aTextures;
		Vector<aeMaterialProperty*> m_aProperties;

		String m_pszName;
	};

	class AE_ENGINE_EXPORT aeMaterialResource : public aeEngineResource
	{
	private:
		friend class aeResourceManager;
	public:
		aeMaterialResource();
		aeMaterialResource(const aeMaterialResource& MR);
		~aeMaterialResource();
	public:
		void Release() override;
		AE_ENGINE_RESOURCE_ID GetID() const override;

		String GetName() const override;
	private:
		SPtr<aeMaterial> m_pMaterial;
	};
}