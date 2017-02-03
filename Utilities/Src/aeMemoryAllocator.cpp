#include "aePrerequisitesUtil.h"

namespace aeEngineSDK
{
	AE_THREADLOCAL uint64 MemoryCounter::m_Allocs = 0;
	AE_THREADLOCAL uint64 MemoryCounter::m_Frees = 0;
}