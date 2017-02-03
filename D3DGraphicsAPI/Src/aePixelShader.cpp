#include "aeGraphicsAPI.h"

namespace aeEngineSDK
{
	aePixelShader::aePixelShader()
	{
		m_pData = ae_new<SHADER_DATA>();
		m_pData->Blob = nullptr;
		m_pData->Shader = nullptr;
	}

	aePixelShader::aePixelShader(const aePixelShader & S)
	{
		*this = S;
	}

	aePixelShader::~aePixelShader()
	{
		ae_delete(m_pData);
	}

	void aePixelShader::Release()
	{
		SAFE_RELEASE(m_pData->Blob);
		((ID3D11PixelShader*)m_pData->Shader)->Release();
		m_pData->Shader = nullptr;
	}
}