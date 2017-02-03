#include "aeGraphicsAPI.h"
#include "aePrerequisitesGraphics.h"
#include <aeImage.h>
#include <aeMath.h>

namespace aeEngineSDK
{
	aeGraphicsAPI::aeGraphicsAPI()
	{
		m_pDepthStencil = nullptr;
		m_pRenderTarget = nullptr;
		m_pData = nullptr;
	}

	aeGraphicsAPI::aeGraphicsAPI(const aeGraphicsAPI & Reference)
	{
		*this = Reference;
	}

	aeGraphicsAPI::~aeGraphicsAPI()
	{
		_Instance() = nullptr;
		IsDestroyed() = true;
	}

	void aeGraphicsAPI::OnStartUp()
	{
		m_pData = ae_new<GRAPHICS_DATA>();
		m_bResizeActive = false;
	}

	void aeGraphicsAPI::OnShutDown()
	{
		ae_delete(m_pData);
	}

	inline uint32 aeGraphicsAPI::GetWidth()
	{
		return m_nX;
	}

	inline uint32 aeGraphicsAPI::GetHeight()
	{
		return m_nY;
	}

	inline float aeGraphicsAPI::GetAspectRatio()
	{
		return m_fAspectRatio;
	}

	aeTexture2D * aeGraphicsAPI::CreateTexture2DFromFile(const String& FileName)
	{
		aeImage Image;
		Image.LoadFromFilePath(FileName);
		Image.ConvertTo32Bits();
		Image.FlipVertical();

		uint32 width = Image.GetWidth();
		uint32 height = Image.GetHeight();

		uint32 Size = sizeof(aeColor) * width * height;

		ID3D11Texture2D * pTemp = nullptr;
		D3D11_TEXTURE2D_DESC dtd = { 0 };
		dtd.ArraySize = 1;
		dtd.BindFlags = 0;
		dtd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		dtd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		dtd.Height = height;
		dtd.Width = width;
		dtd.MipLevels = 1 + (uint32)floor(log(aeMath::Min(dtd.Width, dtd.Height) / log(2)));
		dtd.SampleDesc.Count = 1;
		dtd.SampleDesc.Quality = 0;
		dtd.Usage = D3D11_USAGE_STAGING;

		HRESULT hResult = m_pData->Device->CreateTexture2D(&dtd, NULL, &pTemp);
		if (FAILED(hResult))
			return nullptr;
		D3D11_MAPPED_SUBRESOURCE ms;
		m_pData->Context->Map(pTemp, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
		memcpy(ms.pData, Image.GetBits(), Size);
		m_pData->Context->Unmap(pTemp, 0);

		Image.Unload();
		
		dtd.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		dtd.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
		dtd.Usage = D3D11_USAGE_DEFAULT;
		dtd.CPUAccessFlags = 0;
		ID3D11Texture2D* pTexture;
		m_pData->Device->CreateTexture2D(&dtd, NULL, &pTexture);
		
		m_pData->Context->CopyResource(pTexture, pTemp);

		ID3D11ShaderResourceView* pSRV = NULL;
		D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
		srvd.Texture2D.MipLevels = dtd.MipLevels;
		srvd.Texture2D.MostDetailedMip = 0;
		srvd.Format = dtd.Format;
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		m_pData->Device->CreateShaderResourceView(pTexture, &srvd, &pSRV);
		m_pData->Context->GenerateMips(pSRV);

		aeTexture2D* NewTexture = new aeTexture2D();
		NewTexture->m_pData->Texture = pTexture;
		NewTexture->m_pData->SRV = pSRV;
		NewTexture->m_pszName = FileName;
		return NewTexture;
	}

	aeBuffer * aeGraphicsAPI::CreateBuffer(AEG_BUFFER_DESC * pBufferDesc, AEG_SUBRESOURCE_DATA * pSubresourceData)
	{
		ID3D11Buffer* pBuff;
		HRESULT hR = m_pData->Device->CreateBuffer((D3D11_BUFFER_DESC*)pBufferDesc, (D3D11_SUBRESOURCE_DATA*)pSubresourceData, &pBuff);

		if (FAILED(hR))
		{
			SAFE_RELEASE(pBuff);
			AE_ERROR("Failed to create buffer.");
			return nullptr;
		}
		aeBuffer* pBuffer = new aeBuffer();
		pBuffer->m_pData->Buffer = pBuff;
		return pBuffer;
	}

	aeConstantBuffer * aeGraphicsAPI::CreateConstantBuffer(AEG_BUFFER_DESC * pBufferDesc)
	{
		ID3D11Buffer* pBuff;

		HRESULT hR = m_pData->Device->CreateBuffer((D3D11_BUFFER_DESC*)pBufferDesc, nullptr, &pBuff);

		if (FAILED(hR))
		{
			SAFE_RELEASE(pBuff);
			AE_ERROR("Failed to constant create buffer.");
			return nullptr;
		}
		aeConstantBuffer* pBuffer = new aeConstantBuffer();
		pBuffer->m_pData->Buffer = pBuff;
		return pBuffer;
	}

	aeIndexBuffer * aeGraphicsAPI::CreateIndexBuffer(uint32 ByteWidth, void * pSysMem)
	{
		ID3D11Buffer* pBuff;

		D3D11_BUFFER_DESC BufferDesc = { 0 };
		D3D11_SUBRESOURCE_DATA SubresourceData = { 0 };

		BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		BufferDesc.ByteWidth = ByteWidth;
		BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		SubresourceData.pSysMem = pSysMem;

		HRESULT hR = m_pData->Device->CreateBuffer(&BufferDesc, &SubresourceData, &pBuff);

		if (FAILED(hR))
		{
			AE_ERROR("Failed to create index buffer.");
			SAFE_RELEASE(pBuff);
			return nullptr;
		}

		aeIndexBuffer* pBuffer = new aeIndexBuffer();
		pBuffer->m_pData->Buffer = pBuff;
		return pBuffer;
	}

	aeVertexBuffer * aeGraphicsAPI::CreateVertexBuffer(uint32 ByteWidth, void * pSysMem)
	{
		ID3D11Buffer* pBuffer = nullptr;

		D3D11_BUFFER_DESC BufferDesc = { 0 };
		D3D11_SUBRESOURCE_DATA SubresourceData = { 0 };

		BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		BufferDesc.ByteWidth = ByteWidth;
		BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		SubresourceData.pSysMem = pSysMem;

		HRESULT hR = m_pData->Device->CreateBuffer(&BufferDesc, &SubresourceData, &pBuffer);

		if (FAILED(hR))
		{
			SAFE_RELEASE(pBuffer);
			AE_ERROR("Failed to create vertex buffer.");
			return nullptr;
		}

		aeVertexBuffer* pVertexBuffer = new aeVertexBuffer();
		pVertexBuffer->m_pData->Buffer = pBuffer;
		return pVertexBuffer;
	}

	aeShader * aeGraphicsAPI::CompileShader(AEG_COMPILE_SHADER_DESC* pDesc)
	{
		ID3D10Blob* pDXIL = nullptr;
		ID3D10Blob* pErrors = nullptr;

		HRESULT hR = D3DCompileFromFile(
			pDesc->FileName.c_str(),
			(D3D_SHADER_MACRO*)pDesc->ShaderMacro,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			pDesc->EntryPoint.c_str(),
			pDesc->Profile.c_str(),
			pDesc->CompileOptimazation,
			pDesc->Flags,
			&pDXIL,
			&pErrors
		);

		if (pErrors)
		{
			AE_ERROR((ANSICHAR*)pErrors->GetBufferPointer());
			SAFE_RELEASE(pErrors);
		}
		if (pDXIL)
		{
			aeShader* pShader = new aeShader();
			pShader->m_pData->Blob = pDXIL;
			return pShader;
		}

		return nullptr;
	}

	aeVertexShader * aeGraphicsAPI::CompileVertexShader(AEG_COMPILE_SHADER_DESC* pDesc)
	{
		ID3D10Blob* pDXIL = nullptr;
		ID3D10Blob* pErrors = nullptr;

		HRESULT hR = D3DCompileFromFile(
			pDesc->FileName.c_str(),
			(D3D_SHADER_MACRO*)pDesc->ShaderMacro,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			pDesc->EntryPoint.c_str(),
			pDesc->Profile.c_str(),
			pDesc->CompileOptimazation,
			pDesc->Flags,
			&pDXIL,
			&pErrors
		);

		if (pErrors)
		{
			AE_ERROR((ANSICHAR*)pErrors->GetBufferPointer());
			SAFE_RELEASE(pErrors);
		}
		if (pDXIL)
		{
			ID3D11VertexShader* pVS = nullptr;

			hR = m_pData->Device->CreateVertexShader(
				pDXIL->GetBufferPointer(),
				pDXIL->GetBufferSize(),
				nullptr,
				&pVS);

			if (FAILED(hR))
			{
				AE_ERROR("Failed to create vertex shader");
				SAFE_RELEASE(pDXIL);
				return nullptr;
			}
			
			aeVertexShader* pShader = new aeVertexShader();
			pShader->m_pData->Blob = pDXIL;
			pShader->m_pData->Shader = pVS;
			return pShader;
		}

		return nullptr;
	}

	aePixelShader * aeGraphicsAPI::CompilePixelShader(AEG_COMPILE_SHADER_DESC* pDesc)
	{
		ID3D10Blob* pDXIL = nullptr;
		ID3D10Blob* pErrors = nullptr;

		HRESULT hR = D3DCompileFromFile(
			pDesc->FileName.c_str(),
			(D3D_SHADER_MACRO*)pDesc->ShaderMacro,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			pDesc->EntryPoint.c_str(),
			pDesc->Profile.c_str(),
			pDesc->CompileOptimazation,
			pDesc->Flags,
			&pDXIL,
			&pErrors
		);

		if (pErrors)
		{
			AE_ERROR((ANSICHAR*)pErrors->GetBufferPointer());
			SAFE_RELEASE(pErrors);
		}
		if (pDXIL)
		{
			ID3D11PixelShader* pPS = nullptr;

			hR = m_pData->Device->CreatePixelShader(
				pDXIL->GetBufferPointer(),
				pDXIL->GetBufferSize(),
				nullptr,
				&pPS);

			SAFE_RELEASE(pDXIL);
			if (FAILED(hR))
			{
				AE_ERROR("Failed to create Pixel shader.");
				return nullptr;
			}

			aePixelShader* pShader = new aePixelShader();
			pShader->m_pData->Blob = nullptr;
			pShader->m_pData->Shader = pPS;
			return pShader;
		}

		return nullptr;
	}

	aeInputLayout * aeGraphicsAPI::CreateInputLayout(uint32 Size, AEG_INPUT_ELEMENT_DESC* pDesc, aeVertexShader * pVertexShader)
	{
		if (pVertexShader)
		{
			ID3D11InputLayout* pIL = nullptr;

			HRESULT hR = m_pData->Device->CreateInputLayout(
				(D3D11_INPUT_ELEMENT_DESC*)pDesc,
				Size,
				pVertexShader->m_pData->Blob->GetBufferPointer(),
				pVertexShader->m_pData->Blob->GetBufferSize(),
				&pIL);

			if (FAILED(hR))
			{
				SAFE_RELEASE(pIL);
				AE_ERROR("Failed to create Input layout.");
				return nullptr;
			}

			aeInputLayout * pInputLayout = new aeInputLayout();
			pInputLayout->m_pData->InputLayout = pIL;
			return pInputLayout;
		}
		return nullptr;
	}

	

	AE_RESULT aeGraphicsAPI::InitializeDevice(SIZE_T Handler)
	{
		IDXGIFactory* pFactory = nullptr;

		HRESULT hR = CreateDXGIFactory(IID_IDXGIFactory, (void**)&pFactory);

		if (FAILED(hR))
		{
			SAFE_RELEASE(pFactory);
			AE_ERROR("Failed to create factory.");
			return hR;
		}

		uint32 i = 0;
		uint32 best = 0;

		hR = E_FAIL;

		do
		{
			hR = pFactory->EnumAdapters(i, &m_pData->Adapter);
			DXGI_ADAPTER_DESC dad = { 0 };
			if (m_pData->Adapter)
			{
				m_pData->Adapter->GetDesc(&dad);
				if (best < dad.DedicatedVideoMemory)
					best = i;
			}
			i++;
		} while (SUCCEEDED(hR));

		pFactory->EnumAdapters(best, &m_pData->Adapter);
		SAFE_RELEASE(pFactory);

		RECT rClient;
		GetClientRect((HWND)Handler, &rClient);

		// Setup the viewport for rendering.
		m_nX = rClient.right - rClient.left;
		m_nY = rClient.bottom - rClient.top;
		m_xViewport.Width = (float)m_nX;
		m_xViewport.Height = (float)m_nY;
		m_xViewport.MinDepth = 0.0f;
		m_xViewport.MaxDepth = 1.0f;
		m_xViewport.TopLeftX = 0.0f;
		m_xViewport.TopLeftY = 0.0f;

		m_fAspectRatio = (float)m_nX / m_nY;

		return hR;
	}

	AE_RESULT aeGraphicsAPI::CreateSwapChain(AEG_SWAP_CHAIN_DESC* pDesc)
	{
		if (m_pData->Device) if(!m_pData->Adapter) return -1; else return -1;

		SAFE_RELEASE(m_pData->Context);
		SAFE_RELEASE(m_pData->SwapChain);

		D3D_FEATURE_LEVEL Requested, Detected;
		Requested = D3D_FEATURE_LEVEL_11_0;

		DXGI_SWAP_CHAIN_DESC dsd = { 0 };
		dsd.BufferCount = pDesc->BufferCount;
		dsd.BufferDesc.Format = (DXGI_FORMAT)pDesc->BufferDesc.Format;
		dsd.BufferDesc.Height = pDesc->BufferDesc.Height;
		dsd.BufferDesc.RefreshRate.Denominator = pDesc->BufferDesc.RefreshRate.Denominator;
		dsd.BufferDesc.RefreshRate.Numerator = pDesc->BufferDesc.RefreshRate.Numerator;
		dsd.BufferDesc.Scaling = (DXGI_MODE_SCALING)pDesc->BufferDesc.Scaling;
		dsd.BufferDesc.ScanlineOrdering = (DXGI_MODE_SCANLINE_ORDER)pDesc->BufferDesc.ScanlineOrdering;
		dsd.BufferDesc.Width = pDesc->BufferDesc.Width;
		dsd.BufferUsage = pDesc->BufferUsage;
		dsd.Flags = pDesc->Flags;
		dsd.OutputWindow = (HWND)pDesc->OutputWindow;
		dsd.SampleDesc.Count = pDesc->SampleDesc.Count;
		dsd.SampleDesc.Quality = pDesc->SampleDesc.Quality;
		dsd.SwapEffect = (DXGI_SWAP_EFFECT)pDesc->SwapEffect;
		dsd.Windowed = pDesc->Windowed;

		HRESULT hR = D3D11CreateDeviceAndSwapChain(
			m_pData->Adapter,
			D3D_DRIVER_TYPE_UNKNOWN,
			NULL,
			NULL,
			&Requested,
			1,
			D3D11_SDK_VERSION,
			&dsd,
			&m_pData->SwapChain,
			&m_pData->Device,
			&Detected,
			&m_pData->Context);

		if (FAILED(hR))
		{
			AE_ERROR("Failed to create swapchain.");
			SAFE_RELEASE(m_pData->Device);
			return hR;
		}

		Resize(pDesc->BufferDesc.Width, pDesc->BufferDesc.Height);
		return hR;
	}

	void aeGraphicsAPI::Resize(uint32 X, uint32 Y)
	{
		if (!m_bResizeActive)
		{
			m_bResizeActive = true;
			if (m_pData->Device)
			{
				m_pData->Context->OMSetRenderTargets(0, 0, 0);

				SAFE_RELEASE(m_pData->DSV);
				SAFE_RELEASE(m_pData->RTV);

				// Setup the viewport for rendering.
				DXGI_FORMAT T = (DXGI_FORMAT)m_pData->SwapChainDesc.BufferDesc.Format;
				HRESULT hR = m_pData->SwapChain->ResizeBuffers(2, X, Y, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

				D3D11_TEXTURE2D_DESC dtdBackbuffer = { 0 };
				ID3D11Texture2D* pBackBuffer = nullptr;
				if (m_pRenderTarget)
				{
					m_pData->SwapChain->GetBuffer(0, IID_ID3D11Texture2D, (void**)&m_pRenderTarget->m_pData->Texture);
					m_pData->Device->CreateRenderTargetView(m_pRenderTarget->m_pData->Texture, 0, &m_pData->RTV);

					m_pRenderTarget->m_pData->Texture->GetDesc(&dtdBackbuffer);
				}
				else
				{
					m_pData->SwapChain->GetBuffer(0, IID_ID3D11Texture2D, (void**)&pBackBuffer);
					m_pData->Device->CreateRenderTargetView(pBackBuffer, 0, &m_pData->RTV);
					pBackBuffer->GetDesc(&dtdBackbuffer);

					SAFE_RELEASE(pBackBuffer);
				}

				D3D11_TEXTURE2D_DESC dtd = { 0 };
				dtd.ArraySize = 1;
				dtd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
				dtd.CPUAccessFlags = 0;
				dtd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				dtd.Height = dtdBackbuffer.Height;
				dtd.Width = dtdBackbuffer.Width;
				dtd.MipLevels = 1;
				dtd.SampleDesc.Count = 1;
				dtd.SampleDesc.Quality = 0;
				dtd.Usage = D3D11_USAGE_DEFAULT;

				if (m_pDepthStencil)
				{
					m_pData->Device->CreateTexture2D(&dtd, 0, &m_pRenderTarget->m_pData->Texture);
					m_pData->Device->CreateDepthStencilView(m_pRenderTarget->m_pData->Texture, 0, &m_pData->DSV);
				}
				else
				{
					ID3D11Texture2D* pDepthBuffer = nullptr;
					m_pData->Device->CreateTexture2D(&dtd, 0, &pDepthBuffer);
					m_pData->Device->CreateDepthStencilView(pDepthBuffer, 0, &m_pData->DSV);

					SAFE_RELEASE(pDepthBuffer);
				}

				

				// Bind the render target view and depth stencil buffer to the output render pipeline.
				m_pData->Context->OMSetRenderTargets(1, &m_pData->RTV, m_pData->DSV);

				// Setup the viewport for rendering.
				m_xViewport.Width = (float)dtdBackbuffer.Width;
				m_xViewport.Height = (float)dtdBackbuffer.Height;
				m_xViewport.MinDepth = 0.0f;
				m_xViewport.MaxDepth = 1.0f;
				m_xViewport.TopLeftX = 0.0f;
				m_xViewport.TopLeftY = 0.0f;

				m_fAspectRatio = m_xViewport.Width / m_xViewport.Height;

				D3D11_VIEWPORT Viewport =
					D3D11_VIEWPORT{
					m_xViewport.TopLeftX ,
					m_xViewport.TopLeftY ,
					m_xViewport.Width ,
					m_xViewport.Height ,
					m_xViewport.MinDepth ,
					m_xViewport.MaxDepth };

				m_pData->Context->RSSetViewports(1, &Viewport);
			}
			m_bResizeActive = false;
		}
	}
}