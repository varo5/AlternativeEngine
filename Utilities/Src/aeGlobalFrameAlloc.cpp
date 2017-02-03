#include "aePrerequisitesUtil.h"

namespace aeEngineSDK
{
	void * GlobalFrameAlloc::m_pMemory = nullptr;
	AE_THREADLOCAL SIZE_T GlobalFrameAlloc::m_nPos = 0;
	AE_THREADLOCAL SIZE_T GlobalFrameAlloc::m_nSize = 0;
	AE_THREADLOCAL SIZE_T GlobalFrameAlloc::m_nPrevSize = 0;
	Set<SIZE_T> GlobalFrameAlloc::m_aTemporaryMemory = Set<SIZE_T>();
}