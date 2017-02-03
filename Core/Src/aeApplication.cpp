#include "aeApplication.h"
namespace aeEngineSDK
{
	aeApplication::aeApplication()
	{
	}

	aeApplication::aeApplication(const aeApplication & A)
	{
		*this = A;
	}

	aeApplication::~aeApplication()
	{
	}

	AE_RESULT aeApplication::Init()
	{
		return -1;
	}

	AE_RESULT aeApplication::StatusUptade()
	{
		return 0;
	}

	void aeApplication::Render()
	{
		
	}

	void aeApplication::Logic()
	{
	}

	void aeApplication::Destroy()
	{
	}

	AE_RESULT aeApplication::Run()
	{
		AE_RESULT Result = 0;

		if (Result = Init())
		{
			return Result;
		}

		while (StatusUptade())
		{
			Logic();
			Render();
		}

		Destroy();

		return 0;
	}

	void aeApplication::Resize(uint32 X, uint32 Y)
	{
	}

	void aeApplication::Stop()
	{
	}
}
