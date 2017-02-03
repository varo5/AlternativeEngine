#pragma once
#include <aeApplication.h>
#include <aeImage.h>

namespace aeEngineSDK
{
	class CoreApp : public aeApplication
	{
	protected:
		Map<String, aeImage*> m_aImages;

		AE_RESULT Init() override;
	public:
		CoreApp();
		CoreApp(const CoreApp& A);
		virtual ~CoreApp();
	};
}