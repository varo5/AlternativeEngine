/*************************************************************************************************/
/* @file	aePlatformTypes.h
/* @author	Alvaro Jesus Estrada Jaime (alvaro.jesus@estradajaime.com)
/* @date	2016/09/15
/*
/* @brief	Declares the platform types.
/*************************************************************************************************/

#pragma once

/*************************************************************************************************/
/* Includes
/*************************************************************************************************/

#if AE_PLATFORM == AE_PLATFORM_PS4
	#include <scebase.h>
#endif

namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* Basic Unsigned Types
	/*************************************************************************************************/
	typedef unsigned char		uint8;		// 8-bit unsigned
	typedef unsigned short		uint16;		// 16-bit unsigned
	typedef unsigned int		uint32;		// 32-bit unsigned
#if AE_COMPILER == AE_COMPILER_MSVC
	typedef unsigned __int64	uint64;		// 64-bit unsigned
#else
	typedef unsigned long long		uint64;		// 64 - bit unsigned
#endif
	
	/*************************************************************************************************/
	/* Basic Signed Types
	/*************************************************************************************************/
	typedef char		int8;		// 8-bit signed
	typedef short		int16;		// 16-bit signed
	typedef int			int32;		// 32-bit signed
#if AE_COMPILER == AE_COMPILER_MSVC
	typedef __int64		int64;		// 64-bit signed
#else
	typedef long long		int64;		// 64 - bit signed
#endif

	/*************************************************************************************************/
	/* @class	QWord
	/*
	/* @brief	A 128-bit storage.
	/*************************************************************************************************/
	MS_ALIGN(16) class AE_UTILITY_EXPORT QWord
	{
	public:
		uint64	m_lower;	//The lower 64 bits of the 128 bit integers
		int64	m_upper;	//The upper 64 bits of the 128 bit integers

		/*************************************************************************************************/
		/* @fn	operator QWord::int64 () const
		/*
		/* @brief	Cast that converts the given  to an int64.
		/*
		/* @return	The result of the operation.
		/*************************************************************************************************/

		operator int64 () const
		{
			return m_lower;
		}

		/*************************************************************************************************/
		/* @fn	QWord::QWord()
		/*
		/* @brief	Default constructor.
		/*************************************************************************************************/

		QWord() : m_lower(0), m_upper(0)
		{

		}

		/*************************************************************************************************/
		/* @fn	QWord::QWord(bool from)
		/*
		/* @brief	The constructor for the QWord class for constructing from a bool value.
		/*
		/* @param	from	The value to construct from.
		/*************************************************************************************************/

		QWord(bool from) : m_lower(from), m_upper(0)
		{

		}

		/*************************************************************************************************/
		/* @fn	QWord::QWord(uint8 from)
		/*
		/* @brief	The constructor for the QWord class for constructing from a uint8 value.
		/*
		/* @param	from	The value to construct from.
		/*************************************************************************************************/

		QWord(uint8 from) : m_lower(from), m_upper(0)
		{

		}

		/*************************************************************************************************/
		/* @fn	QWord::QWord(uint16 from)
		/*
		/* @brief	The constructor for the QWord class for constructing from a uint16 value.
		/*
		/* @param	from	The value to construct from.
		/*************************************************************************************************/

		QWord(uint16 from) : m_lower(from), m_upper(0)
		{

		}

		/*************************************************************************************************/
		/* @fn	QWord::QWord(uint32 from)
		/*
		/* @brief	The constructor for the QWord class for constructing from a uint32 value.
		/*
		/* @param	from	The value to construct from.
		/*************************************************************************************************/

		QWord(uint32 from) : m_lower(from), m_upper(0)
		{

		}

		/*************************************************************************************************/
		/* @fn	QWord::QWord(uint64 from)
		/*
		/* @brief	The constructor for the QWord class for constructing from a uint64 value.
		/*
		/* @param	from	The value to construct from.
		/*************************************************************************************************/

		QWord(uint64 from) : m_lower(from), m_upper(0)
		{

		}

		/*************************************************************************************************/
		/* @fn	QWord::QWord(float from)
		/*
		/* @brief	The constructor for the QWord class for constructing from a float value.
		/*
		/* @param	from	The value to construct from.
		/*************************************************************************************************/

		QWord(float from) : m_lower((uint64)from), m_upper(0)
		{

		}

		/*************************************************************************************************/
		/* @fn	QWord::QWord(double from)
		/*
		/* @brief	The constructor for the QWord class for constructing from a double value.
		/*
		/* @param	from	The value to construct from.
		/*************************************************************************************************/

		QWord(double from) : m_lower((uint64)from), m_upper(0)
		{

		}
	} GCC_ALIGN(16);

	typedef QWord int128;	//Signed 128 bit integer.
	typedef QWord uint128;	//Unsigned 128 bit integer.

	/*************************************************************************************************/
	/* Character Types
	/*************************************************************************************************/
#if AE_COMPILER == AE_COMPILER_MSVC || AE_COMPILER == AE_COMPILER_PS4
	typedef wchar_t				WCHAR;		//Wide character (used by visual studio)
#else
	typedef unsigned short		WCHAR;		//Wide character (Any other compiler)
#endif
	typedef char				ANSICHAR;	//ANSI character type
	typedef WCHAR				UNICHAR;	//UNICODE character type

	/*************************************************************************************************/
	/* NULL data type
	/*************************************************************************************************/
	typedef int32				TYPE_OF_NULL;	

	/*************************************************************************************************/
	/* Basic data type
	/*************************************************************************************************/
	typedef uint8				BYTE;

	/*************************************************************************************************/
	/* TIME_T is a definition dependent data type
	/*************************************************************************************************/
#ifdef _USE_32BIT_TIME_T
	typedef int32			TIME_T;
#else
	#if ((AE_ARCH_TYPE == AE_ARCHITECTURE_x86_64) && (AE_COMPILER == AE_COMPILER_MSVC))
		typedef __int64		TIME_T;
	#else
		typedef long long	TIME_T;
	#endif
#endif

	/*************************************************************************************************/
	/* SIZE_T is an architecture dependent data type
	/*************************************************************************************************/
#if ((AE_ARCH_TYPE == AE_ARCHITECTURE_x86_64) && (AE_COMPILER == AE_COMPILER_MSVC))
	typedef unsigned __int64	SIZE_T;
#else
	typedef unsigned long long	SIZE_T;
#endif

	/*************************************************************************************************/
	/* Basic data type
	/*************************************************************************************************/
	typedef SIZE_T				AE_RESULT;
}
