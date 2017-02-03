#include "aeResourceManager.h"

namespace aeEngineSDK
{
	aeMaterial::aeMaterial()
	{
	}

	aeMaterial::aeMaterial(const aeMaterial &M)
	{
		*this = M;
	}

	aeMaterial::~aeMaterial()
	{
	}

	inline String aeMaterial::GetName()
	{
		return m_pszName;
	}

	/*************************************************************************************************/
	/*
	/*************************************************************************************************/

	aeMaterialResource::aeMaterialResource()
	{
	}

	aeMaterialResource::aeMaterialResource(const aeMaterialResource & MR)
	{
		*this = MR;
	}

	aeMaterialResource::~aeMaterialResource()
	{
	}

	void aeMaterialResource::Release()
	{
	}

	AE_ENGINE_RESOURCE_ID aeMaterialResource::GetID() const
	{
		return AE_ENGINE_RESOURCE_ID::AE_ENGINE_RESOURCE_MATERIAL;
	}

	inline String aeMaterialResource::GetName() const
	{
		return m_pMaterial->GetName();
	}
}