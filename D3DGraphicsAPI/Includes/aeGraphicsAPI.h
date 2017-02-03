#pragma once
#include "aePrerequisitesGraphics.h"
#include <aePrerequisitesUtil.h>
#include <aeColor.h>

namespace aeEngineSDK
{
	class aeTexture2D;
	class aeBuffer;
	class aeConstantBuffer;
	class aeIndexBuffer;
	class aeVertexBuffer;
	class aeShader;
	class aeVertexShader;
	class aePixelShader;
	class aeInputLayout;
	class aeRenderer;

	class AE_GRAPHICS_EXPORT aeGraphicsAPI : public Module<aeGraphicsAPI>
	{
	protected:
		uint32 m_nX, m_nY;
		float m_fAspectRatio;
		bool m_bResizeActive;

		GRAPHICS_DATA* m_pData;
		AEG_VIEWPORT m_xViewport;
		aeTexture2D* m_pRenderTarget;
		aeTexture2D* m_pDepthStencil;

		friend class aeRenderer;
	private:
		aeGraphicsAPI(const aeGraphicsAPI&);
	public:
		aeGraphicsAPI();	
		virtual ~aeGraphicsAPI();

		
	protected:
		/*************************************************************************************************/
		/* @fn	virtual void aeGraphicsAPI::OnStartUp();
		/*
		/* @brief	Override if you want to module to be notified once it has been constructed on start.
		/*************************************************************************************************/

		virtual void OnStartUp();

		/*************************************************************************************************/
		/* @fn	virtual void aeGraphicsAPI::OnShutDown();
		/*
		/* @brief	Override if you want to module to be notified once it has been constructed on shut
		/* 			down.
		/*************************************************************************************************/

		virtual void OnShutDown();
	public:
		AE_RESULT			InitializeDevice(SIZE_T Handler);
		AE_RESULT			CreateSwapChain(AEG_SWAP_CHAIN_DESC* pDesc);
		
	public:
		aeTexture2D*		CreateTexture2DFromFile(const String& FileName);
		aeBuffer*			CreateBuffer(AEG_BUFFER_DESC* pBufferDesc, AEG_SUBRESOURCE_DATA* pSubresourceData = nullptr);
		aeConstantBuffer*	CreateConstantBuffer(AEG_BUFFER_DESC* pBufferDesc);
		aeIndexBuffer*		CreateIndexBuffer(uint32 ByteWidth, void* pSysMem);
		aeVertexBuffer*		CreateVertexBuffer(uint32 ByteWidth, void* pSysMem);
		aeShader*			CompileShader(AEG_COMPILE_SHADER_DESC* pDesc);
		aeVertexShader*		CompileVertexShader(AEG_COMPILE_SHADER_DESC* pDesc);
		aePixelShader*		CompilePixelShader(AEG_COMPILE_SHADER_DESC* pDesc);
		aeInputLayout*		CreateInputLayout(uint32 Size, AEG_INPUT_ELEMENT_DESC* pDesc, aeVertexShader* pVertexShader);

	public:
		void Resize(uint32 X, uint32 Y);
		uint32 GetWidth();
		uint32 GetHeight();
		float GetAspectRatio();
	};
}

#include "aeGraphicsResource.h"
#include "aeRenderer.h"
#include "aeTexture2D.h"
#include "aeBuffer.h"
#include "aeConstantBuffer.h"
#include "aeIndexBuffer.h"
#include "aeVertexBuffer.h"
#include "aeShader.h"
#include "aePixelShader.h"
#include "aeVertexShader.h"
#include "aeInputLayout.h"
#include "aeCamera.h"

