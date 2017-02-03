#pragma once

namespace aeEngineSDK
{
	class AE_GRAPHICS_EXPORT aeInputLayout : public aeGraphicsResource
	{
	protected:
		aeInputLayout();

		INPUTLAYOUT_DATA* m_pData;

		friend class aeGraphicsAPI;
		friend class aeRenderer;
	public:
		aeInputLayout(const aeInputLayout& S);
		virtual ~aeInputLayout();

		void Release();
	};
}