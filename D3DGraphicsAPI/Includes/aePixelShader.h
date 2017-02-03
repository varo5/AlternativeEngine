#pragma once

namespace aeEngineSDK
{
	class AE_GRAPHICS_EXPORT aePixelShader : public aeShader
	{
	protected:
		aePixelShader();

		friend class aeGraphicsAPI;
		friend class aeRenderer;
	public:
		aePixelShader(const aePixelShader& S);
		virtual ~aePixelShader();

		void Release();
	};
}
