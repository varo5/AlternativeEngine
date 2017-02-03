#include "aePrerequisitesUtil.h"
#include "aeMath.h"
#include "aeTime.h"
#include "aeVector2.h"
#include "aeVector2Int.h"
#include "aeVector3.h"
#include "aeVector4.h"
#include "aeMatrix3.h"
#include "aeMatrix4.h"

using aeEngineSDK::aeMath;
using aeEngineSDK::aeTime;
using aeEngineSDK::String;
using aeEngineSDK::aeStringUtil;
using aeEngineSDK::Function;
aeEngineSDK::Vector<aeEngineSDK::int8*> g_ptrList = aeEngineSDK::Vector<aeEngineSDK::int8*>();

void FrameAllocateTest()
{
	for (size_t i = 0; i < 10000; i++)
	{
		aeEngineSDK::int8* i1 = aeEngineSDK::ae_frame_newN<aeEngineSDK::int8>(16);
	}
	for (size_t i = 0; i < 1000; i++)
	{
		aeEngineSDK::int8* i2 = aeEngineSDK::ae_frame_newN<aeEngineSDK::int8>(256);
	}

	for (size_t i = 0; i < 50; i++)
	{
		aeEngineSDK::int8* i3 = aeEngineSDK::ae_frame_newN<aeEngineSDK::int8>(2097152);
	}
	aeEngineSDK::GlobalFrameAlloc::Reset();
}

void RegularAllocateTest()
{
	for (size_t i = 0; i < 10000; i++)
	{
		aeEngineSDK::int8* i1 = new aeEngineSDK::int8[16];
		g_ptrList.push_back(i1);
	}
	for (size_t i = 0; i < 1000; i++)
	{
		aeEngineSDK::int8* i2 = new aeEngineSDK::int8[256];
		g_ptrList.push_back(i2);
	}

	for (size_t i = 0; i < 50; i++)
	{
		aeEngineSDK::int8* i3 = new aeEngineSDK::int8[2097152];
		g_ptrList.push_back(i3);
	}

	for (size_t i = 0; i < g_ptrList.size(); i++)
	{
		delete[] g_ptrList[i];
	}
	g_ptrList.clear();
}

int main(int argc, char** argv)
{
	/*************************************************************************************************/
	/* Initialize the logger
	/*************************************************************************************************/
	AE_START_PROCESS_NAMED_LOGGER(argv[0]);	

	/*************************************************************************************************/
	/* Testing general use equations
	/*************************************************************************************************/
	AE_ASSERT(aeMath::Abs(-3.5f) == 3.5f);
	AE_ASSERT(aeMath::Percentage(100.0f,1.0f) == 0.01f);
	AE_ASSERT(aeMath::CloseEnough(3.5f, 3.501f, 0.01f));
	AE_ASSERT(aeMath::CloseEnough(3.5f,3.5f));
	AE_ASSERT(aeMath::Trunc(3.5f) == 3.0f);
	AE_ASSERT(aeMath::Floor(3.5f) == 3.0f);
	AE_ASSERT(aeMath::Round(3.5f) == 4.0f);
	AE_ASSERT(aeMath::Ceil(3.5f) == 4.0f);
	AE_ASSERT(aeMath::Fractional(3.5f) == 0.5f);
	AE_ASSERT(aeMath::CloseEnough(aeMath::Exp(2.0f),7.389056098f));
	AE_ASSERT(aeMath::CloseEnough(aeMath::Loge(2.0f), 0.69314718f));
	AE_ASSERT(aeMath::CloseEnough(aeMath::Log10(2.0f), 0.301029995f));
	AE_ASSERT(aeMath::CloseEnough(aeMath::LogX(2.0f,3.0f), 1.5849625007f));
	AE_ASSERT(aeMath::CloseEnough(aeMath::LogX(2.0f, 3.0f), 1.5849625007f));
	AE_ASSERT(aeMath::Mod(20,6) == 2);
	AE_ASSERT(aeMath::Modf(20, 6) == 2.0f);
	AE_ASSERT(aeMath::CloseEnough(aeMath::Sqrt(2.0f), 1.414213562f));
	AE_ASSERT(aeMath::CloseEnough(aeMath::InvSqrt(2.0f), 0.707106781f));
	AE_ASSERT(aeMath::CloseEnough(aeMath::FastInvSqrt(2.0f), aeMath::InvSqrt(2.0f)));
	AE_ASSERT(aeMath::CloseEnough(aeMath::Pow(2.0f,3.0f), 8.0f));
	AE_ASSERT(aeMath::Max(20, 6) == 20);
	AE_ASSERT(aeMath::Min(20, 6) == 6);
	AE_ASSERT(aeMath::Max3(20, 6, 8) == 20);
	AE_ASSERT(aeMath::Min3(20, 6, 8) == 6);
	AE_ASSERT(aeMath::Sign(20));
	AE_ASSERT(aeMath::Clamp(20, 0, 10) == 10);
	AE_ASSERT(aeMath::CloseEnough(aeMath::Lerp(2.0f, 3.0f, 0.5f), 2.5f));
	AE_ASSERT(aeMath::CloseEnough(aeMath::Slerp(2.0f, 3.0f, 0.5f), 2.25f));
	AE_ASSERT(aeMath::CloseEnough(aeMath::PI, 3.14159265358f));
	AE_ASSERT(aeMath::IsNaN(aeMath::FLOAT_NAN));
	AE_ASSERT(!aeMath::IsFinite(aeMath::FLOAT_INFINITY));
	AE_ASSERT(aeMath::IsNegativeFloat(-20.0f));

	/*************************************************************************************************/
	/* Testing regular trigonometric equations
	/*************************************************************************************************/
	AE_ASSERT(aeMath::Sin(aeMath::HALF_PI) == 1.0f);
	AE_ASSERT(aeMath::Cos(0.0f) == 1.0f);
	AE_ASSERT(aeMath::Tan(aeMath::PI) == aeMath::Sin(aeMath::PI) / aeMath::Cos(aeMath::PI));
	AE_ASSERT(aeMath::ArcSin(1.0f) == aeMath::HALF_PI);
	AE_ASSERT(aeMath::ArcCos(1.0f) == 0.0f);
	AE_ASSERT(aeMath::ArcTan(1.0f) == aeMath::ONE_QUARTER_PI);

	/*************************************************************************************************/
	/* Testing precision of the fast trigonometric equations against their counterparts
	/*************************************************************************************************/
	AE_ASSERT(aeMath::CloseEnough(aeMath::Sin(aeMath::HALF_PI),			aeMath::FastSin(aeMath::HALF_PI),			0.005f));
	AE_ASSERT(aeMath::CloseEnough(aeMath::Cos(aeMath::HALF_PI),			aeMath::FastCos(aeMath::HALF_PI),			0.005f));
	AE_ASSERT(aeMath::CloseEnough(aeMath::Tan(aeMath::ONE_QUARTER_PI),	aeMath::FastTan(aeMath::ONE_QUARTER_PI),	0.005f));

	AE_ASSERT(aeMath::CloseEnough(1.0f / aeMath::Sin(aeMath::HALF_PI),			aeMath::FastCsc(aeMath::HALF_PI),			0.005f));
	AE_ASSERT(aeMath::CloseEnough(1.0f / aeMath::Cos(aeMath::ONE_QUARTER_PI),	aeMath::FastSec(aeMath::ONE_QUARTER_PI),	0.005f));
	AE_ASSERT(aeMath::CloseEnough(1.0f / aeMath::Tan(aeMath::HALF_PI),			aeMath::FastCot(aeMath::HALF_PI),			0.005f));

	AE_ASSERT(aeMath::CloseEnough(aeMath::ArcSin(aeMath::ONE_QUARTER_PI), aeMath::FastArcSin(aeMath::ONE_QUARTER_PI), 0.005f));
	AE_ASSERT(aeMath::CloseEnough(aeMath::ArcCos(aeMath::ONE_QUARTER_PI), aeMath::FastArcCos(aeMath::ONE_QUARTER_PI), 0.005f));
	AE_ASSERT(aeMath::CloseEnough(aeMath::ArcTan(aeMath::ONE_QUARTER_PI), aeMath::FastArcTan(aeMath::ONE_QUARTER_PI), 0.005f));

	AE_ASSERT(aeMath::CloseEnough(aeMath::ArcTan2(3,4), aeMath::FastArcTan2(3,4), 0.005f));
	
	/*************************************************************************************************/
	/* Testing speed test tools and function handling
	/*************************************************************************************************/
	//AE_ASSERT(aeMath::CloseEnough(aeEngineSDK::SpeedTest(1, []() { aeEngineSDK::SleepFor(0.1f); }), 0.1f, 0.005f));

	Function<float, const float&> FSin = aeMath::Sin;
	AE_ASSERT(FSin(aeMath::HALF_PI) == 1);

	Function<void> FSleep = []() { aeEngineSDK::SleepFor(0.1f); };
	AE_ASSERT(aeMath::CloseEnough(aeEngineSDK::SpeedTest(1, FSleep), 0.1f, 0.005f));	

	AE_ASSERT(aeMath::FastAbs(-2) >= 0);
	AE_ASSERT(aeMath::FastAbs(-2.0) >= 0);
	AE_ASSERT(aeMath::FastAbs(-2.0f) >= 0);

	AE_ASSERT((aeEngineSDK::SpeedTest<float, const float&>(100000, &aeMath::FastAbs, -2.0f)) < (aeEngineSDK::SpeedTest<float, const float&>(100000, &aeMath::Abs, -2.0f)));

	/*************************************************************************************************/
	/* Testing speed of the fast trigonometric equations against their counterparts
	/*************************************************************************************************/
	AE_ASSERT((aeEngineSDK::SpeedTest(1000000, &aeMath::FastSin, aeMath::HALF_PI)) < (aeEngineSDK::SpeedTest(1000000, &aeMath::Sin, aeMath::HALF_PI)));
	AE_ASSERT((aeEngineSDK::SpeedTest(1000000, &aeMath::FastCos, aeMath::HALF_PI)) < (aeEngineSDK::SpeedTest(1000000, &aeMath::Cos, aeMath::HALF_PI)));
	AE_ASSERT((aeEngineSDK::SpeedTest(1000000, &aeMath::FastTan, aeMath::HALF_PI)) < (aeEngineSDK::SpeedTest(1000000, &aeMath::Tan, aeMath::HALF_PI)));
	AE_ASSERT((aeEngineSDK::SpeedTest(1000000, &aeMath::FastCsc, aeMath::HALF_PI)) < (aeEngineSDK::SpeedTest(1000000, &aeMath::Sin, aeMath::HALF_PI)));
	AE_ASSERT((aeEngineSDK::SpeedTest(1000000, &aeMath::FastSec, aeMath::HALF_PI)) < (aeEngineSDK::SpeedTest(1000000, &aeMath::Cos, aeMath::HALF_PI)));
	AE_ASSERT((aeEngineSDK::SpeedTest(1000000, &aeMath::FastCot, aeMath::HALF_PI)) < (aeEngineSDK::SpeedTest(1000000, &aeMath::Tan, aeMath::HALF_PI)));
			   						   
	AE_ASSERT((aeEngineSDK::SpeedTest(1000000, &aeMath::FastArcSin, aeMath::HALF_PI)) < (aeEngineSDK::SpeedTest(1000000, &aeMath::ArcSin, aeMath::HALF_PI)));
	AE_ASSERT((aeEngineSDK::SpeedTest(1000000, &aeMath::FastArcCos, aeMath::HALF_PI)) < (aeEngineSDK::SpeedTest(1000000, &aeMath::ArcCos, aeMath::HALF_PI)));
	AE_ASSERT((aeEngineSDK::SpeedTest(1000000, &aeMath::FastArcTan, aeMath::HALF_PI)) < (aeEngineSDK::SpeedTest(1000000, &aeMath::ArcTan, aeMath::HALF_PI)));
			   
	AE_ASSERT((aeEngineSDK::SpeedTest(1000000, &aeMath::FastArcTan2, 3, 4)) < (aeEngineSDK::SpeedTest(1000000, &aeMath::ArcTan2, 3, 4)));

	std::cout << aeEngineSDK::SpeedTest(10, &FrameAllocateTest) << std::endl;
	aeEngineSDK::GlobalFrameAlloc::Release();
	std::cout << aeEngineSDK::SpeedTest(10, &RegularAllocateTest) << std::endl;

	aeEngineSDK::aeVector2 v0 = aeEngineSDK::aeVector2Int();
	aeEngineSDK::aeVector2 v1 = aeEngineSDK::aeVector3();
	aeEngineSDK::aeVector2 v2 = aeEngineSDK::aeVector4();
	aeEngineSDK::aeVector3 v3 = aeEngineSDK::aeVector2();
	aeEngineSDK::aeVector3 v4 = aeEngineSDK::aeVector2Int();
	aeEngineSDK::aeVector3 v5 = aeEngineSDK::aeVector4();
	aeEngineSDK::aeVector4 v6 = aeEngineSDK::aeVector2();
	aeEngineSDK::aeVector4 v7 = aeEngineSDK::aeVector2Int();
	aeEngineSDK::aeVector4 v8 = aeEngineSDK::aeVector3();

	AE_CLOSE_LOGGER();

	return 0;
}