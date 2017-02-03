#pragma once
#include <aePrerequisitesUtil.h>
#include "aePrerequisitesEngine.h"
#include <aeGraphicsAPI.h>

#include "aeEngineResource.h"
#include "aeTexture2DResource.h"
#include "aeMaterial.h"
#include "aeModel.h"

namespace aeEngineSDK
{
	struct aeResourceManagerNode
	{
		aeEngineResource* pResource;
		uint32 nInstances;
	};

	class AE_ENGINE_EXPORT aeResourceManager : Module<aeResourceManager>
	{
		/*************************************************************************************************/
		/* Constructors
		/*************************************************************************************************/
	public:
		aeResourceManager();
		virtual ~aeResourceManager();

	private:
		aeResourceManager(const aeResourceManager&);
		aeResourceManager& operator=(const aeResourceManager&);

	private:
		void OnStartUp() override;
		void OnShutDown() override;

	private:
		MultiMap<AE_ENGINE_RESOURCE_ID, Map<String, aeResourceManagerNode>> m_aResources;
		
	public:
		aeModelResource LoadModel(const String& FilePath);
		aeTexture2DResource LoadTexture2d(const String& FilePath);
		void LoadResource(const String& FilePath, aeEngineResource* pResource);
	};
}