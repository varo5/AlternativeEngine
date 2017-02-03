#include "aeGraphicsAPI.h"

namespace aeEngineSDK
{
	aeShader::aeShader()
	{
		m_pData = ae_new<SHADER_DATA>();
		m_pData->Blob = nullptr;
		m_pData->Shader = nullptr;
	}

	aeShader::aeShader(const aeShader & S)
	{
		*this = S;
	}

	aeShader::~aeShader()
	{
		ae_delete(m_pData);
	}

	void aeShader::Release()
	{
		SAFE_RELEASE(m_pData->Blob);
	}
}
