/*************************************************************************************************/
/* @file	aeMath.h
/*
/* @brief	Declares the mathematics class.
/*************************************************************************************************/

#pragma once
#include "aePrerequisitesUtil.h"

#if AE_PLATFORM == AE_PLATFORM_WIN32
#include "aeWin32Math.h"
#else
#include "aePlatformMath.h"
#endif

namespace aeEngineSDK
{
#if AE_PLATFORM == AE_PLATFORM_WIN32
	typedef aeWin32Math aeMath;
#else
	typedef aePlatformMath aeMath;
#endif

	struct aeVector2;
	struct aeVector2Int;
	struct aeVector3;
	struct aeVector4;
	struct aeQuaternion;
	struct aeMatrix3;
	struct aeMatrix4;
	struct aePlane;
	struct aeRay;
	struct aeAABB;
	struct aeOBB;
	struct aeSphere;
}

#include "aeVector2.h"
#include "aeVector2Int.h"
#include "aeVector3.h"
#include "aeVector4.h"
#include "aeMatrix3.h"
#include "aeMatrix4.h"
#include "aeQuaternion.h"
#include "aePlane.h"
#include "aeRay.h"
#include "aeAABB.h"
//#include "aeOBB.h"
#include "aeSphere.h"

namespace aeEngineSDK
{
	extern bool CollisionRayToPlane(const aePlane& P, const aeRay& R, float& F, aeVector3& V);

	extern bool operator^(const aeVector3& V, const aeAABB& AB);

	extern bool operator^(const aeSphere& S, const aeVector3& V);
	extern bool operator^(const aeVector3& V, const aeSphere& S);

	extern bool operator^(const aeSphere& S, const aePlane& P);
	extern bool operator^(const aePlane& P, const aeSphere& S);
}