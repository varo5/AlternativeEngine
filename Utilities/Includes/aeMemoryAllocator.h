#pragma once

#undef min
#undef max

#ifndef AE_UNREFERENCED_PARAMETER
#define AE_UNREFERENCED_PARAMETER(P) (void)P
#endif

#include <new>
#include <atomic>
#include <limits>
#include <utility>

namespace aeEngineSDK
{
	class MemoryAllocatorBase;

	class MemoryCounter
	{
	private:
		friend class MemoryAllocatorBase;

		static AE_UTILITY_EXPORT void IncrementAllocCount() { m_Allocs++; }
		static AE_UTILITY_EXPORT void IncrementFreeCount() { m_Frees++; }

		static AE_THREADLOCAL uint64 m_Allocs;
		static AE_THREADLOCAL uint64 m_Frees;
	public:
		static AE_UTILITY_EXPORT uint64 GetNumAllocs()
		{
			return m_Allocs;
		}

		static AE_UTILITY_EXPORT uint64 GetNumFrees()
		{
			return m_Frees;
		}

	};

	class MemoryAllocatorBase
	{
	protected:
		static void IncrementAllocCount() { MemoryCounter::IncrementAllocCount(); }
		static void IncrementFreeCount() { MemoryCounter::IncrementFreeCount(); }
	};

	template<class T>
	class MemoryAllocator : public MemoryAllocatorBase
	{
	public:
		static inline void* Allocate(SIZE_T bytes)
		{
#if AE_PROFILING_ENABLED
			IncrementAllocCount();
#endif
			return malloc(bytes);
		}

		static inline void* AllocateArray(SIZE_T bytes, uint32 count)
		{
#if AE_PROFILING_ENABLED
			IncrementAllocCount();
#endif
			return malloc(bytes * count);
		}

		static inline void Free(void* ptr)
		{
#if AE_PROFILING_ENABLED
			IncrementFreeCount();
#endif
			::free(ptr);
		}

		static inline void FreeArray(void* ptr, uint32 count)
		{
			AE_UNREFERENCED_PARAMETER(count);
#if AE_PROFILING_ENABLED
			IncrementFreeCount();
#endif
			::free(ptr);
		}
	};

	class GenAlloc
	{
	};

	template <class  Alloc>
	inline void* ae_alloc(SIZE_T count)
	{
		return MemoryAllocator<Alloc>::Allocate(count);
	}

	template <class T, class Alloc>
	inline T* ae_alloc()
	{
		return (T*)MemoryAllocator<Alloc>::Allocate(sizeof(T));
	}

	template <class T, class Alloc>
	inline T* ae_newN(uint32 count)
	{
		T* ptr = (T*)MemoryAllocator<Alloc>::AllocateArray(sizeof(T), count);

		for (uint32 i = 0; i < count; i++)
		{
			new ((void*)&ptr[i]) T;
		}

		return ptr;
	}
	
	template <class Type, class Alloc, class... Args>
	Type* ae_new(Args&&... args)
	{
		return new (ae_alloc<Alloc>(sizeof(Type))) Type(std::forward<Args>(args)...);
	}

	template <class Alloc>
	inline void ae_free(void* sock)
	{
		MemoryAllocator<Alloc>::Free(sock);
	}

	template <class T, class Alloc = GenAlloc>
	inline void ae_delete(T* ptr)
	{
		(ptr)->~T();
		MemoryAllocator<Alloc>::Free(ptr);
	}

	template <class T, class Alloc = GenAlloc>
	inline void ae_deleteN(T* ptr, uint32 count)
	{
		for (uint32 i = 0; i < count; i++)
		{
			ptr[i].~T();
		}
		
		MemoryAllocator<Alloc>::FreeArray(ptr, count);
	}

	inline void* ae_alloc(SIZE_T count)
	{
		return MemoryAllocator<GenAlloc>::Allocate(count);
	}

	template <class  T>
	inline T* ae_alloc()
	{
		return (T*)MemoryAllocator<GenAlloc>::Allocate(sizeof(T));
	}

	template <class T>
	inline T* ae_newN(uint32 count)
	{
		T* ptr = (T*)MemoryAllocator<GenAlloc>::AllocateArray(sizeof(T), count);

		for (uint32 i = 0; i < count; i++)
		{
			new ((void*)&ptr[i]) T;
		}

		return ptr;
	}

	template <class Type, class... Args>
	Type* ae_new(Args&&... args)
	{
		return new (ae_alloc<GenAlloc>(sizeof(Type))) Type(std::forward<Args>(args)...);
	}

	inline void ae_free(void* sock)
	{
		MemoryAllocator<GenAlloc>::Free(sock);
	}
}


#define  AE_PVT_DELETE(T, ptr)	\
	(ptr)->~T()					\
	MemoryAllocator<GenAlloc>::Free(ptr);

#define  AE_PVT_DELETE_A(T, ptr, Alloc)	\
	(ptr)->~T()							\
	MemoryAllocator<Alloc>::Free(ptr);

namespace aeEngineSDK
{
	template <class T, class Alloc = GenAlloc>
	class StdAlloc
	{
	public:
		typedef T value_type;
		StdAlloc() _NOEXCEPT {}
		template<class T, class Alloc> StdAlloc(const StdAlloc<T, Alloc>&) _NOEXCEPT {}
		template<class T, class Alloc> bool operator==(const StdAlloc<T, Alloc>&) const _NOEXCEPT { return true; }
		template<class T, class Alloc> bool operator!=(const StdAlloc<T, Alloc>&) const _NOEXCEPT { return false; }

		T* allocate(const size_t num)
		{
			if (num == 0)
			{
				return nullptr;
			}

			if (num > static_cast<size_t>(-1)/sizeof(T))
			{
				throw std::bad_array_new_length();
			}

			void* const pv = ae_alloc<Alloc>((uint32)(num*sizeof(T)));
			if(!pv)
			{
				throw std::bad_alloc();
			}

			return static_cast<T*>(pv);
		}

		void deallocate(T* p, size_t) const _NOEXCEPT
		{
			ae_free<Alloc>((void*)p);
		}
	};
}

//aeMemstack
// aeMemAlloc
