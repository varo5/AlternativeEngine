#include "aeCriticalSection.h"

namespace aeEngineSDK
{
	struct CRITICAL_SECTION_DATA
	{
		std::mutex Lock;
	};

	aeCriticalSection::aeCriticalSection()
	{
		m_pData = ae_new<CRITICAL_SECTION_DATA>();
	}

	aeCriticalSection::~aeCriticalSection()
	{
		ae_delete(m_pData);
	}

	void aeCriticalSection::Lock()
	{
		m_pData->Lock.lock();
	}

	void aeCriticalSection::Unlock()
	{
		m_pData->Lock.unlock();
	}

	bool aeCriticalSection::TryLock()
	{
		return m_pData->Lock.try_lock();
	}
}