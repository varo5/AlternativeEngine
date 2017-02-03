#pragma once
#include "aeScene.h"

namespace aeEngineSDK
{
	class AE_ENGINE_EXPORT aeOctrisNode
	{
	public:
		aeOctrisNode();
		aeOctrisNode(const aeOctrisNode& O);
		aeOctrisNode(const aeVector3& Min, const aeVector3& Max);
		~aeOctrisNode();

	public:
		bool IsOverloaded(uint32 Max);
		void CreateNewBranches(MultiMap<bool, aeOctrisNode*>& Nodes);
		bool IsEmpty() const;
	public:
		aeAABB m_xBox;
		uint64 m_nFaceCount;
		aeModel m_xModel;
		aeOctrisNode* m_aNodes;
	};

	class AE_ENGINE_EXPORT aeOctris
	{
		/*************************************************************************************************/
		/* Constructors
		/*************************************************************************************************/
	public:
		aeOctris();
		aeOctris(const aeOctris& O);
		~aeOctris();

	public:
		void SegmentMesh(aeScene& Scene, uint32 Max);
		void SaveToFile();
		void SaveToFile(const String& FilePath);

	private:
		MultiMap<bool, aeOctrisNode*> m_aOctriTree;
		Vector<aeMesh*> m_aMeshes;
		aeOctrisNode* m_pRoot;
		String m_pszSceneName;
	};
}