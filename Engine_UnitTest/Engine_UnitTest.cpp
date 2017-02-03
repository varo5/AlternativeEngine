#include <WinApplication.h>
#include <aePrerequisitesUtil.h>
#include <aeTime.h>

#ifdef main
#undef main
#endif

int main(int argc, char** argv)
{
#if _DEBUG
	aeEngineSDK::String S = argv[0];
	S.push_back(0);
	aeEngineSDK::WinApplication App(S);

	aeEngineSDK::AE_RESULT Res;

	AE_ASSERT((Res = App.Run()) == 0);

	return Res;
#else
	aeEngineSDK::String S = argv[0];
	S.push_back(0);
	aeEngineSDK::WinApplication App(S);

	return App.Run();
#endif
	
}