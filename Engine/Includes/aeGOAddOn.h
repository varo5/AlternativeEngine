#pragma once
#include "aePrerequisitesUtil.h"
#include "aePrerequisitesEngine.h"

namespace aeEngineSDK
{
	enum struct AE_ADD_ON_ID
	{
		AE_RENDERER
	};

	class aeGameObject;
	class AE_ENGINE_EXPORT aeGOAddOn
	{
		friend class aeGOFactory;
	public:
		aeGOAddOn();
		aeGOAddOn(const aeGOAddOn& AO);
		~aeGOAddOn();
		
	public:
		virtual AE_RESULT Init();
		virtual void Update();
		virtual void Destroy();

		virtual AE_ADD_ON_ID GetComponentId() const = 0;

		aeGameObject* m_pGameObject;
	};
}