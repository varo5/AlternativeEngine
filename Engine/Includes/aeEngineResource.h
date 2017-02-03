#pragma once

namespace aeEngineSDK
{
	enum struct AE_ENGINE_RESOURCE_ID : uint32
	{
		AE_ENGINE_RESOURCE_TEXTURE_2D,
		AE_ENGINE_RESOURCE_MATERIAL,
		AE_ENGINE_RESOURCE_MODEL
	};

	class AE_ENGINE_EXPORT aeEngineResource
	{
	public:
		aeEngineResource() {}
		aeEngineResource(const aeEngineResource& Resource) { *this = Resource; }
		virtual ~aeEngineResource() {}
	public:
		virtual void Release() {}
		virtual AE_ENGINE_RESOURCE_ID GetID() const = 0;
		virtual String GetName() const = 0;
	};
}
