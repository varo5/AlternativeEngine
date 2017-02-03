#include "aePlatformTime.h"
#include "aeTime.h"
#include <sys/time.h>

namespace aeEngineSDK
{
	aePlatformTime::aePlatformTime()
	{
	}

	aePlatformTime::aePlatformTime(const aePlatformTime& T)
	{
		*this = T;
	}

	aePlatformTime::~aePlatformTime()
	{
	}

	void aePlatformTime::Start(float Scale)
	{
		// Establish the time scale
		m_fTimeScale = Scale;
		// start timer
		timespec t;
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t);
		m_xReference = m_xStart = t;
	}

	TIME_T aePlatformTime::Time()
	{
		return (TIME_T)time(0);
	}

	aeTimeStamp aePlatformTime::GMTime(const TIME_T* T)
	{
		time_t tt = *T;
		tm * ptm;
		ptm = gmtime(&tt);

		aeTimeStamp t;
		t.Seconds = ptm->tm_sec;
		t.Minutes = ptm->tm_min;
		t.Hours = ptm->tm_hour;
		t.Day = ptm->tm_mday;
		t.Month = ptm->tm_mon;
		t.Year = ptm->tm_year;
		t.WeekDay = ptm->tm_wday;
		t.YearDay = ptm->tm_yday;
		t.IsDST = ptm->tm_isdst;

		delete ptm;
		return t;
	}

	aeTimeStamp aePlatformTime::LocalTime(const TIME_T* T)
	{
		time_t tt = *T;
		tm * ptm;
		ptm = localtime(&tt);

		aeTimeStamp t;
		t.Seconds = ptm->tm_sec;
		t.Minutes = ptm->tm_min;
		t.Hours = ptm->tm_hour;
		t.Day = ptm->tm_mday;
		t.Month = ptm->tm_mon;
		t.Year = ptm->tm_year;
		t.WeekDay = ptm->tm_wday;
		t.YearDay = ptm->tm_yday;
		t.IsDST = ptm->tm_isdst;

		delete ptm;
		return t;
	}

	float aePlatformTime::DeltaTime()
	{
		return m_fTimeScale * FixedDeltaTime();
	}

	float aePlatformTime::FixedDeltaTime()
	{
		timespec t;

		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t);

		float Delta = FREQUENCY * (t.QuadPart - m_xReference);

		m_xReference = t.QuadPart;

		return Delta;
	}

	float aePlatformTime::TimeSinceStart() const
	{
		LARGE_INTEGER t;

		QueryPerformanceCounter(&t);

		return (FREQUENCY * (t.QuadPart - m_xStart));
	}

	float aePlatformTime::GetTimeScale() const
	{
		return m_fTimeScale;
	}

	void aePlatformTime::SetTimeScale(const float & Scale)
	{
		if (Scale >= 0)	m_fTimeScale = Scale;
	}

	float aePlatformTime::GetFrequency()
	{// get ticks per second
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		return 1.0f / frequency.QuadPart;
	}
}