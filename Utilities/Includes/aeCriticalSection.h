#pragma once

namespace aeEngineSDK
{
	struct CRITICAL_SECTION_DATA;

	class AE_UTILITY_EXPORT aeCriticalSection
	{
	public:
		/*************************************************************************************************/
		/* Constructor
		/*************************************************************************************************/

		aeCriticalSection();
		~aeCriticalSection();

		/*************************************************************************************************/
		/* @fn	void aeCriticalSection::Lock()
		/*
		/* @brief	Locks this object.
		/*************************************************************************************************/

		void Lock();

		/*************************************************************************************************/
		/* @fn	void aeCriticalSection::Unlock()
		/*
		/* @brief	Unlocks this object.
		/*************************************************************************************************/

		void Unlock();

		/*************************************************************************************************/
		/* @fn	void aeCriticalSection::TryLock();
		/*
		/* @brief	Try lock.
		/*************************************************************************************************/

		bool TryLock();


		/*************************************************************************************************/
		/* Data
		/*************************************************************************************************/
	private:
		CRITICAL_SECTION_DATA* m_pData;
	};
}