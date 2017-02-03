#include "aeGraphicsAPI.h"

namespace aeEngineSDK
{
	aeInputLayout::aeInputLayout()
	{
		m_pData = ae_new<INPUTLAYOUT_DATA>();
		m_pData->InputLayout = nullptr;
	}

	aeInputLayout::aeInputLayout(const aeInputLayout & S)
	{
		*this = S;
	}

	aeInputLayout::~aeInputLayout()
	{
		ae_delete(m_pData);
		m_pData = nullptr;
	}

	void aeInputLayout::Release()
	{
		SAFE_RELEASE(m_pData->InputLayout);
	}
}