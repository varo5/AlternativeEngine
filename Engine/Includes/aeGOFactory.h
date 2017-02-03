#pragma once
#include "aeGOAddOn.h"
#include "aeGameObject.h"

namespace aeEngineSDK
{
	class AE_ENGINE_EXPORT aeGOFactory : public Module<aeGOFactory>
	{
		/*************************************************************************************************/
		/* Constructors
		/*************************************************************************************************/
	public:
		aeGOFactory();
		virtual ~aeGOFactory();

	private:
		aeGOFactory(const aeGOFactory&);
		aeGOFactory& operator=(const aeGOFactory&);

	private:
		void OnStartUp() override;
		void OnShutDown() override;

	private:
		Map<AE_GAME_OBJECT_ID, aeGameObject*> m_aGameObjects;
	};
}

