#include "aeGraphicsAPI.h"

namespace aeEngineSDK
{
	aeVertexShader::aeVertexShader()
	{
		m_pData = ae_new<SHADER_DATA>();
		m_pData->Blob = nullptr;
		m_pData->Shader = nullptr;
	}

	aeVertexShader::aeVertexShader(const aeVertexShader & S)
	{
		*this = S;
	}

	aeVertexShader::~aeVertexShader()
	{
		ae_delete(m_pData);
	}

	void aeVertexShader::Release()
	{
		SAFE_RELEASE(m_pData->Blob);
		((ID3D11VertexShader*)m_pData->Shader)->Release();
		m_pData->Shader = nullptr;
	}
}