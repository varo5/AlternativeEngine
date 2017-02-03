#pragma once
#include "aeGraphicsResource.h"

namespace aeEngineSDK
{
	enum struct AE_GRAPHICS_EXPORT AE_TEXTURE_TYPE
	{
		AE_TEXTURE_TYPE_NONE,
		AE_TEXTURE_TYPE_DIFFUSE,
		AE_TEXTURE_TYPE_SPECULAR,
		AE_TEXTURE_TYPE_AMBIENT,
		AE_TEXTURE_TYPE_EMISSIVE,
		AE_TEXTURE_TYPE_HEIGHT,
		AE_TEXTURE_TYPE_NORMALS,
		AE_TEXTURE_TYPE_SHININESS,
		AE_TEXTURE_TYPE_OPACITY,
		AE_TEXTURE_TYPE_DISPLACEMENT,
		AE_TEXTURE_TYPE_LIGHTMAP,
		AE_TEXTURE_TYPE_REFLECTION,
		AE_TEXTURE_TYPE_UNKNOWN
	};

	class AE_GRAPHICS_EXPORT aeTexture2D : public aeGraphicsResource
	{
	private:
		aeTexture2D();

		friend class aeGraphicsAPI;
		friend class aeRenderer;

		TEXTURE2D_DATA* m_pData;
		String m_pszName;
		AE_TEXTURE_TYPE m_xType;
	public:
		aeTexture2D(const aeTexture2D& T);
		~aeTexture2D();

		void Release();
		void SetType(AE_TEXTURE_TYPE Type);

		String GetName() const;
		AE_TEXTURE_TYPE GetType();
	};
}
