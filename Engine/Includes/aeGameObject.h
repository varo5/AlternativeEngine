#pragma once
#include "aeResourceManager.h"
#include "aeTransform.h"
#include "aeGOAddOn.h"

namespace aeEngineSDK
{
	typedef uint64 AE_GAME_OBJECT_ID;

	class AE_ENGINE_EXPORT aeGameObject
	{
		friend class aeGOFactory;
	public:
		aeGameObject();
		aeGameObject(const String& GO);
		aeGameObject(const aeGameObject& GO);
		~aeGameObject();

	public:
		void SetStatic(const bool& Bool);
		void AddComponent(aeGOAddOn* AddOn);

		bool IsStatic() const;
		
		AE_GAME_OBJECT_ID GetID() const;

		String m_xName;
		aeTransform m_xTransform;
		MultiMap<AE_ADD_ON_ID, aeGOAddOn*> m_aAddOns;
	private:
		bool m_bStatic;

		AE_GAME_OBJECT_ID m_nID;
	};
}
