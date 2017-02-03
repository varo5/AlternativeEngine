#pragma once
#include "aePrerequisitesUtil.h"
#include "aeString.h"

namespace aeEngineSDK
{
	enum FileMode
	{
		IN = 0x01,
		OUT = 0x02,
		BINARY = 0x20
	};

	class AE_UTILITY_EXPORT aeFileSystem
	{
	private:
		std::fstream m_xDataStream;
	public:
		aeFileSystem();
		~aeFileSystem();

	public:
		void Open(String pszFileName, FileMode Mode);
		void Close();

		void Read(void* pData, SIZE_T StreamSize);
		void Write(void* pData, SIZE_T StreamSize);

		bool IsOpen();

		aeFileSystem& operator >> (bool& val);
		aeFileSystem& operator >> (int8& val);
		aeFileSystem& operator >> (int16& val);
		aeFileSystem& operator >> (int32& val);
		aeFileSystem& operator >> (int64& val);
		aeFileSystem& operator >> (uint8& val);
		aeFileSystem& operator >> (uint16& val);
		aeFileSystem& operator >> (uint32& val);
		aeFileSystem& operator >> (uint64& val);
		aeFileSystem& operator >> (float& val);
		aeFileSystem& operator >> (double& val);
		aeFileSystem& operator >> (long double& val);
		aeFileSystem& operator >> (String& val);
		aeFileSystem& operator >> (void*& val);

		aeFileSystem& operator<< (bool& val);
		aeFileSystem& operator<< (int8& val);
		aeFileSystem& operator<< (int16& val);
		aeFileSystem& operator<< (int32& val);
		aeFileSystem& operator<< (int64& val);
		aeFileSystem& operator<< (uint8& val);
		aeFileSystem& operator<< (uint16& val);
		aeFileSystem& operator<< (uint32& val);
		aeFileSystem& operator<< (uint64& val);
		aeFileSystem& operator<< (float& val);
		aeFileSystem& operator<< (double& val);
		aeFileSystem& operator<< (long double& val);
		aeFileSystem& operator<< (String& val);
		aeFileSystem& operator<< (void*& val);
	};
}
