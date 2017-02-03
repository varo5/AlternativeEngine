#pragma once

namespace aeEngineSDK
{
	class AE_GRAPHICS_EXPORT aeVertexShader : public aeShader
	{
	protected:
		aeVertexShader();

		friend class aeGraphicsAPI;
		friend class aeRenderer;
	public:
		aeVertexShader(const aeVertexShader& S);
		virtual ~aeVertexShader();

		void Release();
	};
}
