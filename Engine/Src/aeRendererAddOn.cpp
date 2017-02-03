#include "aeRendererAddOn.h"

namespace aeEngineSDK
{
	aeRendererAddOn::aeRendererAddOn()
	{
	}

	aeRendererAddOn::aeRendererAddOn(const aeRendererAddOn & AO)
	{
		*this = AO;
	}

	aeRendererAddOn::~aeRendererAddOn()
	{
	}

	AE_RESULT aeRendererAddOn::Init()
	{
		return 0;
	}

	void aeRendererAddOn::Update()
	{
	}

	void aeRendererAddOn::Destroy()
	{
	}

	void aeRendererAddOn::Render(const aeTransform & Transform)
	{
		m_xModel.Render(Transform.GetRealMatrix());
	}

	AE_ADD_ON_ID aeRendererAddOn::GetComponentId() const
	{
		return AE_ADD_ON_ID::AE_RENDERER;
	}
}