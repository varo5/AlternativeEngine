#pragma once

namespace aeEngineSDK
{
	/*class  GlobalFrameAlloc : public GenAlloc
	{
	private:
		static AE_THREADLOCAL void* m_pMemory;
		static AE_THREADLOCAL SIZE_T m_nSize;

		struct OcuppiedMemoryBlock
		{
			SIZE_T Pos;
			SIZE_T Size;

			bool operator() (const OcuppiedMemoryBlock& lhs, const OcuppiedMemoryBlock& rhs) const
			{
				return lhs.Pos < rhs.Pos;
			}

			bool operator< (const OcuppiedMemoryBlock& b) const
			{
				return Pos < b.Pos;
			}
		};

		struct EmptyMemoryBlock
		{
			SIZE_T Pos;
			SIZE_T Size;

			SIZE_T GetPos() const
			{
				return Pos;
			}

			bool operator() (const EmptyMemoryBlock& lhs, const EmptyMemoryBlock& rhs) const
			{
				return lhs.Size < rhs.Size;
			}

			bool operator< (const EmptyMemoryBlock& b) const
			{
				return Size < b.Size;
			}
		};

		static Set<OcuppiedMemoryBlock> m_aOccupiedMemory;
		static Set<EmptyMemoryBlock> m_aEmptyMemory;

		static inline void InitMemory(const SIZE_T& bytes)
		{
			m_pMemory = ::malloc(bytes);
			m_nSize += bytes;
			m_aEmptyMemory.insert(EmptyMemoryBlock{ 0,bytes });
		}

		static inline SIZE_T ExpandMemory(const SIZE_T& bytes)
		{
			SIZE_T Pos = m_nSize;
			m_aEmptyMemory.insert(EmptyMemoryBlock{ Pos,bytes });
			m_nSize += bytes;
			m_pMemory = ::realloc(m_pMemory, m_nSize);
			return Pos;
		}

		static inline SIZE_T ResizeToWord(SIZE_T bytes)
		{
			return (((bytes + 3) >> 2) << 2);
		}

		static void CheckForAdjacentEmptyMemory()
		{
			for (auto f : m_aEmptyMemory)
			{
				SIZE_T NextPos = f.Pos + f.Size;

				auto itt = FindIf(m_aEmptyMemory.begin(), m_aEmptyMemory.end(), 
					GenericComparator<EmptyMemoryBlock, SIZE_T>(&EmptyMemoryBlock::GetPos, NextPos));
				if(itt != m_aEmptyMemory.end())
					if ((*itt).Pos == NextPos)
					{
						f.Size = (*itt).Size + f.Size;
						m_aEmptyMemory.erase(itt);
					}
			}
		}

	public:
		static AE_UTILITY_EXPORT void* Alloc(const SIZE_T& bytes)
		{
			SIZE_T Resized = ResizeToWord(bytes);
			if (!m_pMemory) InitMemory(Resized);

			bool MemoryLocationNotFound = true;
			SIZE_T PosFound = 0;

			while (MemoryLocationNotFound)
			{
				auto itt = m_aEmptyMemory.equal_range(EmptyMemoryBlock{ 0,Resized });
				if (itt.first != m_aEmptyMemory.end())
				{
					if ((*itt.first).Size == Resized)
					{
						MemoryLocationNotFound = false;
						PosFound = (*itt.first).Pos;
						m_aEmptyMemory.erase(itt.first);
						m_aOccupiedMemory.insert(OcuppiedMemoryBlock{ PosFound ,Resized });
						continue;
					}
				}
				if (itt.second != m_aEmptyMemory.end())
				{
					if ((*itt.second).Size > Resized)
					{
						MemoryLocationNotFound = false;
						PosFound = (*itt.second).Pos;
						auto temp = EmptyMemoryBlock{ (*itt.second).Pos + Resized,(*itt.second).Size - Resized };
						m_aEmptyMemory.erase(itt.second);
						m_aEmptyMemory.insert(temp);
						m_aOccupiedMemory.insert(OcuppiedMemoryBlock{ PosFound ,Resized });
						continue;
					}
				}

				if (MemoryLocationNotFound) PosFound = ExpandMemory(Resized);
			}
			return (BYTE*)m_pMemory + PosFound;
		}

		static AE_UTILITY_EXPORT void Free(void* ptr)
		{
			if (!m_pMemory) return;

			if ((SIZE_T)ptr < (SIZE_T)m_pMemory) return;

			SIZE_T Pos = (SIZE_T)ptr - (SIZE_T)m_pMemory;

			if (Pos > m_nSize) return;

			auto itt = m_aOccupiedMemory.lower_bound(OcuppiedMemoryBlock{ Pos,0 });

			if ((*itt).Pos != Pos) return;

			m_aEmptyMemory.insert(EmptyMemoryBlock{ Pos,(*itt).Size });

			m_aOccupiedMemory.erase(itt);

			CheckForAdjacentEmptyMemory();
		}

		static AE_UTILITY_EXPORT inline void Reset()
		{
			m_aOccupiedMemory.clear();
			m_aEmptyMemory.clear();
			m_aEmptyMemory.insert(EmptyMemoryBlock{ 0,m_nSize });
		}

		static AE_UTILITY_EXPORT inline void Release()
		{
			void* ptr = m_pMemory;
			m_pMemory = nullptr;
			::free(ptr);
			m_aOccupiedMemory.clear();
			m_aEmptyMemory.clear();
		}
	};*/

	/*class  GlobalFrameAlloc : public GenAlloc
	{
	private:
		static AE_THREADLOCAL void* m_pMemory;
		static AE_THREADLOCAL SIZE_T m_nSize;

		struct OcuppiedMemoryBlock
		{
			SIZE_T Pos;
			SIZE_T Size;

			bool operator() (const OcuppiedMemoryBlock& lhs, const OcuppiedMemoryBlock& rhs) const
			{
				return lhs.Pos < rhs.Pos;
			}

			bool operator< (const OcuppiedMemoryBlock& b) const
			{
				return Pos < b.Pos;
			}
		};

		struct EmptyMemoryBlock
		{
			SIZE_T Pos;
			SIZE_T Size;

			SIZE_T GetPos() const
			{
				return Pos;
			}

			bool operator() (const EmptyMemoryBlock& lhs, const EmptyMemoryBlock& rhs) const
			{
				return lhs.Size < rhs.Size;
			}

			bool operator< (const EmptyMemoryBlock& b) const
			{
				return Size < b.Size;
			}
		};

		static Set<OcuppiedMemoryBlock> m_aOccupiedMemory;
		static Vector<EmptyMemoryBlock> m_aEmptyMemory;

		static inline void InitMemory(const SIZE_T& bytes)
		{
			m_pMemory = ::malloc(bytes);
			m_nSize += bytes;
			m_aEmptyMemory.push_back(EmptyMemoryBlock{ 0,bytes });
		}

		static inline SIZE_T ExpandMemory(const SIZE_T& bytes)
		{
			SIZE_T Pos = m_nSize;
			m_aEmptyMemory.push_back(EmptyMemoryBlock{ Pos,bytes });
			m_nSize += bytes;
			m_pMemory = ::realloc(m_pMemory, m_nSize);
			return Pos;
		}

		static inline SIZE_T ResizeToWord(SIZE_T bytes)
		{
			return (((bytes + 3) >> 2) << 2);
		}

		static void CheckForAdjacentEmptyMemory()
		{
			/ *for (auto f : m_aEmptyMemory)
			{
				SIZE_T NextPos = f.Pos + f.Size;

				auto itt = FindIf(m_aEmptyMemory.begin(), m_aEmptyMemory.end(),
					GenericComparator<EmptyMemoryBlock, SIZE_T>(&EmptyMemoryBlock::GetPos, NextPos));
				if (itt != m_aEmptyMemory.end())
					if ((*itt).Pos == NextPos)
					{
						f.Size = (*itt).Size + f.Size;
						m_aEmptyMemory.erase(itt);
					}
			}* /
		}

	public:
		static AE_UTILITY_EXPORT void* Alloc(const SIZE_T& bytes)
		{
			SIZE_T Resized = ResizeToWord(bytes);
			if (!m_pMemory) InitMemory(Resized);

			bool MemoryLocationNotFound = true;
			SIZE_T PosFound = 0;

			while (MemoryLocationNotFound)
			{
				for (SIZE_T i = 0; i < m_aEmptyMemory.size(); i++)
				{
					if (m_aEmptyMemory[i].Size == Resized)
					{
						MemoryLocationNotFound = false;
						PosFound = m_aEmptyMemory[i].Pos;
						m_aEmptyMemory.erase(m_aEmptyMemory.begin() + i);
						m_aOccupiedMemory.insert(OcuppiedMemoryBlock{ PosFound ,Resized });
						break;
					}
					else if (m_aEmptyMemory[i].Size > Resized)
					{
						MemoryLocationNotFound = false;
						PosFound = m_aEmptyMemory[i].Pos;
						m_aEmptyMemory[i] = EmptyMemoryBlock{ m_aEmptyMemory[i].Pos + Resized, m_aEmptyMemory[i].Size - Resized };
						m_aOccupiedMemory.insert(OcuppiedMemoryBlock{ PosFound ,Resized });
						break;
					}
				}
				if (MemoryLocationNotFound) PosFound = ExpandMemory(Resized);
			}
			return (BYTE*)m_pMemory + PosFound;
		}

		static AE_UTILITY_EXPORT void Free(void* ptr)
		{
			if (!m_pMemory) return;

			if ((SIZE_T)ptr < (SIZE_T)m_pMemory) return;

			SIZE_T Pos = (SIZE_T)ptr - (SIZE_T)m_pMemory;

			if (Pos > m_nSize) return;

			auto itt = m_aOccupiedMemory.lower_bound(OcuppiedMemoryBlock{ Pos,0 });

			if ((*itt).Pos != Pos) return;

			m_aEmptyMemory.push_back(EmptyMemoryBlock{ Pos,(*itt).Size });

			m_aOccupiedMemory.erase(itt);

			CheckForAdjacentEmptyMemory();
		}

		static AE_UTILITY_EXPORT inline void Reset()
		{
			m_aOccupiedMemory.clear();
			m_aEmptyMemory.clear();
			m_aEmptyMemory.push_back(EmptyMemoryBlock{ 0,m_nSize });
		}

		static AE_UTILITY_EXPORT inline void Release()
		{
			void* ptr = m_pMemory;
			m_pMemory = nullptr;
			::free(ptr);
			m_aOccupiedMemory.clear();
			m_aEmptyMemory.clear();
		}
	};*/

	/*class  GlobalFrameAlloc : public GenAlloc, public Module<GlobalFrameAlloc>
	{
	public:
		GlobalFrameAlloc()
		{
		}

		virtual ~GlobalFrameAlloc()
		{
			_Instance() = nullptr;
			IsDestroyed() = true;
		}

		GlobalFrameAlloc(const GlobalFrameAlloc&)
		{
		}

		GlobalFrameAlloc& operator=(const GlobalFrameAlloc&)
		{
			return *this;
		}

	private:
		void* m_pMemory;
		SIZE_T m_nPos;
		SIZE_T m_nSize;
		SIZE_T m_nPrevSize;

		Set<SIZE_T> m_aTemporaryMemory;

		inline void InitMemory(const SIZE_T& bytes)
		{
			m_pMemory = ::malloc(bytes);
			m_nPrevSize = m_nSize += bytes;
		}

		virtual void OnStartUp()
		{
			m_pMemory = nullptr;
			m_nPos = 0;
			m_nSize = 0;
			m_nPrevSize = 0;
			m_aTemporaryMemory = Set<SIZE_T>();
		}

		virtual void OnShutDown()
		{

		}

		static inline SIZE_T ResizeToWord(SIZE_T bytes)
		{
			return (((bytes + 3) >> 2) << 2);
		}

	public:
		static AE_UTILITY_EXPORT void* Alloc(const SIZE_T& bytes)
		{
			SIZE_T Resized = GlobalFrameAlloc::ResizeToWord(bytes);
			if (!GlobalFrameAlloc::IsStarted())
			{
				GlobalFrameAlloc::StartUp();
				if (!GlobalFrameAlloc::IsStarted()) return nullptr;
				GlobalFrameAlloc::Instance().InitMemory(Resized);
			}

			if (GlobalFrameAlloc::Instance().m_nPos + Resized <= GlobalFrameAlloc::Instance().m_nPrevSize)
			{
				SIZE_T Pos = GlobalFrameAlloc::Instance().m_nPos;
				GlobalFrameAlloc::Instance().m_nPos += Resized;
				return (BYTE*)GlobalFrameAlloc::Instance().m_pMemory + Pos;
			} 
			else
			{
				GlobalFrameAlloc::Instance().m_nSize += Resized;
				void* tmp = ::malloc(bytes);
				GlobalFrameAlloc::Instance().m_aTemporaryMemory.insert((SIZE_T)tmp);
				return tmp;
			}
			
		}

		static AE_UTILITY_EXPORT void Free(void* ptr)
		{
			if (!GlobalFrameAlloc::IsStarted())
			{
				::free(ptr);
				return;
			}

			if ((SIZE_T)ptr < (SIZE_T)GlobalFrameAlloc::Instance().m_pMemory)
				if ((SIZE_T)ptr - (SIZE_T)GlobalFrameAlloc::Instance().m_pMemory >  GlobalFrameAlloc::Instance().m_nSize)
				{
					auto tmp = GlobalFrameAlloc::Instance().m_aTemporaryMemory.find((SIZE_T)ptr);
					if (tmp == GlobalFrameAlloc::Instance().m_aTemporaryMemory.end())
					{
						::free(ptr);
						return;
					}
					::free(ptr);
					GlobalFrameAlloc::Instance().m_aTemporaryMemory.erase(tmp);
					return;
				}
		}

		static AE_UTILITY_EXPORT inline void Reset()
		{
			if (!GlobalFrameAlloc::IsStarted())
			{
				GlobalFrameAlloc::Instance().m_nPos = 0;
				if (GlobalFrameAlloc::Instance().m_nPrevSize != GlobalFrameAlloc::Instance().m_nSize)
				{
					GlobalFrameAlloc::Instance().m_pMemory = ::realloc(GlobalFrameAlloc::Instance().m_pMemory, GlobalFrameAlloc::Instance().m_nSize);
					GlobalFrameAlloc::Instance().m_nPrevSize = GlobalFrameAlloc::Instance().m_nSize;
				}

				for (auto mem : GlobalFrameAlloc::Instance().m_aTemporaryMemory)
					::free((void*)mem);

				GlobalFrameAlloc::Instance().m_aTemporaryMemory.clear();
			}
		}

		static AE_UTILITY_EXPORT inline void Release()
		{
			if (!GlobalFrameAlloc::IsStarted())
			{
				void* ptr = GlobalFrameAlloc::Instance().m_pMemory;
				GlobalFrameAlloc::Instance().m_pMemory = nullptr;
				::free(ptr);

				for (auto mem : GlobalFrameAlloc::Instance().m_aTemporaryMemory)
					::free((void*)mem);

				GlobalFrameAlloc::Instance().m_aTemporaryMemory.clear();

				GlobalFrameAlloc::ShutDown();
			}
		}
	};*/

	class  GlobalFrameAlloc : public GenAlloc
	{
	private:
		static void* m_pMemory;
		static AE_THREADLOCAL SIZE_T m_nPos;
		static AE_THREADLOCAL SIZE_T m_nSize;
		static AE_THREADLOCAL SIZE_T m_nPrevSize;

		static Set<SIZE_T> m_aTemporaryMemory;

		static inline void InitMemory(const SIZE_T& bytes)
		{
			m_pMemory = ::malloc(bytes);
			m_nPrevSize = m_nSize += bytes;
		}

		static inline SIZE_T ResizeToWord(SIZE_T bytes)
		{
			return (((bytes + 3) >> 2) << 2);
		}

	public:
		static AE_UTILITY_EXPORT void* Alloc(const SIZE_T& bytes)
		{
			SIZE_T Resized = ResizeToWord(bytes);
			if (!m_pMemory) InitMemory(Resized);

			if (m_nPos + Resized <= m_nPrevSize)
			{
				SIZE_T Pos = m_nPos;
				m_nPos += Resized;
				return (BYTE*)m_pMemory + Pos;
			}
			else
			{
				m_nSize += Resized;
				void* tmp = ::malloc(bytes);
				m_aTemporaryMemory.insert((SIZE_T)tmp);
				return tmp;
			}

		}

		static AE_UTILITY_EXPORT void Free(void* ptr)
		{
			if (!m_pMemory)
			{
				::free(ptr);
				return;
			}

			if ((SIZE_T)ptr < (SIZE_T)m_pMemory)
				if ((SIZE_T)ptr - (SIZE_T)m_pMemory > m_nSize)
				{
					auto tmp = m_aTemporaryMemory.find((SIZE_T)ptr);
					if (tmp == m_aTemporaryMemory.end())
					{
						::free(ptr);
						return;
					}
					::free(ptr);
					m_aTemporaryMemory.erase(tmp);
					return;
				}
		}

		static AE_UTILITY_EXPORT inline void Reset()
		{
			m_nPos = 0;
			if (m_nPrevSize != m_nSize)
			{
				m_pMemory = ::realloc(m_pMemory, m_nSize);
				m_nPrevSize = m_nSize;
			}

			for (auto mem : m_aTemporaryMemory)
				::free((void*)mem);

			m_aTemporaryMemory.clear();
		}

		static AE_UTILITY_EXPORT inline void Release()
		{
			void* ptr = m_pMemory;
			m_pMemory = nullptr;
			::free(ptr);

			for (auto mem : m_aTemporaryMemory)
				::free((void*)mem);

			m_aTemporaryMemory.clear();
		}
	};


	template<>
	class MemoryAllocator<GlobalFrameAlloc> : public MemoryAllocatorBase
	{
	public:
		static inline void* Allocate(SIZE_T bytes)
		{
#if AE_PROFILING_ENABLED
			IncrementAllocCount();
#endif
			return GlobalFrameAlloc::Alloc(bytes);
		}

		static inline void* AllocateArray(SIZE_T bytes, uint32 count)
		{
#if AE_PROFILING_ENABLED
			IncrementAllocCount();
#endif
			return GlobalFrameAlloc::Alloc(bytes * count);
		}

		static inline void Free(void* ptr)
		{
#if AE_PROFILING_ENABLED
			IncrementFreeCount();
#endif
			GlobalFrameAlloc::Free(ptr);
		}

		static inline void FreeArray(void* ptr, uint32 count)
		{
			AE_UNREFERENCED_PARAMETER(count);
#if AE_PROFILING_ENABLED
			IncrementFreeCount();
#endif
			GlobalFrameAlloc::Free(ptr);
		}
	};

	inline void* ae_frame_alloc(SIZE_T count)
	{
		return MemoryAllocator<GlobalFrameAlloc>::Allocate(count);
	}

	template <class T>
	inline T* ae_frame_alloc()
	{
		return (T*)MemoryAllocator<GlobalFrameAlloc>::Allocate(sizeof(T));
	}

	template <class T>
	inline T* ae_frame_newN(uint32 count)
	{
		T* ptr = (T*)MemoryAllocator<GlobalFrameAlloc>::AllocateArray(sizeof(T), count);

		for (uint32 i = 0; i < count; i++)
		{
			new ((void*)&ptr[i]) T;
		}

		return ptr;
	}

	template <class Type, class... Args>
	Type* ae_frame_new(Args&&... args)
	{
		return new (ae_alloc<GlobalFrameAlloc>(sizeof(Type))) Type(std::forward<Args>(args)...);
	}

	inline void ae_frame_free(void* sock)
	{
		MemoryAllocator<GlobalFrameAlloc>::Free(sock);
	}

	template <class T>
	inline void ae_frame_delete(T* ptr)
	{
		(ptr)->~T();
		MemoryAllocator<GlobalFrameAlloc>::Free(ptr);
	}

	template <class T>
	inline void ae_frame_deleteN(T* ptr, uint32 count)
	{
		for (uint32 i = 0; i < count; i++)
		{
			ptr[i].~T();
		}

		MemoryAllocator<GlobalFrameAlloc>::FreeArray(ptr, count);
	}
}

namespace aeEngineSDK
{
	template <typename T>
	using FrameAlloc = StdAlloc<T, GlobalFrameAlloc>;
}

namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* Frame containers, for easier access in my own namespace
	/*************************************************************************************************/
	template <typename T>
	using FrameDeque = std::deque<T, FrameAlloc<T>>;

	template <typename T>
	using FrameVector = std::vector<T, FrameAlloc<T>>;

	template <typename T>
	using FrameList = std::list<T, FrameAlloc<T>>;

	template <typename T>
	using FrameStack = std::stack<T, std::deque<T, FrameAlloc<T>>>;

	template <typename T>
	using FrameQueue = std::queue<T, std::deque<T, FrameAlloc<T>>>;

	template <typename T, typename P = std::less<T>>
	using FrameSet = std::set<T, P, FrameAlloc<T>>;

	template <typename K, typename V, typename P = std::less<K>>
	using FrameMap = std::map<K, V, P, FrameAlloc<std::pair<const K, V>>>;

	template <typename K, typename V, typename P = std::less<K>>
	using FrameMultiMap = std::multimap<K, V, P, FrameAlloc<std::pair<const K, V>>>;

	template <typename T, typename H = std::hash<T>, typename C = std::equal_to<T>>
	using FrameUnorderedSet = std::unordered_set<T, H, C, FrameAlloc<T>>;

	template <typename K, typename V, typename H = std::hash<K>, typename C = std::equal_to<K>>
	using FrameUnorderedMap = std::unordered_map<K, V, H, C, FrameAlloc<std::pair<const K, V>>>;

	template <typename K, typename V, typename H = std::hash<K>, typename C = std::equal_to<K>>
	using FrameUnorderedMultimap = std::unordered_multimap<K, V, H, C, FrameAlloc<std::pair<const K, V>>>;

	/*************************************************************************************************/
	/* Smart pointer that retains shared ownership of a project through a pointer. Reference unique.
	/* The object is destroyed automatically when the las shared pointer to the object is destroyed.
	/*************************************************************************************************/

	template <typename T>
	using FrameUPtr = std::unique_ptr < T, decltype(&ae_delete<T, FrameAlloc>)>;

	/*************************************************************************************************/
	/* Create a new shared pointer using the frame allocator category.
	/*************************************************************************************************/
	template<class Type, class... Args>
	SPtr<Type> ae_frame_shared_ptr_new(Args&&... args)
	{
		return std::allocate_shared<Type>(FrameAlloc<Type>(), std::forward<Args>(args)...);
	}

	/*************************************************************************************************/
	/* Create a new shared pointer from a previously constructed object. Pointer specific data will
	/* be allocated using the frame allocator category.
	/*************************************************************************************************/
	template<class Type>
	SPtr<Type> ae_frame_shared_ptr(Type* data)
	{
		return std::shared_ptr<Type>(data, &ae_delete<Type, GlobalFrameAlloc>, FrameAlloc<Type>());
	}

	/*************************************************************************************************/
	/* Create a new unique pointer from a previously constructed object. Pointer specific data will
	/* be allocated using the frame allocator category.
	/*************************************************************************************************/
	template<class Type>
	FrameUPtr<Type> ae_frame_unique_ptr(Type* data)
	{
		return std::unique_ptr<Type, decltype(&ae_delete<Type, GlobalFrameAlloc>)>(data, ae_delete<Type, GlobalFrameAlloc>);
	}

	/*************************************************************************************************/
	/* Create a new unique pointer using the frame allocator category.
	/*************************************************************************************************/
	template<class Type, class... Args>
	FrameUPtr<Type> ae_frame_unique_ptr_new(Args &&... args)
	{
		Type* rawPtr = ae_new<Type, GlobalFrameAlloc>(std::forward<Args>(args)...);
		return ae_unique_ptr<Type, GlobalFrameAlloc>(rawPtr);
	}
}
