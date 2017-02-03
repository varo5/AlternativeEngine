#pragma once
/*************************************************************************************************/
/* External libraries
/*************************************************************************************************/
#include <tinyxml2.h>

namespace aeEngineSDK
{
	typedef tinyxml2::XMLDocument		aeXMLDocument;
	typedef tinyxml2::XMLElement		aeXMLElement;
	typedef tinyxml2::XMLAttribute		aeXMLAttribute;
	typedef tinyxml2::XMLComment		aeXMLComment;
	typedef tinyxml2::XMLText			aeXMLText;
	typedef tinyxml2::XMLDeclaration	aeXMLDeclaration;
	typedef tinyxml2::XMLUnknown		aeXMLUnknown;
	typedef tinyxml2::XMLPrinter		aeXMLPrinter;
	typedef tinyxml2::XMLNode			aeXMLNode;
	typedef tinyxml2::XMLVisitor		aeXMLVisitor;
	typedef tinyxml2::XMLUtil			aeXMLUtil;
	typedef tinyxml2::XMLHandle			aeXMLHandle;
	typedef tinyxml2::XMLConstHandle	aeXMLConstHandle;
	typedef tinyxml2::XMLError			aeXMLError;
}
