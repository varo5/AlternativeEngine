#pragma once
#include <aePlatformDefines.h>

/*************************************************************************************************/
/* Windows specific settings
/*************************************************************************************************/
#if AE_PLATFORM == AE_PLATFORM_WIN32
//If we're not including this from a client build, specify that the stuff 
// should get exported.
	#if defined(AE_STATIC_LIB)
		#define AE_CORE_EXPORT //Linux compilers don't have symbol import
	#else
		#if defined(AE_CORE_EXPORTS)
			#define AE_CORE_EXPORT __declspec(dllexport)
		#else
			#if defined(__MINGW32__)
				#define AE_CORE_EXPORT
			#else
				#define AE_CORE_EXPORT __declspec( dllimport)
			#endif
		#endif
	#endif
#endif

/*************************************************************************************************/
/* Linux/Apple specific Settings
/*************************************************************************************************/
#if AE_PLATFORM == AE_PLATFORM_LINUX || AE_PLATFORM == AE_PLATFORM_APPLE
//Enable GCC symbol visibility
	#if defined(AE_GCC_VISIBILITY)
		#define AE_CORE_EXPORT __attribute__ ((visibility("default")))
	#else
		#define AE_CORE_EXPORT
	#endif
#endif

/*************************************************************************************************/
/* PS4 specific Settings
/*************************************************************************************************/
#if AE_PLATFORM == AE_PLATFORM_PS4
//If we're not including this from a client build, specify that the stuff 
// should get exported.
	#if defined(AE_STATIC_LIB)
		#define AE_CORE_EXPORT //Linux compilers don't have symbol import
	#else
		#if defined(AE_CORE_EXPORTS)
			#define AE_CORE_EXPORT __declspec(dllexport)
		#else
		#if defined(__MINGW32__)
			#define AE_CORE_EXPORT
		#else
			#define AE_CORE_EXPORT __declspec( dllimport)
		#endif
	#endif
	#endif
#endif
