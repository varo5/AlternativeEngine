#include "aeGraphicsAPI.h"

namespace aeEngineSDK
{
	aeConstantBuffer::aeConstantBuffer()
	{
	}

	aeConstantBuffer::aeConstantBuffer(const aeConstantBuffer & B)
	{
		*this = B;
	}

	aeConstantBuffer::~aeConstantBuffer()
	{
	}
}