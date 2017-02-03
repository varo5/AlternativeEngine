#pragma once

namespace aeEngineSDK
{
	class AE_GRAPHICS_EXPORT aeBuffer : public aeGraphicsResource
	{
	protected:
		aeBuffer();

		BUFFER_DATA* m_pData;

		friend class aeGraphicsAPI;
		friend class aeRenderer;
	public:
		aeBuffer(const aeBuffer& B);
		virtual ~aeBuffer();

		void Release();
	};
}
