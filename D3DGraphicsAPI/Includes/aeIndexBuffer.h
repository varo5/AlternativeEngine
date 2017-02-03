#pragma once

namespace aeEngineSDK
{
	class AE_GRAPHICS_EXPORT aeIndexBuffer : public aeBuffer
	{
	protected:
		aeIndexBuffer();

		friend class aeGraphicsAPI;
	public:
		aeIndexBuffer(const aeIndexBuffer& B);
		virtual ~aeIndexBuffer();
	};
}