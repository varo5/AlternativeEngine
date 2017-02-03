#include "aeResourceManager.h"

namespace aeEngineSDK
{
	aeResourceManager::aeResourceManager()
	{
	}

	aeResourceManager::~aeResourceManager()
	{
	}

	aeResourceManager::aeResourceManager(const aeResourceManager &)
	{
	}

	aeResourceManager & aeResourceManager::operator=(const aeResourceManager &)
	{
		return *this;
	}

	void aeResourceManager::OnStartUp()
	{
	}

	void aeResourceManager::OnShutDown()
	{
	}

	aeModelResource aeResourceManager::LoadModel(const String & FilePath)
	{
		return aeModelResource();
	}

	aeTexture2DResource aeResourceManager::LoadTexture2d(const String & FilePath)
	{
		return aeTexture2DResource();
	}

	void aeResourceManager::LoadResource(const String & FilePath, aeEngineResource * pResource)
	{
	}
}