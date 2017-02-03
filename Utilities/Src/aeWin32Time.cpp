#include "aeTime.h"
#include "aeString.h"
#include <windows.h>

namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* @struct	TIME_DATA
	/*
	/* @brief	Time data.
	/*************************************************************************************************/

	struct TIME_DATA
	{
		float TimeScale;
		int64 Reference;
		int64 Start;
	};

	float GetFrequency()
	{// get ticks per second
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		return 1.0f / frequency.QuadPart;
	}
	
	const float FREQUENCY = GetFrequency();

	aeTime::aeTime()
	{
		m_pData = ae_new<TIME_DATA>();
	}

	aeTime::aeTime(const aeTime& T)
	{
		*this = T;
	}

	aeTime::~aeTime()
	{
		ae_delete(m_pData);
	}

	void aeTime::Start(float Scale)
	{
		// Establish the time scale
		m_pData->TimeScale = Scale;
		// start timer
		LARGE_INTEGER t;
		QueryPerformanceCounter(&t);
		m_pData->Reference = m_pData->Start = t.QuadPart;
	}

	TIME_T aeTime::Time()
	{
		return (TIME_T)time(0);
	}

	TIME_STAMP aeTime::GMTime(const TIME_T* T)
	{
		time_t tt = (time_t)*T;
		tm * ptm = nullptr;
		ptm = gmtime(&tt);

		TIME_STAMP t;
		t.Seconds = ptm->tm_sec;
		t.Minutes = ptm->tm_min;
		t.Hours = ptm->tm_hour;
		t.Day = ptm->tm_mday;
		t.Month = ptm->tm_mon+1;
		t.Year = ptm->tm_year + 1900;
		t.WeekDay = ptm->tm_wday;
		t.YearDay = ptm->tm_yday;
		t.IsDST = ptm->tm_isdst;

		return t;
	}

	TIME_STAMP aeTime::LocalTime(const TIME_T* T)
	{
		time_t tt = (time_t)*T;
		tm * ptm = nullptr;
		ptm = localtime(&tt);

		TIME_STAMP t;
		t.Seconds = ptm->tm_sec;
		t.Minutes = ptm->tm_min;
		t.Hours = ptm->tm_hour;
		t.Day = ptm->tm_mday;
		t.Month = ptm->tm_mon+1;
		t.Year = ptm->tm_year+1900;
		t.WeekDay = ptm->tm_wday;
		t.YearDay = ptm->tm_yday;
		t.IsDST = ptm->tm_isdst;

		return t;
	}

	String aeTime::GetTimeStamp()
	{
		String str;
		TIME_T T = Time();
		TIME_STAMP TS = LocalTime(&T);

		str += ToString(TS.Year);
		if (TS.Month<10) str += "0";
		str += ToString(TS.Month);
		str += ToString(TS.Day);

		str += "T";
		if (TS.Hours<10) str += "0";
		str += ToString(TS.Hours);
		if (TS.Minutes<10) str += "0";
		str += ToString(TS.Minutes);
		if (TS.Seconds<10) str += "0";
		str += ToString(TS.Seconds);

		return str;
	}

	float aeTime::DeltaTime()
	{
		return m_pData->TimeScale * FixedDeltaTime();
	}

	float aeTime::FixedDeltaTime()
	{
		LARGE_INTEGER t;

		QueryPerformanceCounter(&t);

		float Delta = FREQUENCY * (t.QuadPart - m_pData->Reference);

		m_pData->Reference = t.QuadPart;

		return Delta;
	}

	float aeTime::TimeSinceStart() const
	{
		LARGE_INTEGER t;

		QueryPerformanceCounter(&t);

		return (FREQUENCY * (t.QuadPart - m_pData->Start));
	}

	float aeTime::GetTimeScale() const
	{
		return m_pData->TimeScale;
	}

	void aeTime::SetTimeScale(const float & Scale)
	{
		if (Scale >= 0)	m_pData->TimeScale = Scale;
	}

	
}