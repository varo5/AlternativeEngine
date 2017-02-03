#pragma once

namespace aeEngineSDK
{
	class AE_GRAPHICS_EXPORT aeVertexBuffer : public aeBuffer
	{
	protected:
		aeVertexBuffer();

		friend class aeGraphicsAPI;
		friend class aeRenderer;
	public:
		aeVertexBuffer(const aeVertexBuffer& B);
		virtual ~aeVertexBuffer();
	};
}
