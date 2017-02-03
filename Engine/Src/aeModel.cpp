#include "aeResourceManager.h"
#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace aeEngineSDK
{
	aeModel::aeModel()
	{
		m_pModelPosition = nullptr;
	}

	aeModel::aeModel(const aeModel &Model)
	{
		*this = Model;
		for (uint32 j = 0; j < m_aMeshes.size(); j++)
		{
			for (uint32 i = 0; i < m_aMeshes[j].Faces.size(); i++)
			{
				m_aMeshes[j].Faces[i].Vertices[0] = &m_aMeshes[j].Vertices[m_aMeshes[j].Faces[i].Indices[0]];
				m_aMeshes[j].Faces[i].Vertices[1] = &m_aMeshes[j].Vertices[m_aMeshes[j].Faces[i].Indices[1]];
				m_aMeshes[j].Faces[i].Vertices[2] = &m_aMeshes[j].Vertices[m_aMeshes[j].Faces[i].Indices[2]];
			}
		}
	}

	aeModel::~aeModel()
	{
	}

	bool aeModel::LoadModel(String & Filename)
	{
		// Release the previously loaded mesh (if it exists)
		Clear();

		bool Ret = false;
		Assimp::Importer Importer;

		const aiScene* pScene = Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

		if (pScene)
		{
			m_aMeshes.resize(pScene->mNumMeshes);

			// Initialize the meshes in the scene one by one
			for (uint32 j = 0; j < m_aMeshes.size(); j++)
			{
				const aiMesh* paiMesh = pScene->mMeshes[j];
				m_aMeshes[j].MaterialIndex = paiMesh->mMaterialIndex;

				Vector<aeVertex> Vertices;
				Vector<aeFace> Faces;
				Vector<uint32> Indices;
				const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
				const aiColor4D White4D(1.0f, 1.0f, 1.0f, 1.0f);

				bool bHasPositions = paiMesh->HasPositions();
				bool bHasNormals = paiMesh->HasNormals();
				bool bHasTangentsAndBitangents = paiMesh->HasTangentsAndBitangents();

				for (unsigned int i = 0; i < paiMesh->mNumVertices; i++)
				{
					const aiVector3D* pPos = bHasPositions ? &(paiMesh->mVertices[i]) : &Zero3D;
					const aiVector3D* pNormal = bHasPositions ? &(paiMesh->mNormals[i]) : &Zero3D;
					const aiVector3D* pTangent = bHasTangentsAndBitangents ? &(paiMesh->mTangents[i]) : &Zero3D;
					const aiVector3D* pBiangent = bHasTangentsAndBitangents ? &(paiMesh->mBitangents[i]) : &Zero3D;
					const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
					const aiColor4D* pColor = paiMesh->HasVertexColors(0) ? &(paiMesh->mColors[0][i]) : &White4D;

					aeVertex v;
					v.Pos = aeVector3(pPos->x, pPos->y, pPos->z);
					v.Normal = aeVector3(pNormal->x, pNormal->y, pNormal->z);
					v.Tangent = aeVector3(pTangent->x, pTangent->y, pTangent->z);
					v.Bitangent = aeVector3(pBiangent->x, pBiangent->y, pBiangent->z);
					v.TexCoord = aeVector2(pTexCoord->x, pTexCoord->y);
					v.Color = aeLinearColor(pColor->r, pColor->g, pColor->b, pColor->a);

					Vertices.push_back(v);
				}
				for (uint32 i = 0; i < paiMesh->mNumFaces; i++)
				{
					const aiFace& Face = paiMesh->mFaces[i];
					if(Face.mNumIndices > 3)
						AE_ERROR("There is a face with a higher number of vertex allowed.");
					aeFace f;
					f.Vertices.push_back(&Vertices[Face.mIndices[0]]);
					f.Vertices.push_back(&Vertices[Face.mIndices[1]]);
					f.Vertices.push_back(&Vertices[Face.mIndices[2]]);

					f.Indices[0] = Face.mIndices[0];
					f.Indices[1] = Face.mIndices[1];
					f.Indices[2] = Face.mIndices[2];

					aeVector3 v = 
						Vertices[Face.mIndices[0]].Normal +
						Vertices[Face.mIndices[1]].Normal +
						Vertices[Face.mIndices[2]].Normal;
					f.Normal = v.Normalized();

					Faces.push_back(f);
					Indices.push_back(Face.mIndices[0]);
					Indices.push_back(Face.mIndices[1]);
					Indices.push_back(Face.mIndices[2]);
				}
				m_aMeshes[j].Vertices = Vertices;
				m_aMeshes[j].Indices = Indices;
				m_aMeshes[j].Faces = Faces;
			}

/*

			for (uint32 i = 0; i < pScene->mNumMaterials; i++)
			{
				const aiMaterial* pMaterial = pScene->mMaterials[i];
				m_aTextures.push_back(nullptr);
				if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
				{
					aiString Path;

					if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
					{
						String FullPath = "../Images/";
						FullPath += Path.data;
						m_aTextures[i] = aeGraphicsAPI::Instance().CreateTexture2DFromFile(FullPath.c_str());

						if (!m_aTextures[i])
						{
							printf("Error loading texture '%s'\n", FullPath.c_str());
							Ret = false;
						}
					}
				}
				if (!m_aTextures[i])
				{
					m_aTextures[i] = aeGraphicsAPI::Instance().CreateTexture2DFromFile("..\\Images\\white.png");
					Ret = m_aTextures[i] != nullptr;
				}
			}*/
		}
		else
		{
			String Error = "Error parsing ";
			Error += Filename;
			Error += ": ";
			Error += Importer.GetErrorString();
			AE_ERROR(Error);
		}

		return Ret;
	}

	void aeModel::LoadToGPU()
	{
		Vector<aeMesh>::iterator Mesh = m_aMeshes.begin();

		AEG_INPUT_ELEMENT_DESC DefaultInputLayout[] =
		{
			{ "POSITION", 0, AEG_FORMAT_R32G32B32_FLOAT, 0,0,AEG_INPUT_PER_VERTEX_DATA,0 },
			{ "NORMAL", 0, AEG_FORMAT_R32G32B32_FLOAT, 0,AEG_APPEND_ALIGNED_ELEMENT,AEG_INPUT_PER_VERTEX_DATA,0 },
			{ "TEXCOORD", 0, AEG_FORMAT_R32G32_FLOAT, 0,AEG_APPEND_ALIGNED_ELEMENT,AEG_INPUT_PER_VERTEX_DATA,0 },
			{ "COLOR", 0, AEG_FORMAT_R32G32B32A32_FLOAT, 0,AEG_APPEND_ALIGNED_ELEMENT,AEG_INPUT_PER_VERTEX_DATA,0 },
			{ "TANGENT", 0, AEG_FORMAT_R32G32B32_FLOAT, 0,AEG_APPEND_ALIGNED_ELEMENT,AEG_INPUT_PER_VERTEX_DATA,0 },
			{ "BINORMAL", 0, AEG_FORMAT_R32G32B32_FLOAT, 0,AEG_APPEND_ALIGNED_ELEMENT,AEG_INPUT_PER_VERTEX_DATA,0 }
		};

		for (; Mesh != m_aMeshes.end(); ++Mesh)
		{
			Mesh->pVB = aeGraphicsAPI::Instance().CreateVertexBuffer(sizeof(aeVertex) * Mesh->Vertices.size(), &Mesh->Vertices[0]);
			Mesh->pIB = aeGraphicsAPI::Instance().CreateIndexBuffer(sizeof(uint32) *  Mesh->Indices.size(), &Mesh->Indices[0]);
			Mesh->pIL = aeGraphicsAPI::Instance().CreateInputLayout(sizeof(DefaultInputLayout)/ sizeof(AEG_INPUT_ELEMENT_DESC), DefaultInputLayout, aeRenderer::Instance().GetVertexShader());
		}
		m_xDesc.StartSlot = 0;
		m_xDesc.NumBuffers = 1;
		m_xDesc.VertexSize = sizeof(aeVertex);
		m_xDesc.Topology = AEG_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		m_xFormat = AEG_FORMAT_R32_UINT;

		AEG_BUFFER_DESC ConstBuffer = { 0 };
		ConstBuffer.BindFlags = AEG_BIND_CONSTANT_BUFFER;
		ConstBuffer.ByteWidth = (sizeof(aeMatrix4) + 15) & 0xfffffff0; //sizeof(aeVector3);
		ConstBuffer.CPUAccessFlags = AEG_CPU_ACCESS_WRITE;
		ConstBuffer.Usage = AEG_USAGE_DYNAMIC;
		ConstBuffer.MiscFlags = 0;
		ConstBuffer.StructureByteStride = 0;

		m_pModelPosition = aeGraphicsAPI::Instance().CreateConstantBuffer(&ConstBuffer);
	}

	void aeModel::UnloadFromGPU()
	{
		SAFE_RELEASE(m_pModelPosition);
		
		Vector<aeMesh>::iterator Mesh = m_aMeshes.begin();
		for (; Mesh != m_aMeshes.end(); ++Mesh)
		{
			SAFE_RELEASE(Mesh->pVB);
			SAFE_RELEASE(Mesh->pIB);
			SAFE_RELEASE(Mesh->pIL);
		}
	}

	void aeModel::Clear()
	{
		m_aMeshes.clear();
		m_aMaterials.clear();

		UnloadFromGPU();
	}

	void aeModel::Render(const aeMatrix4& Transform)
	{
		void* pData = aeRenderer::Instance().MapConstantBuffer(m_pModelPosition);
		aeMatrix4* pPosition = (aeMatrix4*)pData;
		*pPosition = Transform;
		aeRenderer::Instance().UnMapConstantBuffer(m_pModelPosition);

		aeRenderer::Instance().SetVertexShaderConstantBuffer(2, 1, m_pModelPosition, aeRenderer::Instance().GetVertexShader());

		Vector<aeMesh>::iterator Mesh = m_aMeshes.begin();

		for (; Mesh != m_aMeshes.end(); ++Mesh)
		{
			m_xDesc.IndexSize = Mesh->Indices.size();
			
			if (Mesh->pIL != aeRenderer::Instance().GetInputLayout())
				aeRenderer::Instance().SetInputLayout(Mesh->pIL);

			aeRenderer::Instance().SetVertexBuffers(m_xDesc, Mesh->pVB);
			aeRenderer::Instance().SetIndexBuffers(m_xFormat, 0, Mesh->pIB);
			aeRenderer::Instance().DrawIndexed(Mesh->Indices.size(), 0, 0);
		}		
	}


	/*************************************************************************************************/
	/* 
	/*************************************************************************************************/

	aeModelResource::aeModelResource()
	{
	}

	aeModelResource::aeModelResource(const aeModelResource & MR)
	{
		*this = MR;
	}

	aeModelResource::~aeModelResource()
	{
	}

	void aeModelResource::Render(const aeMatrix4& Transform)
	{
		m_pModel->Render(Transform);
	}

	void aeModelResource::Release()
	{

	}

	inline AE_ENGINE_RESOURCE_ID aeModelResource::GetID() const
	{
		return AE_ENGINE_RESOURCE_ID::AE_ENGINE_RESOURCE_MODEL;
	}

	inline String aeModelResource::GetName() const
	{
		return m_pModel->m_pszName;
	}

	inline Vector<aeMesh> aeModelResource::GetMeshes()
	{
		return m_pModel->m_aMeshes;
	}

	inline Vector<aeMaterialResource> aeModelResource::GetMaterials()
	{
		return m_pModel->m_aMaterials;
	}

}