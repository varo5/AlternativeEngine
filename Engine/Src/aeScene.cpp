#include "aeScene.h"
#include "aeRendererAddOn.h"

namespace aeEngineSDK
{
	aeScene::aeScene()
	{
		m_pszName = "New Scene";
	}

	aeScene::aeScene(const String & Name)
	{
		m_pszName = Name;
	}

	aeScene::aeScene(const aeScene & O)
	{
		*this = O;
	}

	aeScene::~aeScene()
	{
	}

	void aeScene::SetName(const String & Name)
	{
		m_pszName = Name;
	}

	void aeScene::LoadScene(const String & Filename)
	{
	}

	void aeScene::AddGameObject(aeGameObject* pGameObject)
	{
		m_aGameObjects.push_back(pGameObject);
	}

	void aeScene::AddModels(aeModel* Output,  aeGameObject* GO, const aeMatrix4& Transform)
	{
		if (GO->IsStatic())
		{
			auto AO = GO->m_aAddOns.equal_range(AE_ADD_ON_ID::AE_RENDERER);
			aeMatrix4 Tr = GO->m_xTransform.GetRealMatrix() * Transform;
			for (auto it = AO.first; it != AO.second; ++it)
			{
				Vector<aeMesh> NM;
				NM = ((aeRendererAddOn*)it->second)->m_xModel.GetMeshes();
				for (auto Mesh : NM)
				{
					for (auto vertex : Mesh.Vertices)
					{
						vertex.Pos = Tr * vertex.Pos;
					}
					Output->m_aMeshes.push_back(Mesh);
					Output->m_aMaterials.push_back(Mesh.pMaterial);
					Output->m_aMeshes.rbegin()->MaterialIndex = Output->m_aMaterials.size()-1;
					Output->m_aMeshes.rbegin()->pMaterial = Mesh.pMaterial;
				}
			}

			for (auto child : GO->m_xTransform.m_aChildren)
			{
				AddModels(Output, child->m_pGameObject, Tr);
			}
		}
	}

	aeModel* aeScene::TransformToModels()
	{
		aeModel* Output = ae_new<aeModel>();

		for (auto GO : m_aGameObjects)
		{
			AddModels(Output, GO,aeMatrix4::Identity());
		}

		return Output;
	}
	String aeScene::GetName()
	{
		return m_pszName;
	}
}