#pragma once
#include <aeCoreDefines.h>

/*************************************************************************************************/
/* Windows specific settings
/*************************************************************************************************/
#if AE_PLATFORM == AE_PLATFORM_WIN32
//If we're not including this from a client build, specify that the stuff 
// should get exported.
	#if defined(AE_STATIC_LIB)
		#define AE_GRAPHICS_EXPORT //Linux compilers don't have symbol import
	#else
		#if defined(AE_GRAPHICS_EXPORTS)
			#define AE_GRAPHICS_EXPORT __declspec(dllexport)
		#else
			#if defined(__MINGW32__)
				#define AE_GRAPHICS_EXPORT
			#else
				#define AE_GRAPHICS_EXPORT __declspec( dllimport)
			#endif
		#endif
	#endif
#endif

