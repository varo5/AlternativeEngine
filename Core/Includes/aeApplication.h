#pragma once
#include "aePrerequisitesCore.h"
#include <aePrerequisitesUtil.h>

namespace aeEngineSDK
{
	class AE_CORE_EXPORT aeApplication
	{
	protected:
		virtual AE_RESULT Init();
		virtual AE_RESULT StatusUptade();
		virtual void Render();
		virtual void Logic();
		virtual void Destroy();
	public:
		aeApplication();
		aeApplication(const aeApplication& A); 
		virtual ~aeApplication();

		virtual AE_RESULT Run();

		virtual void Resize(uint32 X, uint32 Y);
		virtual void Stop();
	};
}