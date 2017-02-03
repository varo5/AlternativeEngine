#pragma once
#include "aePrerequisitesUtil.h"

namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* @struct	TIME_STAMP
	/*
	/* @brief	A time stamp.
	/*************************************************************************************************/

	struct AE_UTILITY_EXPORT TIME_STAMP
	{		
		union
		{
			struct
			{
				uint8	Seconds : 6;
				uint8	Minutes : 6;
				uint8	Hours : 5;
				uint16	Year : 12;
				uint8	Month : 4;
				uint8	Day : 5;
				uint8	WeekDay : 4;
				uint16	YearDay : 9;
				bool	IsDST : 1;
			};
			uint64 T;
		};
	};

	/*************************************************************************************************/
	/* @struct	TIME_DATA
	/*
	/* @brief	A time data.
	/*************************************************************************************************/

	struct TIME_DATA;

	/*************************************************************************************************/
	/* @class	aeTime
	/*
	/* @brief	An ae utility export.
	/*************************************************************************************************/

	class AE_UTILITY_EXPORT aeTime
	{
	private:
		TIME_DATA* m_pData;

	public:
		aeTime();
		aeTime(const aeTime& T);
		~aeTime();

	public:
		void Start(float Scale = 1.0f); ///Reset the timer

		static TIME_T Time(); ///Returns the time since Epoch
		static TIME_STAMP GMTime(const TIME_T* T); ///Fills the time stamp structure with the given reference time
		static TIME_STAMP LocalTime(const TIME_T* T); ///Fills the time stamp structure with the given reference time
		static String GetTimeStamp(); /// Returns a string that contains the date and hour.

		float DeltaTime(); /// The time in seconds since the last call, its adjusted by a scale 
		float FixedDeltaTime(); /// The time in seconds since the last call
		float TimeSinceStart() const;	/// This is the time in seconds since the start of the timer

		float GetTimeScale() const;
		void SetTimeScale(const float& Scale);
	};

	template<class ReturnType, class... Args>
	static float SpeedTest(uint32 Repetitions, ReturnType(*f)(Args...), Args&&... args)
	{
		aeTime t;
		t.Start();
		for (uint32 i = 0; i < Repetitions; i++)
		{
			f(Forward<Args>(args)...);
		}
		return t.DeltaTime();
	}

	// Slows down the entire process by a lot, it is not recommended 
	template<typename Function, typename... Args>
	static float SpeedTest(uint32 Repetitions, Function&& f, Args&&... args)
	{
		aeTime t;
		t.Start();
		for (uint32 i = 0; i < Repetitions; i++)
		{
			f(Forward<Args>(args)...);
		}
		return t.DeltaTime();
	}
}

#define AE_TIME_STAMP aeEngineSDK::aeTime::GetTimeStamp()

#define AE_START_TIMED_LOGGER(FileName) \
		aeEngineSDK::String TS = "..\\Logs\\";\
		aeEngineSDK::String TT = AE_TIME_STAMP;\
		TS += TT;\
		TS += " ";\
		TS += FileName;\
		TS += ".xml";\
		AE_START_LOGGER(TS); 

#define AE_START_PROCESS_NAMED_LOGGER(argv)\
	aeEngineSDK::String s = argv;\
	aeEngineSDK::aeStringUtil::TrimRight(s, '.');\
	aeEngineSDK::aeStringUtil::TrimLeft(s, '\\');\
	auto v = aeEngineSDK::aeStringUtil::Split(s, '\\');\
	s = *v.rbegin();\
	AE_START_TIMED_LOGGER(s);