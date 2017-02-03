#pragma once

namespace aeEngineSDK
{
	class AE_GRAPHICS_EXPORT aeGraphicsResource
	{
	public:
		aeGraphicsResource() {}
		virtual ~aeGraphicsResource() {}

	public:
		virtual void Release() = 0;
	};
}
