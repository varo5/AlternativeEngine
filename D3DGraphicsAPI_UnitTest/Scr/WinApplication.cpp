#include "WinApplication.h"
#include "..\resource.h"
#include <aeString.h>
#include <aeGraphicsAPI.h>
#include <aeMath.h>

#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)

namespace aeEngineSDK
{
	WinApplication* ApplicationHandle = nullptr;
	aeLinearColor Color(0.5f, 0.5f, 0.5f, 1.0f);

	AE_RESULT WinApplication::Init()
	{
		uint32 cx, cy;

		WNDCLASSEX wcex;
		DEVMODE dmScreenSettings;

		ApplicationHandle = this;

		// Get the instance of this application.
		m_hInstance = GetModuleHandle(NULL);

		// Give the application a name.
		m_pszApplicationName = "Alternative Engine";

		wcex.cbSize = sizeof(WNDCLASSEX);

		// Setup the windows class with default settings.
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = m_hInstance;
		wcex.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_ICON1));
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = 0;
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = m_pszApplicationName.c_str();
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

		// Register the window class.
		RegisterClassEx(&wcex);

		// Determine the resolution of the clients desktop screen.
		cx = GetSystemMetrics(SM_CXSCREEN)/2;
		cy = GetSystemMetrics(SM_CYSCREEN)/2;

		m_hWnd = CreateWindow(m_pszApplicationName.c_str(), m_pszApplicationName.c_str(), WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0, cx, cy, nullptr, nullptr, m_hInstance, nullptr);

		// Bring the window up on the screen and set it as main focus.
		ShowWindow(m_hWnd, SW_SHOW);
		SetForegroundWindow(m_hWnd);
		SetFocus(m_hWnd);

		RECT ClientRect;

		GetClientRect(m_hWnd, &ClientRect);

		cx = ClientRect.right - ClientRect.left;
		cy = ClientRect.bottom - ClientRect.top;

		// Hide the mouse cursor.
		ShowCursor(true);

		aeGraphicsAPI::StartUp();

		AE_RESULT Result = aeGraphicsAPI::Instance().InitializeDevice((SIZE_T)m_hWnd);

		AEG_SWAP_CHAIN_DESC SwChDesc = {0};
		SwChDesc.BufferCount = 2;
		SwChDesc.BufferDesc.Format = AEG_FORMAT_R8G8B8A8_UNORM;
		SwChDesc.BufferDesc.Height = cy;
		SwChDesc.BufferDesc.Width = cx;
		SwChDesc.BufferDesc.RefreshRate.Numerator = 0;
		SwChDesc.BufferDesc.RefreshRate.Denominator = 0;
		SwChDesc.BufferDesc.Scaling = AEG_MODE_SCALING_STRETCHED;
		SwChDesc.BufferDesc.ScanlineOrdering = AEG_MODE_SCANLINE_ORDER_PROGRESSIVE;
		SwChDesc.BufferUsage = AEG_USAGE_RENDER_TARGET_OUTPUT | AEG_USAGE_UNORDERED_ACCESS;
		SwChDesc.Flags = 0;
		SwChDesc.OutputWindow = (uint32)m_hWnd;
		SwChDesc.SampleDesc.Count = 1;
		SwChDesc.SampleDesc.Quality = 0;
		SwChDesc.SwapEffect = AEG_SWAP_EFFECT_DISCARD;
		SwChDesc.Windowed = true;

		Result = aeGraphicsAPI::Instance().CreateSwapChain(&SwChDesc);
		aeRenderer::StartUp(aeGraphicsAPI::InstancePtr());

		AEG_COMPILE_SHADER_DESC VertexShaderDesc;
		String BinDir = EXPAND(BIN_DIR);
		wString wBinDir = aeStringUtil::Str2Wstr(BinDir);
		wBinDir.erase(0, 1); // erase the first quote
		wBinDir.erase(wBinDir.size() - 2); // erase the last quote and the dot
		VertexShaderDesc.FileName = wBinDir;
		VertexShaderDesc.FileName += L"Shaders\\BasicVs.hlsl";
		VertexShaderDesc.ShaderMacro = nullptr;
		VertexShaderDesc.EntryPoint = "VSMain";
		VertexShaderDesc.Flags = 0;
		VertexShaderDesc.CompileOptimazation = AEG_COMPILE_DEBUG | AEG_COMPILE_ENABLE_STRICTNESS ;
		VertexShaderDesc.Profile = "vs_5_0";
		m_pVS = aeGraphicsAPI::Instance().CompileVertexShader(&VertexShaderDesc);

		AEG_COMPILE_SHADER_DESC PixelShaderDesc;
		PixelShaderDesc.FileName = wBinDir;
		PixelShaderDesc.FileName += L"Shaders\\BasicPs.hlsl";
		PixelShaderDesc.ShaderMacro = nullptr;
		PixelShaderDesc.EntryPoint = "PSMain";
		PixelShaderDesc.Flags = 0;
		PixelShaderDesc.CompileOptimazation = AEG_COMPILE_DEBUG | AEG_COMPILE_ENABLE_STRICTNESS;
		PixelShaderDesc.Profile = "ps_5_0";
		m_pPS = aeGraphicsAPI::Instance().CompilePixelShader(&PixelShaderDesc);

		AEG_INPUT_ELEMENT_DESC InputLayout[] =
		{
			{ "POSITION", 0, AEG_FORMAT_R32G32B32A32_FLOAT, 0,0,AEG_INPUT_PER_VERTEX_DATA,0 }
		};

		m_pIL = aeGraphicsAPI::Instance().CreateInputLayout(1,InputLayout, m_pVS);

		AEG_BUFFER_DESC ConstBuffer = { 0 };
		ConstBuffer.BindFlags = AEG_BIND_CONSTANT_BUFFER;
		ConstBuffer.ByteWidth = (sizeof(MatrixBuffer) + 15) & 0xfffffff0;
		ConstBuffer.CPUAccessFlags = AEG_CPU_ACCESS_WRITE;
		ConstBuffer.Usage = AEG_USAGE_DYNAMIC;
		ConstBuffer.MiscFlags = 0;
		ConstBuffer.StructureByteStride = 0;
		m_pCB = aeGraphicsAPI::Instance().CreateConstantBuffer(&ConstBuffer);

		m_xCamera.World = aeMatrix4(1);

		aeVector3 position, lookAt;

		// Setup the position of the camera in the world.
		position.x = 0.0f;
		position.y = 5.0f;
		position.z = -2.0f;

		// Setup where the camera is looking by default.
		lookAt.x = 0.0f;
		lookAt.y = 0.0f;
		lookAt.z = 0.0f;

		// Finally create the view matrix from the three updated vectors.
		m_xCamera.View = aeMatrix4::LookAtLH(position, lookAt).Transpose();

		m_xCamera.Projection = aeMatrix4::PerspectiveFOVLH(0.01f, 100.0f, 3.1416f / 3, float(cx)/ cy).Transpose();

		void* pData = aeRenderer::Instance().MapConstantBuffer(m_pCB);

		MatrixBuffer* pMatrix = (MatrixBuffer*)pData;
		pMatrix->World = m_xCamera.World;
		pMatrix->View = m_xCamera.View;
		pMatrix->Projection = m_xCamera.Projection;

		aeRenderer::Instance().UnMapConstantBuffer(m_pCB);

		// Load the vertex array with data.
		m_xModel.resize(4);

		m_xModel[0].Position = aeVector4(0.5f, 0.5f, 0, 1.0f);  //Top right
		m_xModel[1].Position = aeVector4(0.5f, -0.5f, 0, 1.0f); // Bottom right
		m_xModel[2].Position = aeVector4(-0.5f, -0.5f, 0, 1.0f); // Bottom left
		m_xModel[3].Position = aeVector4(-0.5f, 0.5f, 0, 1.0f); // Top Left

		m_pVB = aeGraphicsAPI::Instance().CreateVertexBuffer(sizeof(Vertex) * m_xModel.size(), &m_xModel[0]);

		// Load the index array with data.
		m_xModelIndex.resize(6);

		m_xModelIndex[0] = 3;
		m_xModelIndex[1] = 0;
		m_xModelIndex[2] = 2;
		m_xModelIndex[3] = 0;
		m_xModelIndex[4] = 1;
		m_xModelIndex[5] = 2;

		m_pIB = aeGraphicsAPI::Instance().CreateIndexBuffer(sizeof(uint32) *  m_xModelIndex.size(), &m_xModelIndex[0]);

		aeRenderer::Instance().SetVertexShader(m_pVS);
		aeRenderer::Instance().SetPixelShader(m_pPS);
		aeRenderer::Instance().SetInputLayout(m_pIL);

		AEG_VERTEX_BUFFER_DESC Desc;
		Desc.StartSlot = 0;
		Desc.NumBuffers = 1;
		Desc.IndexSize = m_xModelIndex.size();
		Desc.VertexSize = sizeof(Vertex);
		Desc.Topology = AEG_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		aeRenderer::Instance().SetVertexBuffers(Desc, m_pVB);

		AEG_FORMAT Format = AEG_FORMAT_R32_UINT;
		aeRenderer::Instance().SetIndexBuffers(Format, 0, m_pIB);

		aeRenderer::Instance().SetVertexShaderConstantBuffer(0, 1, m_pCB, m_pVS);

		ZeroMemory(&m_xMsg, sizeof(MSG));

		return 0;
	}

	AE_RESULT WinApplication::StatusUptade()
	{
		// Handle the windows messages.
		if (PeekMessage(&m_xMsg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&m_xMsg);
			DispatchMessage(&m_xMsg);
		}

		return (m_bRunning) ? -1 : 0;
	}

	void WinApplication::Render()
	{
		aeRenderer::Instance().Clear(Color);
		aeRenderer::Instance().DrawIndexed(m_xModelIndex.size(),0,0);
		aeRenderer::Instance().EndScene();
	}

	void WinApplication::Destroy()
	{
		SAFE_RELEASE(m_pIB);
		SAFE_RELEASE(m_pIL);
		SAFE_RELEASE(m_pVB);
		SAFE_RELEASE(m_pVS);
		SAFE_RELEASE(m_pCB);
		aeRenderer::ShutDown();
		aeGraphicsAPI::ShutDown();
	}

	WinApplication::WinApplication()
	{
		m_pCB = nullptr;
		m_pVB = nullptr;
		m_pIB = nullptr;
		m_pVS = nullptr;
		m_pPS = nullptr;
		m_pIL = nullptr;
	}

	void WinApplication::Resize(uint32 X, uint32 Y)
	{
		if (aeGraphicsAPI::IsStarted())
			aeGraphicsAPI::Instance().Resize(X, Y);

		if (m_pCB)
		{
			m_xCamera.Projection = aeMatrix4::PerspectiveFOVLH(0.01f, 100.0f, 3.1416f / 3, float(X) / Y).Transpose();

			void* pData = aeRenderer::Instance().MapConstantBuffer(m_pCB);

			MatrixBuffer* pMatrix = (MatrixBuffer*)pData;
			pMatrix->World = m_xCamera.World;
			pMatrix->View = m_xCamera.View;
			pMatrix->Projection = m_xCamera.Projection;

			aeRenderer::Instance().UnMapConstantBuffer(m_pCB);
		}
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
	{
		switch (umessage)
		{
		case WM_SIZE:
		{
			uint32 cx = LOWORD(lparam);
			uint32 cy = HIWORD(lparam);

			ApplicationHandle->Resize(cx, cy);

			return 0;
		}
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			ApplicationHandle->m_bRunning = false;
			PostQuitMessage(0);
			return 0;
		}
		// Check if the window is being closed.
		case WM_CLOSE:
		{
			ApplicationHandle->m_bRunning = false;
			PostQuitMessage(0);
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return DefWindowProc(hwnd, umessage, wparam, lparam);
		}
		}
	}
}
