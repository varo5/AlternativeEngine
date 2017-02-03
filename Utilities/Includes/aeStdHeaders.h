/*************************************************************************************************/
/* @file	aeStdHeadersh.h
/*
/* @brief	Declares the standard headers class.
/*************************************************************************************************/

#pragma once

/*************************************************************************************************/
/* If we are on a Borland compiler (C++ Builder)
/*************************************************************************************************/
#ifdef __BORLANDC__
	#define __STD_ALGORITHM
#endif

/*************************************************************************************************/
/* C type objects
/*************************************************************************************************/
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdarg>
#include <cmath>

/*************************************************************************************************/
/* For memory management
/*************************************************************************************************/
#include <memory>

/*************************************************************************************************/
/* For memory management
/*************************************************************************************************/
#include <thread>
#include <mutex>

/*************************************************************************************************/
/* STL Containers
/*************************************************************************************************/
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <set>
#include <list>
#include <deque>
#include <queue>
#include <bitset>
#include <array>

/*************************************************************************************************/
/* Note - not in the original STL, but exists in SGI STL and STLport
/* For GCC 4.3 see http://gcc.gnu.org/gcc-4.3/changes.html
/*************************************************************************************************/
#if (AE_COMPILER == AE_COMPILER_GNUC)
	#if AE_COMP_VER >= 430
		#include <tra/unordered_map>
		#include <tra/unordered_set>
	#elif (AE_PLATFORM == AE_PLATFORM_PS4)
		#include <unordered_map>
		#include <unordered_set>
	#else 
		#include <ext/hash_map>
		#include <ext/hash_set>
	#endif
#else
	#if (AE_COMPILER == AE_COMPILER_MSVC) && AE_COMP_VER >= 1600 //VC++ 10.0 or higher
		#include <unordered_map>
		#include <unordered_set>
	#else 
		#include <hash_map>
		#include <hash_set>
	#endif
#endif

/*************************************************************************************************/
/* STL algorithms & functions
/*************************************************************************************************/
#include <algorithm>
#include <functional>
#include <limits>

/*************************************************************************************************/
/* C++ Stream stuff
/*************************************************************************************************/
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

#ifdef __BORLANDC__
	namespace aeEngineSDK
	{
		using namespace std;
	}
#endif

/*************************************************************************************************/
/* C Types and Stats
/*************************************************************************************************/
extern "C"
{
	#include <sys/types.h>
	#include <sys/stat.h>
}

/*************************************************************************************************/
/* Windows specifics
/*************************************************************************************************/
#if (AE_PLATFORM == AE_PLATFORM_WIN32)
	//Undefine min & max
	#undef min
	#undef max

	#if !defined(NOMINMAX) && defined(_MSC_VER)
		#define  NOMINMAX //Required to stop windows.h messing up std::min
	#endif
	#if defined(__MINGW32__)
		#include <unistd.h>
	#endif
#endif

/*************************************************************************************************/
/* Linux specifics
/*************************************************************************************************/
#if (AE_PLATFORM == AE_PLATFORM_LINUX)
	extern "C"
	{
		#include <unistd.h>
		#include <dlfcn.h>
	}
#endif

/*************************************************************************************************/
/* Apple specifics
/*************************************************************************************************/
#if (AE_PLATFORM == AE_PLATFORM_APPLE)
	extern "C"
	{
		#include <unistd.h>
		#include <sys/param.h>
		#include <CoreFoundation/CoreFoundation.h>
	}
#endif

/*************************************************************************************************/
/* PlayStation 4 specifics
/*************************************************************************************************/
#if (AE_PLATFORM == AE_PLATFORM_PS4)
	extern "C"
	{
		#include <unistd.h>
		#include <sys/param.h>
	}
#endif

namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* Standard containers, for easier access in my own namespace
	/*************************************************************************************************/
	template <typename A, typename B>
	using Pair = std::pair<A, B>;

	template <typename T>
	using Less = std::less<T>;
	
	template <typename T, typename A = StdAlloc<T>>
	using Deque = std::deque<T, A>;

	template <typename T, typename A = StdAlloc<T>>
	using Vector = std::vector<T, A>;

	template <typename T, typename A = StdAlloc<T>>
	using List = std::list<T, A>;

	template <typename T, typename A = StdAlloc<T>>
	using Stack = std::stack<T, std::deque<T,A>>;

	template <typename T, typename A = StdAlloc<T>>
	using Queue = std::queue<T, std::deque<T, A>>;	

	template <typename T, typename P = std::less<T>, typename A = StdAlloc<T>>
	using Set = std::set<T, P, A>;

	template <typename K, typename V, typename P = std::less<K>, typename A = StdAlloc<std::pair<const K,V>>>
	using Map = std::map<K, V, P, A>;

	template <typename K, typename V, typename P = std::less<K>, typename A = StdAlloc<std::pair<const K, V>>>
	using MultiMap = std::multimap<K, V, P, A>;

	template <typename T, typename H = std::hash<T>, typename C = std::equal_to<T>, typename A = StdAlloc<T>>
	using UnorderedSet = std::unordered_set<T, H, C, A>;

	template <typename K, typename V, typename H = std::hash<K>, typename C = std::equal_to<K>, typename A = StdAlloc<std::pair<const K, V>>>
	using UnorderedMap = std::unordered_map<K, V, H, C, A>;

	template <typename K, typename V, typename H = std::hash<K>, typename C = std::equal_to<K>, typename A = StdAlloc<std::pair<const K, V>>>
	using UnorderedMultimap = std::unordered_multimap<K, V, H, C, A>;

	/*************************************************************************************************/
	/* Smart pointer that retains shared ownership of a project through a pointer. The pointer 
	/* automatically when the last shared pointer to the object is destroyed.
	/*************************************************************************************************/
	template <typename T>
	using SPtr = std::shared_ptr<T>;

	/*************************************************************************************************/
	/* Smart pointer that retains shared ownership of a project through a pointer. Reference unique. 
	/* The object is destroyed automatically when the las shared pointer to the object is destroyed.
	/*************************************************************************************************/

	template <typename T, typename Alloc = GenAlloc>
	using UPtr = std::unique_ptr < T, decltype(&ae_delete<T, Alloc>)>;

	/*************************************************************************************************/
	/* Create a new shared pointer using a custom allocator category. 
	/*************************************************************************************************/
	template<class Type, class AllocCategory, class... Args>
	SPtr<Type> ae_shared_ptr_new(Args&&... args)
	{
		return std::allocate_shared<Type>(StdAlloc<Type, AllocCategory>(), std::forward<Args>(args)...);
	}

	/*************************************************************************************************/
	/* Create a new shared pointer using the default allocator category.
	/*************************************************************************************************/
	template<class Type, class... Args>
	SPtr<Type> ae_shared_ptr_new(Args&&... args)
	{
		return std::allocate_shared<Type>(StdAlloc<Type, GenAlloc>(), std::forward<Args>(args)...);
	}

	/*************************************************************************************************/
	/* Create a new shared pointer from a previously constructed object. Pointer specific data will 
	/* be allocated using the provided allocator category.
	/*************************************************************************************************/
	template<class Type, class MainAlloc = GenAlloc, class PtrDataAlloc = GenAlloc>
	SPtr<Type> ae_shared_ptr(Type* data)
	{
		return std::shared_ptr<Type>(data, &ae_delete<Type, MainAlloc>, StdAlloc<Type, PtrDataAlloc>());
	}

	/*************************************************************************************************/
	/* Create a new unique pointer from a previously constructed object. Pointer specific data will 
	/* be allocated using the provided allocator category.
	/*************************************************************************************************/
	template<class Type, class Alloc = GenAlloc>
	UPtr<Type> ae_unique_ptr(Type* data)
	{
		return std::unique_ptr<Type, decltype(&ae_delete<Type,Alloc>)>(data, ae_delete<Type, Alloc>);
	}

	/*************************************************************************************************/
	/* Create a new unique pointer using a custom allocator category.
	/*************************************************************************************************/
	template<class Type, class Alloc, class... Args>
	UPtr<Type> ae_unique_ptr_new(Args &&... args)
	{
		Type* rawPtr = ae_new<Type, Alloc>(std::forward<Args>(args)...);
		return ae_unique_ptr<Type, Alloc>(rawPtr);
	}

	/*************************************************************************************************/
	/* Create a new unique pointer using the default allocator category.
	/*************************************************************************************************/
	template<class Type, class... Args>
	UPtr<Type> ae_unique_ptr_new(Args &&... args)
	{
		Type* rawPtr = ae_new<Type, GenAlloc>(std::forward<Args>(args)...);
		return ae_unique_ptr<Type, GenAlloc>(rawPtr);
	}
}

namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* Standard numeric limits, for easier access in my own namespace
	/*************************************************************************************************/
	template<typename T>
	using NumericLimits = std::numeric_limits<T>;


	template <typename T, typename M>
	struct GenericComparator
	{
		typedef  M (T::*GETTER)() const;
		GETTER m_getterFunc;
		M m_data;
		GenericComparator(GETTER getterFunc, M data)
		{
			m_getterFunc = getterFunc;
			m_data = data;
		}
		bool operator()(const T  & obj)
		{
			if ((obj.*m_getterFunc)() == m_data)
				return true;
			else
				return false;
		}
	};
}

namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* Function related mask
	/*************************************************************************************************/
	template<class ResultType, class... Args>
	using Function = std::function<ResultType(Args ...)>;

	template <class Function, class... Args>
	void Wrapper(Function(*f)(Args...), Args&&... a) 
	{
		f(std::forward<Args>(a)...);
	}

	template<class ITT, class COMP> inline
	void Sort(ITT First, ITT Last, COMP Pred)
	{	// order [_First, _Last), using _Pred
		_DEBUG_RANGE(First, Last);
		_Sort_unchecked(_Unchecked(First), _Unchecked(Last), Pred);
	}

	template<class ITT> inline
	void Sort(ITT First, ITT Last)
	{	// order [_First, _Last), using operator<
		_STD sort(First, Last, less<>());
	}

	template<class ITT> inline
	void Reverse(ITT First, ITT Last)
	{	// reverse elements in [_First, _Last)
		_DEBUG_RANGE(First, Last);
		_Reverse_unchecked(_Unchecked(First), _Unchecked(Last));
	}

	template<class ITT, class COMP> inline
	ITT FindIf(ITT First, ITT Last, COMP Pred)
	{	// find first satisfying _Pred
		_DEBUG_RANGE_PTR(First, Last, Pred);
		return (_Rechecked(First,
			_Find_if_unchecked(_Unchecked(First), _Unchecked(Last), Pred)));
	}
}

namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* Thread related functions
	/*************************************************************************************************/
	template <class T>
	void SleepFor(const T& SleepDuration)
	{
		std::this_thread::sleep_for(std::chrono::nanoseconds(uint32(SleepDuration * 1000000000)));
	}
}

namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* Standard froward mask
	/*************************************************************************************************/
	// TEMPLATE CLASS remove_reference
	template<class T>
	struct remove_reference
	{	// remove reference
		typedef T type;
	};

	template<class T>
	struct remove_reference<T&>
	{	// remove reference
		typedef T type;
	};

	template<class T>
	struct remove_reference<T&&>
	{	// remove rvalue reference
		typedef T type;
	};

	// TEMPLATE FUNCTION forward
	template<class T> inline
		constexpr T&& Forward(typename remove_reference<T>::type& Arg) _NOEXCEPT
	{ // forward an lvalue as either an lvalue or an rvalue
		return (static_cast<T&&>(Arg));
	}

	template<class T> inline
		constexpr T&& Forward(typename remove_reference<T>::type&& Arg) _NOEXCEPT
	{	// forward an rvalue as an rvalue
		static_assert(!is_lvalue_reference<T>::value, "bad forward call");
		return (static_cast<T&&>(Arg));
	}
}

/*************************************************************************************************/
/* TThis define helps macro declaration for multiple lines of code
/*************************************************************************************************/
#define MULTI_LINE_MACRO_BEGIN do{
#define MULTI_LINE_MACRO_END \
	__pragma(warning(push)) \
	__pragma(warning(disable:4127)) \
	} while(0) \
	__pragma(warning(pop))

//Storing for possible future use
/*
namespace aeEngineSDK
{
	
	// For generic types that are functors, delegate to its 'operator()'
	template <typename T>
	struct function_traits
	: public function_traits<decltype(&T::operator())>
	{};

	// for pointers to member function
	template <typename ClassType, typename ReturnType, typename... Args>
	struct function_traits<ReturnType(ClassType::*)(Args...) const> {
	enum { arity = sizeof...(Args) };
	typedef std::function<ReturnType(Args...)> f_type;
	};

	// for pointers to member function
	template <typename ClassType, typename ReturnType, typename... Args>
	struct function_traits<ReturnType(ClassType::*)(Args...) > {
	enum { arity = sizeof...(Args) };
	typedef std::function<ReturnType(Args...)> f_type;
	};

	// for function pointers
	template <typename ReturnType, typename... Args>
	struct function_traits<ReturnType(*)(Args...)> {
	enum { arity = sizeof...(Args) };
	typedef std::function<ReturnType(Args...)> f_type;
	};

	template <typename L>
	static typename function_traits<L>::f_type make_function(L l) {
	return (typename function_traits<L>::f_type)(l);
	}

	//handles bind & multiple function call operator()'s
	template<typename ReturnType, typename... Args, class T>
	auto make_function(T&& t)
	-> std::function<decltype(ReturnType(t(std::declval<Args>()...)))(Args...)>
	{
	return{ std::forward<T>(t) };
	}

	//handles explicit overloads
	template<typename ReturnType, typename... Args>
	auto make_function(ReturnType(*p)(Args...))
	-> std::function<ReturnType(Args...)> {
	return{ p };
	}

	//handles explicit overloads
	template<typename ReturnType, typename... Args, typename ClassType>
	auto make_function(ReturnType(ClassType::*p)(Args...))
	-> std::function<ReturnType(Args...)> {
	return{ p };
	}
	
}*/
