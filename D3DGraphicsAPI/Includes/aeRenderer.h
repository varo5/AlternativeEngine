#pragma once

namespace aeEngineSDK
{
	class AE_GRAPHICS_EXPORT aeRenderer : public Module<aeRenderer>
	{
	protected:
		aeInputLayout* m_pInputLayout;
		aeVertexShader* m_pVertexShader;
		aePixelShader* m_pPixelShader;
		aeGraphicsAPI* m_pInstance;
	private:
		aeRenderer();
		aeRenderer(const aeRenderer&);
		aeRenderer& operator=(const aeRenderer&);
	public:
		aeRenderer(aeGraphicsAPI*);
		virtual ~aeRenderer();

		
	protected:

		/*************************************************************************************************/
		/* @fn	virtual void aeRenderer::OnStartUp();
		/*
		/* @brief	Override if you want to module to be notified once it has been constructed on start.
		/*************************************************************************************************/

		virtual void OnStartUp();

		/*************************************************************************************************/
		/* @fn	virtual void aeRenderer::OnShutDown();
		/*
		/* @brief	Override if you want to module to be notified once it has been constructed on shut
		/* 			down.
		/*************************************************************************************************/

		virtual void OnShutDown();

	public:
		AE_RESULT	LinkDepthStencil(aeTexture2D * Texture);
		AE_RESULT	LinkRenderTarget(aeTexture2D * Texture);

		void SetVertexShader(aeVertexShader* pVS);
		void SetPixelShader(aePixelShader* pPS);
		void SetInputLayout(aeInputLayout* pIL);

		aeVertexShader* GetVertexShader() const;
		aePixelShader* GetPixelShader() const;
		aeInputLayout* GetInputLayout() const;

		void* MapConstantBuffer(aeConstantBuffer* pCB);
		void UnMapConstantBuffer(aeConstantBuffer* pCB);

		void SetVertexShaderConstantBuffer(uint32 Start, uint32 Size, aeConstantBuffer* pCB, aeVertexShader* pVS);
		void SetPixelShaderConstantBuffer(uint32 Start, uint32 Size, aeConstantBuffer* pCB, aePixelShader* pPS);

		void SetVertexBuffers(AEG_VERTEX_BUFFER_DESC& Desc, aeVertexBuffer * pVB);
		void SetIndexBuffers(AEG_FORMAT& Format, uint32 Offset, aeIndexBuffer * pIB);

		void DrawIndexed(uint32 IndexCount, uint32 StartIndexLocation, int32 BaseVertexLocation);

		void Clear(aeLinearColor& Color);
		void ResetBackBufferRenderTarget();
		void ResetViewPort();
		void EndScene();
	};
}