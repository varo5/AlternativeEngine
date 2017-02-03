#include "aeGameObject.h"

namespace aeEngineSDK
{
	aeGameObject::aeGameObject()
	{
		m_xName = "New GameObject";
		m_xTransform.m_pGameObject = this;
	}

	aeGameObject::aeGameObject(const String & GO)
	{
		m_xName = GO;
		m_xTransform.m_pGameObject = this;
	}

	aeGameObject::aeGameObject(const aeGameObject & GO)
	{
		*this = GO;
	}

	aeGameObject::~aeGameObject()
	{
	}

	inline void aeGameObject::SetStatic(const bool & Bool)
	{
		m_bStatic = Bool;
		for (auto child : m_xTransform.m_aChildren)
		{
			child->m_pGameObject->m_bStatic = m_bStatic;
		}
	}

	inline void aeGameObject::AddComponent(aeGOAddOn * AddOn)
	{
		m_aAddOns.insert(Pair<AE_ADD_ON_ID, aeGOAddOn*>(AddOn->GetComponentId(), AddOn));
	}

	inline bool aeGameObject::IsStatic() const
	{
		return m_bStatic;
	}

	inline AE_GAME_OBJECT_ID aeGameObject::GetID() const
	{
		return m_nID;
	}
}