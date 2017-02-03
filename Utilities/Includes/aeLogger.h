#pragma once

namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* @struct	LOGGER_DATA
	/*
	/* @brief	This is an empty structure that it is defined in aeLogger.cpp
	/*************************************************************************************************/

	struct LOGGER_DATA;

	/*************************************************************************************************/
	/* @class	aeLogger
	/*
	/* @brief	This is a logger module
	/*************************************************************************************************/

	class AE_UTILITY_EXPORT aeLogger : public Module<aeLogger>
	{
		/*************************************************************************************************/
		/* Constructors
		/*************************************************************************************************/
	public:
		aeLogger(String& FileName);
		virtual ~aeLogger();

	private:
		aeLogger(const aeLogger&);
		aeLogger& operator=(const aeLogger&);

	protected:
		/*************************************************************************************************/
		/* @fn	virtual void aeLogger::OnStartUp()
		/*
		/* @brief	Override if you want to module to be notified once it has been constructed on start.
		/*************************************************************************************************/

		void OnStartUp() override;

		/*************************************************************************************************/
		/* @fn	virtual void aeLogger::OnShutDown()
		/*
		/* @brief	Override if you want to module to be notified once it has been constructed on shut
		/* 			down.
		/*************************************************************************************************/

		void OnShutDown() override;
	public:
		/*************************************************************************************************/
		/* @fn	void aeLogger::Log(const String& Tag, const String& Msg, const ANSICHAR* FuncName, const ANSICHAR* sourceFile, uint32 lineNum);
		/*
		/* @brief	Writes into the log file.
		/*
		/* @param	Tag		  	The tag.
		/* @param	Msg		  	The message.
		/* @param	FuncName  	Name of the function.
		/* @param	sourceFile	Source file.
		/* @param	lineNum   	The line number.
		/*************************************************************************************************/

		void Log(const String& Tag, const String& Msg, const String& FuncName, const String& SourceFile, const uint32& LineNum);

		/*************************************************************************************************/
		/* @fn	void aeLogger::SaveToFile();
		/*
		/* @brief	Saves to file.
		/*************************************************************************************************/

		void SaveToFile();
	private:
		LOGGER_DATA* m_pData; //This variable stores all the data necessary to work
	};

}

#define AE_START_LOGGER(FileName) aeEngineSDK::aeLogger::StartUp(String(FileName)); 
#define AE_CLOSE_LOGGER() aeEngineSDK::aeLogger::ShutDown(); 
#define AE_FATAL(str) aeEngineSDK::aeLogger::Instance().Log("Fatal", str, __FUNCTION__, __FILE__, __LINE__); 

#if defined(_DEBUG)
	#define AE_ERROR(str) aeEngineSDK::aeLogger::Instance().Log("Error", str, __FUNCTION__, __FILE__, __LINE__); 
	#define AE_WARNING(str) aeEngineSDK::aeLogger::Instance().Log("Warning", str, __FUNCTION__, __FILE__, __LINE__); 
	#define AE_INFO(str) aeEngineSDK::aeLogger::Instance().Log("INFO", str, nullptr, nullptr, 0); 
	#define AE_LOG(tag, str) aeEngineSDK::aeLogger::Instance().Log(tag, str, nullptr, nullptr, 0); 
	#define AE_ASSERT(expr) aeEngineSDK::aeLogger::Instance().Log("Assert", aeEngineSDK::ToString((bool)(expr)).c_str(), __FUNCTION__, __FILE__, __LINE__);
#else
	#define AE_ERROR(str)		 (void)sizeof(str);
	#define AE_WARNING(str)	 (void)sizeof(str);
	#define AE_INFO(str)		 (void)sizeof(str);
	#define AE_LOG(tag, str)	 (void)sizeof(tag); (void)sizeof(str);
	#define AE_ASSERT(expr)	 (void)sizeof(expr);
#endif 