#include "aeOctris.h"
#include <aeMath.h>
#include <aeAABB.h>
#include <assimp/IOSystem.hpp>
#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <fbxsdk.h>
#include <fbxsdk/fileio/fbxiosettings.h>

#define MAX_VERTEX

namespace aeEngineSDK
{
	aeOctrisNode::aeOctrisNode()
	{
		m_nFaceCount = 0;
		m_aNodes = nullptr;
	}

	aeOctrisNode::aeOctrisNode(const aeOctrisNode& O)
	{
		*this = O;
	}

	aeOctrisNode::aeOctrisNode(const aeVector3& Min, const aeVector3& Max)
	{
		m_xBox = aeAABB(Min, Max);
		m_nFaceCount = 0;
		m_aNodes = nullptr;
	}

	aeOctrisNode::~aeOctrisNode()
	{
	}

	bool aeOctrisNode::IsOverloaded(uint32 Max)
	{
		bool Overload = false;
		for (auto Mesh : m_xModel.m_aMeshes)
		{
			for (auto vertex : Mesh.Faces)
			{
				m_nFaceCount++;
				if (m_nFaceCount > Max)
				{
					Overload = true;
				}
			}
		}
		return  Overload;
	}

	void aeOctrisNode::CreateNewBranches(MultiMap<bool, aeOctrisNode*>& Nodes)
	{
		m_aNodes = new aeOctrisNode[8];

		Nodes.insert(Pair<bool, aeOctrisNode*>(true, &m_aNodes[0]));
		Nodes.insert(Pair<bool, aeOctrisNode*>(true, &m_aNodes[1]));
		Nodes.insert(Pair<bool, aeOctrisNode*>(true, &m_aNodes[2]));
		Nodes.insert(Pair<bool, aeOctrisNode*>(true, &m_aNodes[3]));
		Nodes.insert(Pair<bool, aeOctrisNode*>(true, &m_aNodes[4]));
		Nodes.insert(Pair<bool, aeOctrisNode*>(true, &m_aNodes[5]));
		Nodes.insert(Pair<bool, aeOctrisNode*>(true, &m_aNodes[6]));
		Nodes.insert(Pair<bool, aeOctrisNode*>(true, &m_aNodes[7]));

		aeVector3 Center = m_xBox.m_xMin + (m_xBox.m_xMax - m_xBox.m_xMin)*0.5f;
		aeVector3 RightTopFront =		aeVector3(m_xBox.m_xMax.x, m_xBox.m_xMax.y, m_xBox.m_xMin.z);
		aeVector3 RightBottomFront =	aeVector3(m_xBox.m_xMax.x, m_xBox.m_xMin.y, m_xBox.m_xMin.z);
		aeVector3 LeftBottomBack =		aeVector3(m_xBox.m_xMin.x, m_xBox.m_xMin.y, m_xBox.m_xMax.z);
		aeVector3 LeftTopBack =			aeVector3(m_xBox.m_xMin.x, m_xBox.m_xMax.y, m_xBox.m_xMax.z);
		aeVector3 LeftTopFront =		aeVector3(m_xBox.m_xMin.x, m_xBox.m_xMax.y, m_xBox.m_xMin.z);
		aeVector3 RightBottomBack =		aeVector3(m_xBox.m_xMax.x, m_xBox.m_xMin.y, m_xBox.m_xMax.z);

		m_aNodes[0] = aeOctrisNode(Center, m_xBox.m_xMin);
		m_aNodes[1] = aeOctrisNode(Center, RightBottomFront);
		m_aNodes[2] = aeOctrisNode(Center, LeftBottomBack);
		m_aNodes[3] = aeOctrisNode(Center, RightBottomBack);
		m_aNodes[4] = aeOctrisNode(Center, LeftTopFront);
		m_aNodes[5] = aeOctrisNode(Center, RightTopFront);
		m_aNodes[6] = aeOctrisNode(Center, LeftTopBack);
		m_aNodes[7] = aeOctrisNode(Center, m_xBox.m_xMax);

		aeModel Model = m_xModel;

		for(uint8 i = 0; i < 8; i++)
		{
			for (uint32 Me = 0; Me < Model.m_aMeshes.size(); Me++)//(auto Mesh = Model.m_aMeshes.begin(); Mesh != Model.m_aMeshes.end(); ++Mesh)//(auto Mesh : Model.m_aMeshes)
			{
				Map<uint32, aeVertex> NewMesh;
				Vector<aeFace> Faces;
				for (uint32 Fa = 0; Fa < Model.m_aMeshes[Me].Faces.size(); Fa++)//(auto Face = Mesh->Faces.begin(); Face != Mesh->Faces.end(); ++Face)//(auto Face : Mesh.Faces)
				{
					for (uint32 Ve = 0; Ve < 3; Ve++)//(auto Vertex = Face->Vertices.begin(); Vertex != Face->Vertices.end(); ++Vertex)//(auto Vertex : Face.Vertices)
					{
						if (m_aNodes[i].m_xBox^Model.m_aMeshes[Me].Faces[Fa].Vertices[Ve]->Pos)
						{
							Faces.push_back(Model.m_aMeshes[Me].Faces[Fa]);
							NewMesh.insert(Pair<uint32, aeVertex>(Model.m_aMeshes[Me].Faces[Fa].Indices[0], *Model.m_aMeshes[Me].Faces[Fa].Vertices[0]));
							NewMesh.insert(Pair<uint32, aeVertex>(Model.m_aMeshes[Me].Faces[Fa].Indices[1], *Model.m_aMeshes[Me].Faces[Fa].Vertices[1]));
							NewMesh.insert(Pair<uint32, aeVertex>(Model.m_aMeshes[Me].Faces[Fa].Indices[2], *Model.m_aMeshes[Me].Faces[Fa].Vertices[2]));
							break;
						}
					}
				}
				if (!NewMesh.empty())
				{
					m_aNodes[i].m_xModel.m_aMeshes.push_back(aeMesh());
					auto m = m_aNodes[i].m_xModel.m_aMeshes.rbegin();
					
					Vector<aeFace> Copy = Faces;
					uint32 counter = 0;
					for (auto itt = NewMesh.begin(); itt != NewMesh.end(); ++itt)//(auto itt : NewMesh)
					{						
						m->Vertices.push_back(itt->second);
						auto v = m->Vertices.rbegin();
						
						for (uint32 f = 0; f < Faces.size(); f++)//(auto f : Faces)
						{
							for (uint32 i = 0; i < 3; i++)
							{
								if (Faces[f].Indices[i] == itt->first)
								{
									Copy[f].Indices[i] = counter;
									Copy[f].Vertices[i] = &*v;
								}
							}
						}
						counter++;
					}
					for (uint32 f = 0; f < Copy.size(); f++)
					{
						m->Indices.push_back(Copy[f].Indices[0]);
						m->Indices.push_back(Copy[f].Indices[1]);
						m->Indices.push_back(Copy[f].Indices[2]);
					}
					m->Faces = Copy;
					m_aNodes[i].m_xModel.m_aMaterials.push_back(Model.m_aMeshes[Me].pMaterial);
					m->pMaterial = *m_aNodes[i].m_xModel.m_aMaterials.rbegin();
					m->MaterialIndex = m_aNodes[i].m_xModel.m_aMaterials.size() - 1;
					m->NumIndices = m->Indices.size();
				}
			}
		}
		m_xModel.Clear();
		m_nFaceCount = 0;
	}

	bool aeOctrisNode::IsEmpty() const
	{
		return !(bool)m_nFaceCount;
	}

	aeOctris::aeOctris()
	{
	}

	aeOctris::aeOctris(const aeOctris& O)
	{
		*this = O;
	}

	aeOctris::~aeOctris()
	{
	}

	void aeOctris::SegmentMesh(aeScene& Scene, uint32 MaxVertex)
	{
		m_pszSceneName = Scene.GetName();
		aeVector3 Max(aeMath::LOW_FLOAT, aeMath::LOW_FLOAT, aeMath::LOW_FLOAT);
		aeVector3 Min(aeMath::MAX_FLOAT, aeMath::MAX_FLOAT, aeMath::MAX_FLOAT);
		auto Model = Scene.TransformToModels();
		for (uint32 i = 0; i < Model->m_aMeshes.size(); i++)//(auto Mesh : Model->m_aMeshes)
		{
			for (uint32 j = 0; j < Model->m_aMeshes[i].Vertices.size(); j++)//(auto vertex : Mesh.Vertices)
			{
				Max.x = aeMath::Max(Max.x, Model->m_aMeshes[i].Vertices[j].Pos.x);
				Max.y = aeMath::Max(Max.y, Model->m_aMeshes[i].Vertices[j].Pos.y);
				Max.z = aeMath::Max(Max.z, Model->m_aMeshes[i].Vertices[j].Pos.z);

				Min.x = aeMath::Min(Min.x, Model->m_aMeshes[i].Vertices[j].Pos.x);
				Min.y = aeMath::Min(Min.y, Model->m_aMeshes[i].Vertices[j].Pos.y);
				Min.z = aeMath::Min(Min.z, Model->m_aMeshes[i].Vertices[j].Pos.z);
			}
		
		}
		m_pRoot = ae_new<aeOctrisNode>(Min, Max);
		m_aOctriTree.insert(Pair<bool, aeOctrisNode*>(true, m_pRoot));
		m_pRoot->m_xModel = *Model;
		while (true)
		{
			auto nodes = m_aOctriTree.equal_range(true);
			if (nodes.first == m_aOctriTree.end() && nodes.second == m_aOctriTree.end())
			{
				break;
			}
			for (auto it = nodes.first; it!= nodes.second;)
			{
				if ((*it).second->IsOverloaded(MaxVertex))
				{
					(*it).second->CreateNewBranches(m_aOctriTree);
				}
				else
				{
					m_aOctriTree.insert(Pair<bool, aeOctrisNode*>(false, (*it).second));
					auto cit = it;
					++it;
					m_aOctriTree.erase(cit);
					--it;
				}
				++it;
			}
		}
		for (auto it = m_aOctriTree.begin(); it != m_aOctriTree.end(); ++it)
		{
			if (it->second->m_xModel.m_aMeshes.size() != 0)
			{
				for (uint32 i = 0; i < it->second->m_xModel.m_aMeshes.size(); i++)
				{
					m_aMeshes.push_back(&it->second->m_xModel.m_aMeshes[i]);
				}
			}
		}
	}

	void aeOctris::SaveToFile()
	{
	}

	void aeOctris::SaveToFile(const String & FilePath)
	{
		String Extension = aeStringUtil::TrimmedLeft(FilePath, '.');

		if (Extension == "dae")
		{
			Assimp::Exporter Exporter;

			const aiExportFormatDesc* format = Exporter.GetExportFormatDescription(0);

			aiScene* scene = new aiScene();

			scene->mRootNode = new aiNode();

			scene->mMaterials = new aiMaterial*[1];
			scene->mMaterials[0] = nullptr;
			scene->mNumMaterials = 1;

			scene->mMaterials[0] = new aiMaterial();

			scene->mMeshes = new aiMesh*[m_aMeshes.size()];
			scene->mNumMeshes = m_aMeshes.size();

			for (uint32 i = 0; i < m_aMeshes.size(); i++)
			{
				scene->mMeshes[i] = nullptr;
				scene->mMeshes[i] = new aiMesh();
				scene->mMeshes[i]->mMaterialIndex = 0;
			}


			scene->mRootNode->mMeshes = new unsigned int[m_aMeshes.size()];
			for (uint32 i = 0; i < m_aMeshes.size(); i++)
			{
				scene->mRootNode->mMeshes[i] = i;
			}
			scene->mRootNode->mNumMeshes = m_aMeshes.size();

			for (uint32 i = 0; i < m_aMeshes.size(); i++)
			{
				auto pMesh = scene->mMeshes[i];

				pMesh->mVertices = new aiVector3D[m_aMeshes[i]->Vertices.size()];
				pMesh->mNumVertices = m_aMeshes[i]->Vertices.size();

				pMesh->mTextureCoords[0] = new aiVector3D[m_aMeshes[i]->Vertices.size()];
				pMesh->mNumUVComponents[0] = m_aMeshes[i]->Vertices.size();

				pMesh->mNormals = new aiVector3D[m_aMeshes[i]->Vertices.size()];
				pMesh->mBitangents = new aiVector3D[m_aMeshes[i]->Vertices.size()];
				pMesh->mTangents = new aiVector3D[m_aMeshes[i]->Vertices.size()];
				pMesh->mColors[0] = new aiColor4D[m_aMeshes[i]->Vertices.size()];

				for (auto itr = m_aMeshes[i]->Vertices.begin(); itr != m_aMeshes[i]->Vertices.end(); ++itr)
				{
					const auto& v = itr->Pos;
					const auto& tc = itr->TexCoord;
					const auto& n = itr->Normal;
					const auto& c = itr->Color;
					const auto& bt = itr->Bitangent;
					const auto& t = itr->Tangent;

					pMesh->mVertices[itr - m_aMeshes[i]->Vertices.begin()] = aiVector3D(v.x, v.y, v.z);
					pMesh->mTextureCoords[0][itr - m_aMeshes[i]->Vertices.begin()] = aiVector3D(tc.x, tc.y, 0);
					pMesh->mNormals[itr - m_aMeshes[i]->Vertices.begin()] = aiVector3D(n.x, n.y, n.z);
					pMesh->mColors[0][itr - m_aMeshes[i]->Vertices.begin()] = aiColor4D(c.R, c.G, c.B, c.A);
					pMesh->mTangents[itr - m_aMeshes[i]->Vertices.begin()] = aiVector3D(t.x, t.y, t.z);
					pMesh->mBitangents[itr - m_aMeshes[i]->Vertices.begin()] = aiVector3D(bt.x, bt.y, bt.z);
				}


				pMesh->mFaces = new aiFace[m_aMeshes[i]->Faces.size()];
				pMesh->mNumFaces = m_aMeshes[i]->Faces.size();

				for (auto itr = m_aMeshes[i]->Faces.begin(); itr != m_aMeshes[i]->Faces.end(); ++itr)
				{
					aiFace& face = pMesh->mFaces[itr - m_aMeshes[i]->Faces.begin()];

					face.mIndices = new unsigned int[3];
					face.mNumIndices = 3;

					face.mIndices[0] = itr->Indices[0];
					face.mIndices[1] = itr->Indices[1];
					face.mIndices[2] = itr->Indices[2];
				}
			}

			aiReturn ret = Exporter.Export(scene, Extension.c_str(), FilePath.c_str());

			if (ret == aiReturn_FAILURE)
			{
				String msg = "Error exporting scene ";
				msg += FilePath;
				msg += " : ";
				msg += Exporter.GetErrorString();
				AE_ERROR(msg.c_str());
			}
			//ae_delete(scene);
		}
		else if (Extension == "obj" || Extension == "fbx")
		{
			// Create the FBX SDK manager
			FbxManager* lSdkManager = FbxManager::Create();

			// Create an IOSettings object.
			FbxIOSettings * ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
			lSdkManager->SetIOSettings(ios);

			// ... Configure the FbxIOSettings object here ...

			// Create an exporter.
			FbxExporter* lExporter = FbxExporter::Create(lSdkManager, "");

			// Initialize the exporter.
			bool lExportStatus = lExporter->Initialize(FilePath.c_str(), -1, lSdkManager->GetIOSettings());

			if (!lExportStatus) 
			{
				String msg = "Call to FbxExporter::Initialize() failed.\n";
				msg += "Error returned : ";
				msg += lExporter->GetStatus().GetErrorString();
				AE_ERROR(msg.c_str());
			}

			// Create a new scene so it can be populated by the imported file.
			FbxScene* lScene = FbxScene::Create(lSdkManager, m_pszSceneName.c_str());

			// Get the root node of the scene.
			FbxNode* lRootNode = lScene->GetRootNode();

			for (uint32 i = 0; i < m_aMeshes.size(); i++)
			{
				// Create a node for our mesh in the scene.
				FbxNode* lMeshNode = FbxNode::Create(lScene, "meshNode");

				// Create a mesh.
				FbxMesh* lMesh = FbxMesh::Create(lScene, "mesh");

				// Set the node attribute of the mesh node.
				lMeshNode->SetNodeAttribute(lMesh);

				// Add the mesh node to the root node in the scene.
				lRootNode->AddChild(lMeshNode);

				// Initialize the control point array of the mesh.
				lMesh->InitControlPoints(m_aMeshes[i]->Vertices.size());
				FbxVector4* lControlPoints = lMesh->GetControlPoints();

				// This is where we will define our normals.
				lMesh->CreateLayer();
				FbxLayer* lLayer = lMesh->GetLayer(0);

				// Create a normal layer.
				FbxLayerElementNormal* lLayerElementNormal = FbxLayerElementNormal::Create(lMesh, "");
				FbxLayerElementBinormal* lLayerElementBinormal = FbxLayerElementBinormal::Create(lMesh, "");
				FbxLayerElementTangent * lLayerElementTangent = FbxLayerElementTangent::Create(lMesh, "");
				FbxLayerElementUV * lLayerElementTexCoord = FbxLayerElementUV::Create(lMesh, "");
				FbxLayerElementVertexColor* lLayerElementColor = FbxLayerElementVertexColor::Create(lMesh, "");

				// Set its mapping mode to map each normal vector to each control point.
				lLayerElementNormal->SetMappingMode(FbxLayerElement::eByControlPoint);
				lLayerElementBinormal->SetMappingMode(FbxLayerElement::eByControlPoint);
				lLayerElementTangent->SetMappingMode(FbxLayerElement::eByControlPoint);
				lLayerElementTexCoord->SetMappingMode(FbxLayerElement::eByControlPoint);
				lLayerElementColor->SetMappingMode(FbxLayerElement::eByControlPoint);

				// Set the reference mode of so that the n'th element of the normal array maps to the n'th
				// element of the control point array.
				lLayerElementNormal->SetReferenceMode(FbxLayerElement::eDirect);
				lLayerElementBinormal->SetReferenceMode(FbxLayerElement::eDirect);
				lLayerElementTangent->SetReferenceMode(FbxLayerElement::eDirect);
				lLayerElementTexCoord->SetReferenceMode(FbxLayerElement::eDirect);
				lLayerElementColor->SetReferenceMode(FbxLayerElement::eDirect);

				for (uint32 j = 0; j < m_aMeshes[i]->Vertices.size(); j++)
				{
					auto v = m_aMeshes[i]->Vertices[j];
					FbxVector4 Position(v.Pos.x, v.Pos.y, v.Pos.z);
					FbxVector4 Normal(v.Normal.x, v.Normal.y, v.Normal.z);
					FbxVector4 Binormal(v.Bitangent.x, v.Bitangent.y, v.Bitangent.z);
					FbxVector4 Tangent(v.Tangent.x, v.Tangent.y, v.Tangent.z);
					FbxVector2 TexCoord(v.TexCoord.x, v.TexCoord.y);
					FbxColor Color(v.Color.R, v.Color.G, v.Color.B, v.Color.A);

					lControlPoints[j] = Position;
					//lMesh->SetControlPointAt(Position, j);
					lLayerElementNormal->GetDirectArray().Add(Normal);
					lLayerElementBinormal->GetDirectArray().Add(Binormal);
					lLayerElementTangent->GetDirectArray().Add(Tangent);
					lLayerElementTexCoord->GetDirectArray().Add(TexCoord);
					lLayerElementColor->GetDirectArray().Add(Color);
				}

				for (uint32 j = 0; j < m_aMeshes[i]->Faces.size(); j++)
				{
					lMesh->BeginPolygon();
					lMesh->AddPolygon(m_aMeshes[i]->Faces[j].Indices[0]);
					lMesh->AddPolygon(m_aMeshes[i]->Faces[j].Indices[1]);
					lMesh->AddPolygon(m_aMeshes[i]->Faces[j].Indices[2]);
					lMesh->EndPolygon();
				}

				// Finally, we set layer 0 of the mesh to the normal layer element.
				lLayer->SetNormals(lLayerElementNormal);
				lLayer->SetBinormals(lLayerElementBinormal);
				lLayer->SetTangents(lLayerElementTangent);
				lLayer->SetUVs(lLayerElementTexCoord);
				lLayer->SetVertexColors(lLayerElementColor);
			}

			// ... Import a scene, or build a new one ...

			// Export the scene to the file.
			lExporter->Export(lScene);

			bool result = true;
			while (lExporter->IsExporting(result));

			if (!result)
			{
				String msg = "Call to FbxExporter::Export() failed.\n";
				msg += "Error returned : ";
				msg += lExporter->GetStatus().GetErrorString();
				AE_ERROR(msg.c_str());
			}

			// Destroy the exporter.
			lExporter->Destroy();
		}
		else
		{
			String msg = "Error exporting scene ";
			msg += FilePath;
			msg += " : ";
			msg += "Not compatible format.";
			AE_ERROR(msg.c_str());
		}
	}
}