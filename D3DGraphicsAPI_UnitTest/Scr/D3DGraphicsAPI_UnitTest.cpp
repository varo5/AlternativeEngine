#include <WinApplication.h>

#ifdef main
#undef main
#endif

int main()
{
	aeEngineSDK::WinApplication App;

	aeEngineSDK::AE_RESULT Res;

	AE_ASSERT((Res = App.Run()) == 0);

	return Res;
}