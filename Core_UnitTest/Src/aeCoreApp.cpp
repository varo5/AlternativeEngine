#include "aeCoreApp.h"

namespace aeEngineSDK
{
	
	CoreApp::CoreApp()
	{
	}
	CoreApp::CoreApp(const CoreApp & A)
	{
		*this = A;
	}
	CoreApp::~CoreApp()
	{
	}

	AE_RESULT CoreApp::Init()
	{
		m_aImages["basic01"] = new aeImage();

		m_aImages["basic01"]->LoadFromFilePath("..\\Images\\basi0g01.png");

		AE_ASSERT(m_aImages["basic01"]->IsLoaded());

		return 0;
	}
}