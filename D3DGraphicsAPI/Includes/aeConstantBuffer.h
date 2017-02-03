#pragma once

namespace aeEngineSDK
{
	class AE_GRAPHICS_EXPORT aeConstantBuffer : public aeBuffer
	{
	protected:
		aeConstantBuffer();

		friend class aeGraphicsAPI;
		friend class aeRenderer;
	public:
		aeConstantBuffer(const aeConstantBuffer& B);
		virtual ~aeConstantBuffer();
	};
}
