#include "aeGraphicsAPI.h"

namespace aeEngineSDK
{
	aeRenderer::aeRenderer()
	{
		m_pInstance = &*aeGraphicsAPI::_Instance();
	}
	aeRenderer::aeRenderer(const aeRenderer &)
	{
	}
	aeRenderer::aeRenderer(aeGraphicsAPI * pInstance)
	{
		m_pInstance = pInstance;
	}
	aeRenderer::~aeRenderer()
	{
	}

	aeRenderer & aeRenderer::operator=(const aeRenderer &)
	{
		return *this;
	}

	void aeRenderer::OnStartUp()
	{
		m_pInputLayout = nullptr;
		m_pVertexShader = nullptr;
		m_pPixelShader = nullptr;
	}

	void aeRenderer::OnShutDown()
	{
		m_pInstance = nullptr;
	}

	void aeRenderer::SetVertexShader(aeVertexShader * pVS)
	{
		m_pVertexShader = pVS;
		m_pInstance->m_pData->Context->VSSetShader((ID3D11VertexShader*)pVS->m_pData->Shader, nullptr, 0);
	}

	void aeRenderer::SetPixelShader(aePixelShader * pPS)
	{
		m_pPixelShader = pPS;
		m_pInstance->m_pData->Context->PSSetShader((ID3D11PixelShader*)pPS->m_pData->Shader, nullptr, 0);
	}

	void aeRenderer::SetInputLayout(aeInputLayout * pIL)
	{
		m_pInputLayout = pIL;
		m_pInstance->m_pData->Context->IASetInputLayout(pIL->m_pData->InputLayout);
	}

	aeVertexShader * aeRenderer::GetVertexShader() const
	{
		return m_pVertexShader;
	}

	aePixelShader * aeRenderer::GetPixelShader() const
	{
		return m_pPixelShader;
	}

	aeInputLayout * aeRenderer::GetInputLayout() const
	{
		return m_pInputLayout;
	}

	void * aeRenderer::MapConstantBuffer(aeConstantBuffer * pCB)
	{
		D3D11_MAPPED_SUBRESOURCE ms = {};

		m_pInstance->m_pData->Context->Map(pCB->m_pData->Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);

		return ms.pData;
	}

	void aeRenderer::UnMapConstantBuffer(aeConstantBuffer * pCB)
	{
		m_pInstance->m_pData->Context->Unmap(pCB->m_pData->Buffer, 0);
	}

	void aeRenderer::SetVertexShaderConstantBuffer(uint32 Start, uint32 Size, aeConstantBuffer * pCB, aeVertexShader * pVS)
	{
		if (pCB && pVS && m_pInstance->m_pData->Context)
		{
			m_pInstance->m_pData->Context->VSSetShader((ID3D11VertexShader*)pVS->m_pData->Shader, nullptr, 0);
			Vector<ID3D11Buffer*> aBuffers;
			for (SIZE_T i = 0; i < Size; i++)
			{
				aBuffers.push_back(pCB[i].m_pData->Buffer);
			}
			m_pInstance->m_pData->Context->VSSetConstantBuffers(Start, Size, &aBuffers[0]);
		}
	}

	void aeRenderer::SetPixelShaderConstantBuffer(uint32 Start, uint32 Size, aeConstantBuffer * pCB, aePixelShader * pPS)
	{
		if (pCB && pPS && m_pInstance->m_pData->Context)
		{
			m_pInstance->m_pData->Context->PSSetShader((ID3D11PixelShader*)pPS->m_pData->Shader, nullptr, 0);
			Vector<ID3D11Buffer*> aBuffers;
			for (SIZE_T i = Start; i < Size; i++)
			{
				aBuffers.push_back(pCB[i].m_pData->Buffer);
			}
			m_pInstance->m_pData->Context->PSSetConstantBuffers(Start, Size, &aBuffers[0]);
		}
	}

	void aeRenderer::SetVertexBuffers(AEG_VERTEX_BUFFER_DESC & Desc, aeVertexBuffer * pVB)
	{
		if (pVB && m_pInstance->m_pData->Context)
		{
			uint32 VertexStride = Desc.VertexSize;
			uint32 VertexOffset = 0;
			D3D11_PRIMITIVE_TOPOLOGY T = (D3D11_PRIMITIVE_TOPOLOGY)Desc.Topology;

			Vector<ID3D11Buffer*> aBuffers;
			for (SIZE_T i = Desc.StartSlot; i < Desc.NumBuffers; i++)
			{
				aBuffers.push_back(pVB[i].m_pData->Buffer);
			}
			m_pInstance->m_pData->Context->IASetVertexBuffers(0, (uint32)aBuffers.size(), &aBuffers[0], &VertexStride, &VertexOffset);
			m_pInstance->m_pData->Context->IASetPrimitiveTopology(T);
		}
	}

	void aeRenderer::SetIndexBuffers(AEG_FORMAT & Format, uint32 Offset, aeIndexBuffer * pIB)
	{
		if (pIB && m_pInstance->m_pData->Context)
		{
			m_pInstance->m_pData->Context->IASetIndexBuffer(pIB->m_pData->Buffer, (DXGI_FORMAT)Format, Offset);
		}
	}

	void aeRenderer::DrawIndexed(uint32 IndexCount, uint32 StartIndexLocation, int32 BaseVertexLocation)
	{
		m_pInstance->m_pData->Context->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
	}

	AE_RESULT aeRenderer::LinkDepthStencil(aeTexture2D * Texture)
	{
		if (m_pInstance->m_pData->Device)
		{
			SAFE_RELEASE(m_pInstance->m_pData->DSV);
			m_pInstance->m_pDepthStencil = Texture;
			HRESULT hR = m_pInstance->m_pData->Device->CreateDepthStencilView(m_pInstance->m_pDepthStencil->m_pData->Texture, 0, &m_pInstance->m_pData->DSV);
			if (FAILED(hR))
			{
				SAFE_RELEASE(m_pInstance->m_pData->DSV);
				return hR;
			}
			m_pInstance->Resize(m_pInstance->GetWidth(), m_pInstance->GetHeight());
			return hR;
		}
		return -1;
	}

	AE_RESULT aeRenderer::LinkRenderTarget(aeTexture2D * Texture)
	{
		if (m_pInstance->m_pData->Device)
		{
			SAFE_RELEASE(m_pInstance->m_pData->RTV);
			m_pInstance->m_pRenderTarget = Texture;
			HRESULT hR = m_pInstance->m_pData->Device->CreateRenderTargetView(m_pInstance->m_pRenderTarget->m_pData->Texture, 0, &m_pInstance->m_pData->RTV);
			if (FAILED(hR))
			{
				SAFE_RELEASE(m_pInstance->m_pData->RTV);
				return hR;
			}
			m_pInstance->Resize(m_pInstance->GetWidth(), m_pInstance->GetHeight());
			return hR;
		}
		return -1;
	}

	void aeRenderer::Clear(aeLinearColor & Color)
	{
		m_pInstance->m_pData->Context->ClearRenderTargetView(m_pInstance->m_pData->RTV, Color.f);
		m_pInstance->m_pData->Context->ClearDepthStencilView(m_pInstance->m_pData->DSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	}

	void aeRenderer::ResetBackBufferRenderTarget()
	{
		// Bind the render target view and depth stencil buffer to the output render pipeline.
		m_pInstance->m_pData->Context->OMSetRenderTargets(1, &m_pInstance->m_pData->RTV, m_pInstance->m_pData->DSV);
	}

	void aeRenderer::ResetViewPort()
	{
		D3D11_VIEWPORT Viewport = 
			D3D11_VIEWPORT{ 
			m_pInstance->m_xViewport.TopLeftX ,
			m_pInstance->m_xViewport.TopLeftY ,
			m_pInstance->m_xViewport.Width ,
			m_pInstance->m_xViewport.Height ,
			m_pInstance->m_xViewport.MinDepth ,
			m_pInstance->m_xViewport.MaxDepth };

		m_pInstance->m_pData->Context->RSSetViewports(1, &Viewport);
	}

	void aeRenderer::EndScene()
	{
		m_pInstance->m_pData->SwapChain->Present(1, 0);
	}
}