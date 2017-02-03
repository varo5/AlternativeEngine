#pragma once

namespace aeEngineSDK
{
	class AE_GRAPHICS_EXPORT aeShader : public aeGraphicsResource
	{
	protected:
		aeShader();
		
		SHADER_DATA* m_pData;

		friend class aeGraphicsAPI;
	public:
		aeShader(const aeShader& S);
		virtual ~aeShader();

		virtual void Release();
	};
}
