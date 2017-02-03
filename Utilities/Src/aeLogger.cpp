#include "aePrerequisitesUtil.h"

#define LINE_TERMINATOR "\r\n"

/*************************************************************************************************/
/* External libraries
/*************************************************************************************************/
#include "aeXMLSystem.h"


namespace aeEngineSDK
{
	/*************************************************************************************************/
	/* @struct	aeTag
	/*
	/* @brief	It stores the tag and message for the output.
	/*************************************************************************************************/

	struct aeTag
	{
		String Tag;
		String Msg;
		String File;
		String Function;
		String Line;
	};

	/*************************************************************************************************/
	/* @struct	LOGGER_DATA
	/*
	/* @brief	A logger data.
	/*************************************************************************************************/

	struct LOGGER_DATA
	{
		String FileName;
		Map<uint32,aeTag> Tags;
		aeCriticalSection TagsLock;
		uint32 Counter;
	};	

	aeLogger::aeLogger(String& FileName)
	{
		m_pData = nullptr;
		m_pData = ae_new<LOGGER_DATA>();

		m_pData->FileName = FileName;
		m_pData->Counter = 0;
	}

	aeLogger::~aeLogger()
	{
		ae_delete(m_pData);
		m_pData = nullptr;
		_Instance() = nullptr;
		IsDestroyed() = true;
	}

	aeLogger::aeLogger(const aeLogger &)
	{
	}

	aeLogger & aeLogger::operator=(const aeLogger &)
	{
		return *this;
	}

	void aeLogger::OnStartUp()
	{
	}

	void aeLogger::OnShutDown()
	{
		SaveToFile();
		m_pData->Tags.clear();
		m_pData->FileName.clear();
	}

	void aeLogger::Log(const String& Tag, const String& Msg, const String& FuncName, const String& SourceFile, const uint32& LineNum)
	{
		aeTag NewLog;

		NewLog.Msg = Msg;

		if (!Tag.empty())
			NewLog.Tag = Tag;
		else
			NewLog.Tag = "NO TAG";

		if (!FuncName.empty())
			NewLog.Function = FuncName;

		if (!SourceFile.empty())
			NewLog.File = SourceFile;

		if (LineNum != 0)
			NewLog.Line = ToString(LineNum);

		while (!m_pData->TagsLock.TryLock());
		m_pData->Tags.insert(Pair<uint32, aeTag>(m_pData->Counter, NewLog));
		m_pData->Counter++;
		m_pData->TagsLock.Unlock();
	}

	void aeLogger::SaveToFile()
	{
		aeXMLDocument XmlFile;
		if (!m_pData->FileName.empty())
		{
			aeXMLError eResult = XmlFile.LoadFile(m_pData->FileName.c_str());

			if (eResult == aeXMLError::XML_ERROR_FILE_NOT_FOUND)
			{
				XmlFile.SaveFile(m_pData->FileName.c_str());
				aeXMLElement* pRoot = XmlFile.NewElement("Root");
				XmlFile.InsertFirstChild(pRoot);
				XmlFile.SaveFile(m_pData->FileName.c_str());
				eResult = XmlFile.LoadFile(m_pData->FileName.c_str());
			}
			else
			{
				aeXMLElement* pRoot = XmlFile.RootElement();
				if (!pRoot)
				{
					pRoot = XmlFile.NewElement("Root");
					XmlFile.InsertFirstChild(pRoot);
					XmlFile.SaveFile(m_pData->FileName.c_str());
					eResult = XmlFile.LoadFile(m_pData->FileName.c_str());
				}
			}
		}
		aeXMLElement* pRoot = XmlFile.RootElement();
		
		for (auto node : m_pData->Tags)
		{
			aeXMLElement* pElement = pRoot->FirstChildElement(node.second.Tag.c_str());

			if (pElement == nullptr)
			{
				pElement = XmlFile.NewElement(node.second.Tag.c_str());
				pRoot->InsertEndChild(pElement);
			}

			aeXMLElement* pList = XmlFile.NewElement("Log_Entry");
			pList->SetText(node.second.Msg.c_str());
			pList->SetAttribute("File",node.second.File.c_str());
			pList->SetAttribute("Function", node.second.Function.c_str());
			pList->SetAttribute("Line", node.second.Line.c_str());
			pElement->InsertEndChild(pList);
		}
		XmlFile.SaveFile(m_pData->FileName.c_str());
		XmlFile.Clear();
	}
}