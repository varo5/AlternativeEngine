#pragma once
#include "aeGOAddOn.h"
#include "aeTransform.h"
#include "aeModel.h"

namespace aeEngineSDK
{
	class AE_ENGINE_EXPORT aeRendererAddOn : public aeGOAddOn
	{
		friend class aeGOFactory;
	public:
		aeRendererAddOn();
		aeRendererAddOn(const aeRendererAddOn& AO);
		~aeRendererAddOn();

	public:
		AE_RESULT Init() override;
		void Update() override;
		void Destroy() override;

		void Render(const aeTransform& Transform);

		AE_ADD_ON_ID GetComponentId() const override;

	public:
		aeModelResource m_xModel;
	};
}
