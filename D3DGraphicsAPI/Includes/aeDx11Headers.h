#pragma once

#include <dxgi.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#ifndef SAFE_RELEASE
	#define SAFE_RELEASE(X) if((X)) {(X)->Release(); (X)=NULL;}
#endif

namespace aeEngineSDK
{
	struct GRAPHICS_DATA
	{
		IDXGIAdapter * Adapter;
		ID3D11Device * Device;
		ID3D11DeviceContext* Context;
		IDXGISwapChain* SwapChain;

		ID3D11RenderTargetView* RTV;
		ID3D11DepthStencilView* DSV;

		DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	};

	struct TEXTURE2D_DATA
	{
		ID3D11Texture2D* Texture;
		ID3D11ShaderResourceView* SRV;
	};

	struct INPUTLAYOUT_DATA
	{
		ID3D11InputLayout* InputLayout;
	};

	struct BUFFER_DATA
	{
		ID3D11Buffer* Buffer;
	};

	struct SHADER_DATA
	{
		ID3D10Blob* Blob;
		ID3D11DeviceChild* Shader;
	};
}