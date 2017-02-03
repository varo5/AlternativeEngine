#pragma once
#include "aeResourceManager.h"
#include "aeGOFactory.h"

namespace aeEngineSDK
{
	class aeGameObject;

	class AE_ENGINE_EXPORT aeScene
	{
		/*************************************************************************************************/
		/* Constructors
		/*************************************************************************************************/
	public:
		aeScene();
		aeScene(const String& Name);
		aeScene(const aeScene& O);
		~aeScene();

		/*************************************************************************************************/
		/* Functions
		/*************************************************************************************************/
	public:
		void SetName(const String& Name);
		void LoadScene(const String& Filename);
		void AddGameObject(aeGameObject* pGameObject);

		aeModel* TransformToModels();
		String GetName();

		/*************************************************************************************************/
		/* Proprieties
		/*************************************************************************************************/
	private:
		String m_pszName;
		Vector<aeGameObject*> m_aGameObjects;

		void AddModels(aeModel* Output, aeGameObject* GO, const aeMatrix4& Transform);
	};
}