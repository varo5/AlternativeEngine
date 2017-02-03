#pragma once
#include <aeMath.h>
#include <aeColor.h>
#include <aeGraphicsAPI.h>
#include "aeMaterial.h"

namespace aeEngineSDK
{
	struct AE_ENGINE_EXPORT aeVertex
	{
		aeVector3 Pos;
		aeVector3 Normal;
		aeVector2 TexCoord;
		aeLinearColor Color;
		aeVector3 Tangent;
		aeVector3 Bitangent;
	};

	struct AE_ENGINE_EXPORT aeFace
	{
		Vector<aeVertex*> Vertices;
		uint32 Indices[3];
		aeVector3 Normal;
	};

	struct AE_ENGINE_EXPORT aeMesh
	{
		Vector<aeVertex> Vertices;
		Vector<aeFace> Faces;
		Vector<uint32> Indices;

		uint32 NumIndices;
		uint32 MaterialIndex;

		aeMaterialResource pMaterial;

		aeVertexBuffer* pVB;
		aeIndexBuffer* pIB;
		aeInputLayout* pIL;
	};

	class AE_ENGINE_EXPORT aeModel
	{
	public:
		aeModel();
		aeModel(const aeModel&);
		~aeModel();

		bool LoadModel(String& Filename);
		void LoadToGPU();
		void UnloadFromGPU();
		void Clear();
		void Render(const aeMatrix4& Transform);

		Vector<aeMesh> m_aMeshes;
		Vector<aeMaterialResource> m_aMaterials;

		String m_pszName;

	private:
		aeConstantBuffer* m_pModelPosition;		

		AEG_VERTEX_BUFFER_DESC m_xDesc;
		AEG_FORMAT m_xFormat;
	};

	class AE_ENGINE_EXPORT aeModelResource : public aeEngineResource
	{
	public:
		aeModelResource();
		aeModelResource(const aeModelResource&);
		~aeModelResource();
	public:
		void Render(const aeMatrix4& Transform);
		void Release();
		AE_ENGINE_RESOURCE_ID GetID() const override;
		String GetName() const override;

		Vector<aeMesh> GetMeshes();
		Vector<aeMaterialResource> GetMaterials();
	public:
		SPtr<aeModel> m_pModel;
	};
}