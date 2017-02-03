#pragma once
#include "aePrerequisitesEngine.h"
#include <aeApplication.h>

namespace aeEngineSDK
{
	struct WinAppData;

	class AE_ENGINE_EXPORT WinApplication : public aeApplication
	{
	protected:
		AE_RESULT Init() override;
		AE_RESULT StatusUptade() override;
		void Render() override;
		void Destroy() override;

		WinAppData* m_pData;
	public:
		WinApplication(String& AppName);
		WinApplication(const WinApplication& A);
		virtual ~WinApplication();

		void Resize(uint32 X, uint32 Y) override;
		void Stop() override;
	};
}