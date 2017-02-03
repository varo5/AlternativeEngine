#include "aeFileSystem.h"

namespace aeEngineSDK
{
	aeFileSystem::aeFileSystem()
	{
	}

	aeFileSystem::~aeFileSystem()
	{
	}

	void aeFileSystem::Open(String pszFileName, FileMode Mode)
	{
		m_xDataStream.open(pszFileName.c_str(), Mode);
	}

	void aeFileSystem::Close()
	{
		m_xDataStream.close();
	}

	void aeFileSystem::Read(void * pData, SIZE_T StreamSize)
	{
		m_xDataStream.read((char*)pData, StreamSize);
	}

	void aeFileSystem::Write(void * pData, SIZE_T StreamSize)
	{
		m_xDataStream.write((char*)pData, StreamSize);
	}

	bool aeFileSystem::IsOpen()
	{
		return m_xDataStream.is_open();
	}

	aeFileSystem & aeFileSystem::operator >> (bool & val)
	{
		m_xDataStream >> val; return *this;
	}

	aeFileSystem & aeFileSystem::operator >> (int8 & val)
	{
		m_xDataStream >> val; return *this;
	}

	aeFileSystem & aeFileSystem::operator >> (int16 & val)
	{
		m_xDataStream >> val; return *this;
	}

	aeFileSystem & aeFileSystem::operator >> (int32 & val)
	{
		m_xDataStream >> val; return *this;
	}

	aeFileSystem & aeFileSystem::operator >> (int64 & val)
	{
		m_xDataStream >> val; return *this;
	}

	aeFileSystem & aeFileSystem::operator >> (uint8 & val)
	{
		m_xDataStream >> val; return *this;
	}

	aeFileSystem & aeFileSystem::operator >> (uint16 & val)
	{
		m_xDataStream >> val; return *this;
	}

	aeFileSystem & aeFileSystem::operator >> (uint32 & val)
	{
		m_xDataStream >> val; return *this;
	}

	aeFileSystem & aeFileSystem::operator >> (uint64 & val)
	{
		m_xDataStream >> val; return *this;
	}

	aeFileSystem & aeFileSystem::operator >> (float & val)
	{
		m_xDataStream >> val; return *this;
	}

	aeFileSystem & aeFileSystem::operator >> (double & val)
	{
		m_xDataStream >> val; return *this;
	}

	aeFileSystem & aeFileSystem::operator >> (long double & val)
	{
		m_xDataStream >> val; return *this;
	}

	aeFileSystem & aeFileSystem::operator >> (String & val)
	{
		m_xDataStream >> val; return *this;
	}

	aeFileSystem & aeFileSystem::operator >> (void *& val)
	{
		m_xDataStream >> val; return *this;
	}



	aeFileSystem & aeFileSystem::operator<<(bool & val)
	{
		m_xDataStream << val; return *this;
	}

	aeFileSystem & aeFileSystem::operator<<(int8 & val)
	{
		m_xDataStream << val; return *this;
	}

	aeFileSystem & aeFileSystem::operator<<(int16 & val)
	{
		m_xDataStream << val; return *this;
	}

	aeFileSystem & aeFileSystem::operator<<(int32 & val)
	{
		m_xDataStream << val; return *this;
	}

	aeFileSystem & aeFileSystem::operator<<(int64 & val)
	{
		m_xDataStream << val; return *this;
	}

	aeFileSystem & aeFileSystem::operator<<(uint8 & val)
	{
		m_xDataStream << val; return *this;
	}

	aeFileSystem & aeFileSystem::operator<<(uint16 & val)
	{
		m_xDataStream << val; return *this;
	}

	aeFileSystem & aeFileSystem::operator<<(uint32 & val)
	{
		m_xDataStream << val; return *this;
	}

	aeFileSystem & aeFileSystem::operator<<(uint64 & val)
	{
		m_xDataStream << val; return *this;
	}

	aeFileSystem & aeFileSystem::operator<<(float & val)
	{
		m_xDataStream << val; return *this;
	}

	aeFileSystem & aeFileSystem::operator<<(double & val)
	{
		m_xDataStream << val; return *this;
	}

	aeFileSystem & aeFileSystem::operator<<(long double & val)
	{
		m_xDataStream << val; return *this;
	}

	aeFileSystem & aeFileSystem::operator<<(String & val)
	{
		m_xDataStream << val; return *this;
	}

	aeFileSystem & aeFileSystem::operator<<(void *& val)
	{
		m_xDataStream << val; return *this;
	}
}
