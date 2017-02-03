#include "aeGraphicsAPI.h"

namespace aeEngineSDK
{
	aeVertexBuffer::aeVertexBuffer()
	{
	}

	aeVertexBuffer::aeVertexBuffer(const aeVertexBuffer & B)
	{
		*this = B;
	}

	aeVertexBuffer::~aeVertexBuffer()
	{
	}
}