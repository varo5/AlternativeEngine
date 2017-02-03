#pragma once
#include <aeCoreDefines.h>

/*************************************************************************************************/
/* Export specific settings
/*************************************************************************************************/
#if AE_PLATFORM == AE_PLATFORM_WIN32
	//If we're not including this from a client build, specify that the stuff 
	// should get exported.
	#if defined(AE_STATIC_LIB)
		#define AE_ENGINE_EXPORT //Linux compilers don't have symbol import
	#else
		#if defined(AE_ENGINE_EXPORTS)
			#define AE_ENGINE_EXPORT __declspec(dllexport)
		#else
			#if defined(__MINGW32__)
				#define AE_ENGINE_EXPORT
			#else
				#define AE_ENGINE_EXPORT __declspec( dllimport)
			#endif
		#endif
	#endif
#endif
