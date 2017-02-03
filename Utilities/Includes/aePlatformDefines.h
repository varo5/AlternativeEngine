/*************************************************************************************************/
/* @file	aePlatformDefines.h
/* @author	Alvaro Jesus Estrada Jaime (alvaro.jesus@estradajaime.com)
/* @date	2016/09/13
/*
/* @brief	Declares the platform defines.
/*************************************************************************************************/

#pragma once

/*************************************************************************************************/
/* Initial platform/compiler-related stuff to set. 
/*************************************************************************************************/

#define AE_PLATFORM_WIN32		1		//Windows Platform
#define AE_PLATFORM_LINUX		2		//Linux Platform
#define AE_PLATFORM_APPLE		3		//Apple Platform
#define AE_PLATFORM_PS4			4		//PlayStation 4 Platform

#define AE_COMPILER_MSVC		1		//Visual Studio Compiler
#define AE_COMPILER_GNUC		2		//GCC Compiler
#define AE_COMPILER_INTEL		3		//Intel Compiler
#define AE_COMPILER_CLANG		4		//Clang Compiler

#define AE_ARCHITECTURE_x86_32	1		//Intel x86 32 bits
#define AE_ARCHITECTURE_x86_64	2		//Intel x86 64 bits

#define AE_ENDIAN_LITTLE		1		//Little Endian
#define AE_ENDIAN_BIG			2		//Big Endian

#define AE_EDITOR_BUILD			1

//Define the actual endian type (little endian
#define AE_ENDIAN AE_ENDIAN_LITTLE	



/*************************************************************************************************/
/* Compiler type and version.
/*************************************************************************************************/

#if defined( _MSC_VER )	// Visual Studio
	#define AE_COMPILER AE_COMPILER_MSVC	//Set as Actual Compiler
	#define AE_COMP_VER _MSC_VER	//Compiler Version
	#define AE_THREADLOCAL __declspec(thread)	//Local thread type
#elif defined( __GNUC__ )	//GCC Compiler
	#define AE_COMPILER AE_COMPILER_GNUC	//Set as Actual Compiler
	//Compiler Version	
	#define AE_COMP_VER (((__GNUC__)*100)+(__GNUC_MINOR__*10)+ __GNUC_PATCHLEVEL__)	
	#define AE_THREADLOCAL __thread	//Local thread type													
#elif defined( __INTEL_COMPILER )	//Intel Compiler
	#define AE_COMPILER AE_COMPILER_GNUC	//Set as Actual Compiler	
	#define AE_COMP_VER __INTEL_COMPILER	//Compiler Version	
#elif defined( __clang__ )	//Clang Compiler
	#define AE_COMPILER AE_COMPILER_CLANG	//Set as Actual Compiler	
	#define AE_COMP_VER __clang_major__	//Compiler Version	
	#define AE_THREADLOCAL __thread	//Local thread type
#else
	//No known compiler found, send the error
	#pragma error "No known compiler."	
#endif

/*************************************************************************************************/
/* See if we can use __forceinline or if we need to use __inline instead
/*************************************************************************************************/

#if AE_COMPILER == AE_COMPILER_MSVC	//if we are compiling on visual studio
	#if AE_COMP_VER >= 1200	//if we are on visual studio 6 or higher
		#define FORCEINLINE __forceinline	//Set __forceinline
		#ifndef RESTRICT
			#define RESTRICT __restrict	//No alias hint
		#endif
	#endif
#elif defined(__MINGW32__)	//if we are on a unix type system
#if !defined(FORCEINLINE)
	#define FORCEINLINE __inline	//Set __inline
	#ifndef RESTRICT
		#define RESTRICT	//No alias hint
	#endif
#endif
#else	//Any other compiler
	#define FORCEINLINE __inline	//Set __inline
	#ifndef RESTRICT
		#define RESTRICT __restrict	//No alias hint
	#endif
#endif

/*************************************************************************************************/
/* Finds the current platform
/*************************************************************************************************/
#if defined(__WIN32__) || defined(_WIN32)	//If it's a windows platform
	#define AE_PLATFORM AE_PLATFORM_WIN32
#elif defined(__APPLE_CC__)	//If it's an Apple platform
	#define AE_PLATFORM AE_PLATFORM_APPLE	
#elif defined(__ORBIS__)	//If it's a PlayStation 4
	#define AE_PLATFORM AE_PLATFORM_PS4
#else	//Will consider it as Linux platform
	#define AE_PLATFORM AE_PLATFORM_LINUX
#endif

/*************************************************************************************************/
/* Finds the architecture type
/*************************************************************************************************/
#if defined(__x86_64__) || defined(_M_X64)	//If it's a x64 compile
	#define AE_ARCH_TYPE AE_ARCHITECTURE_x86_64
#else										//If it's a X86 compile
	#define AE_ARCH_TYPE AE_ARCHITECTURE_x86_32	
#endif

/*************************************************************************************************/
/* Memory Alignment macros
/*************************************************************************************************/
#if AE_COMPILER == AE_COMPILER_MSVC	//if we are compiling on visual studio
	#define MS_ALIGN(n) __declspec(align(n))	//Microsoft compatible alignment
	#ifndef GCC_PACK
		#define GCC_PACK(n)	//GCC compatible pack (no needed on Microsoft
	#endif
	#ifndef GCC_ALIGN
		#define GCC_ALIGN(n)	//GCC compatible align (no needed on Microsoft)
	#endif
#elif ( AE_COMPILER == AE_COMPILER_GNUC && AE_PLATFORM == AE_PLATFORM_PS4 )
	#define MS_ALIGN(n)
	#define GCC_PACK(n)//GCCcompatible pack
	#define GCC_ALIGN(n) __attribute__((__aligned__(n)))//GCC compatible align
#else	//If we are on a Unix type system
	#define MS_ALIGN(n)
	#define GCC_PACK(n) __attribute__((packed, aligned(n)))
	#define GCC_ALIGN(n) __attribute__((__aligned__(n)))
#endif

/*************************************************************************************************/
/* For throw override (deprecated on c++11 but visual studio does not handle
/* noexcept
/*************************************************************************************************/
#if AE_COMPILER == AE_COMPILER_MSVC
	#define _NOEXCEPT noexcept
#elif AE_COMPILER == AE_COMPILER_INTEL
	#define _NOEXCEPT noexcept
#elif AE_COMPILER == AE_COMPILER_GNUC
	#define _NOEXCEPT noexcept
#else
	#define _NOEXCEPT
#endif

/*************************************************************************************************/
/* Windows specific settings
/*************************************************************************************************/
#if AE_PLATFORM == AE_PLATFORM_WIN32
	//If we're not including this from a client build, specify that the stuff 
	// should get exported.
	#if defined(AE_STATIC_LIB)
		#define AE_UTILITY_EXPORT //Linux compilers don't have symbol import
	#else
		#if defined(AE_UTILITY_EXPORTS)
			#define AE_UTILITY_EXPORT __declspec(dllexport)
		#else
			#if defined(__MINGW32__)
				#define AE_UTILITY_EXPORT
			#else
				#define AE_UTILITY_EXPORT __declspec( dllimport)
			#endif
		#endif
	#endif
	//Win32 compilers use _DEBUG for specifying debug builds. For MinGW, we 
	// set DEBUG
	#if defined(_DEBUG) || defined(DEBUG)
		#define AE_DEBUG_MODE 1	//Specifies that we are on a DEBUG build
	#else
		#define AE_DEBUG_MODE 0 //We are not on a DEBUG build
	#endif

	#if AE_COMPILER == AE_COMPILER_INTEL
		#define AE_THREADLOCAL __declspec(thread) //Set the windows local thread for the In
	#endif
#endif

/*************************************************************************************************/
/* Linux/Apple specific Settings
/*************************************************************************************************/
#if AE_PLATFORM == AE_PLATFORM_LINUX || AE_PLATFORM == AE_PLATFORM_APPLE
	//Enable GCC symbol visibility
	#if defined(AE_GCC_VISIBILITY)
		#define AE_UTILITY_EXPORT __attribute__ ((visibility("default")))
	#else
		#define AE_UTILITY_EXPORT
	#endif
	
	#define stricmp strcasecmp
	
	//If we are on a DEBUG build
	#if defined(_DEBUG) || defined(DEBUG)
		#define AE_DEBUG_MODE 1 // Specifies that we are on a DEBUG build
	#else
		#define AE_DEBUG_MODE 0 //We are not on a DEBUG build
	#endif
	
	#if AE_COMPILER == AE_COMPILER_INTEL
		#define AE_THREADLOCAL __thread //Set the windows local thread for the In
	#endif 
#endif

/*************************************************************************************************/
/* PS4 specific Settings
/*************************************************************************************************/
#if AE_PLATFORM == AE_PLATFORM_PS4
	//If we're not including this from a client build, specify that the stuff 
	// should get exported.
	#if defined(AE_STATIC_LIB)
		#define AE_UTILITY_EXPORT //Linux compilers don't have symbol import
	#else
		#if defined(AE_UTILITY_EXPORTS)
			#define AE_UTILITY_EXPORT __declspec(dllexport)
		#else
			#if defined(__MINGW32__)
				#define AE_UTILITY_EXPORT
			#else
				#define AE_UTILITY_EXPORT __declspec( dllimport)
			#endif
		#endif
	#endif
	//Win32 compilers use _DEBUG for specifying debug builds. For MinGW, we 
	// set DEBUG
	#if defined(_DEBUG) || defined(DEBUG)
		#define AE_DEBUG_MODE 1	//Specifies that we are on a DEBUG build
	#else
		#define AE_DEBUG_MODE 0 //We are not on a DEBUG build
	#endif
#endif

/*************************************************************************************************/
/* Definition of Debug macros
/*************************************************************************************************/
#if AE_DEBUG_MODE
	#define AE_DEBUG_ONLY(x) x
	//#define AE_ASSERT(x) assert(x)
#else
	#define AE_DEBUG_ONLY(x)
	//#define AE_ASSERT(x)
#endif