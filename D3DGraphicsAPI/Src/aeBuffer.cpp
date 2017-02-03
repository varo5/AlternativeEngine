#include "aeGraphicsAPI.h"

namespace aeEngineSDK
{
	aeBuffer::aeBuffer()
	{
		m_pData = ae_new<BUFFER_DATA>();
		m_pData->Buffer = nullptr;
	}

	aeBuffer::aeBuffer(const aeBuffer & B)
	{
		*this = B;
	}

	aeBuffer::~aeBuffer()
	{
		ae_delete(m_pData);
		m_pData = nullptr;
	}

	void aeBuffer::Release()
	{
		SAFE_RELEASE(m_pData->Buffer);
	}
}