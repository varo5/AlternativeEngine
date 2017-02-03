#pragma once

#if AE_COMPILER ==  AE_COMPILER_MSVC
#undef __PRETTY_FUNCTION__
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

namespace aeEngineSDK
{
#if AE_COMPILER ==  AE_COMPILER_MSVC
	#pragma warning( push )
	#pragma  warning(disable : 4275)
#endif

	class AE_UTILITY_EXPORT aeException : public std::exception
	{
	public:

		aeException() throw() : std::exception()
		{
		}

		explicit aeException(char const* const _Message) throw() : std::exception(_Message)
		{

		}

		aeException(char const* const _Message, int) throw() : std::exception(_Message,1)
		{
		}

		aeException(aeException const& _Other) throw() : std::exception(_Other)
		{
		}

		virtual ~aeException() throw()
		{
		}
	};

	class AE_UTILITY_EXPORT  InternalErrorException : public aeException
	{
	public:

		InternalErrorException() throw() : aeException("Internal error exception", 1)
		{
		}

	};

}
#if defined(_DEBUG)
#define AE_EXCEPT(Except,Msg) \
	MULTI_LINE_MACRO_BEGIN \
	Except(); \
	MULTI_LINE_MACRO_END
#else
#define AE_EXCEPT(Except,Msg) MULTI_LINE_MACRO_BEGIN Except(); MULTI_LINE_MACRO_END
#endif