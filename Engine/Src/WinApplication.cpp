#include "WinApplication.h"
#include "..\resource.h"
#include <aePrerequisitesUtil.h>
#include <aeTime.h>
#include <aeGraphicsAPI.h>
#include <aeModel.h>
#include <aeGraphicsAPI.h>
#include <aeMath.h>
#include <aeRendererAddOn.h>
#include <aeScene.h>
#include "aeOctris.h"
#include <windows.h>

namespace aeEngineSDK
{
	WinApplication* ApplicationHandle = nullptr;

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
			ApplicationHandle->Stop();
			return 0;
		}
		// Check if the window is being closed.
		case WM_CLOSE:
		{
			ApplicationHandle->Stop();
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return DefWindowProc(hwnd, umessage, wparam, lparam);
		}
		}
	}

	struct WinAppData
	{
		bool bRunning;

		aeLinearColor xColor;

		aeConstantBuffer* pCB;
		aeVertexBuffer* pVB;
		aeIndexBuffer* pIB;
		aeVertexShader* pVS;
		aePixelShader* pPS;
		aeInputLayout* pIL;

		aeCamera xCamera;
		aeModel xModel;

		MSG xMsg;

		String pszApplicationName;
		HINSTANCE hInstance;
		HWND hWnd;
	};

	WinApplication::WinApplication(String& AppName)
	{
		AE_START_PROCESS_NAMED_LOGGER(AppName);
		m_pData = ae_new<WinAppData>();

		m_pData->pCB = nullptr;
		m_pData->pVB = nullptr;
		m_pData->pIB = nullptr;
		m_pData->pVS = nullptr;
		m_pData->pPS = nullptr;
		m_pData->pIL = nullptr;
	}

	WinApplication::WinApplication(const WinApplication& A)
	{ 
		*this = A; 
	}

	WinApplication::~WinApplication()
	{
		AE_CLOSE_LOGGER();
	}

	AE_RESULT WinApplication::Init()
	{
		m_pData->bRunning = true;
		m_pData->xColor= aeLinearColor(0, 0, 0, 1.0f);

		uint32 cx, cy;

		WNDCLASSEX wcex;
		DEVMODE dmScreenSettings;

		ApplicationHandle = this;

		// Get the instance of this application.
		m_pData->hInstance = GetModuleHandle(NULL);

		// Give the application a name.
		m_pData->pszApplicationName = "Alternative Engine";

		wcex.cbSize = sizeof(WNDCLASSEX);

		// Setup the windows class with default settings.
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = m_pData->hInstance;
		wcex.hIcon = LoadIcon(m_pData->hInstance, MAKEINTRESOURCE(IDI_ICON1));
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = 0;
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = m_pData->pszApplicationName.c_str();
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

		// Register the window class.
		RegisterClassEx(&wcex);

		// Determine the resolution of the clients desktop screen.
		cx = GetSystemMetrics(SM_CXSCREEN)/2;
		cy = GetSystemMetrics(SM_CYSCREEN)/2;

		m_pData->hWnd = CreateWindow(m_pData->pszApplicationName.c_str(), m_pData->pszApplicationName.c_str(), WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0, cx, cy, nullptr, nullptr, m_pData->hInstance, nullptr);

		// Bring the window up on the screen and set it as main focus.
		ShowWindow(m_pData->hWnd, SW_SHOW);
		SetForegroundWindow(m_pData->hWnd);
		SetFocus(m_pData->hWnd);

		RECT ClientRect;

		GetClientRect(m_pData->hWnd, &ClientRect);

		cx = ClientRect.right - ClientRect.left;
		cy = ClientRect.bottom - ClientRect.top;

		// Hide the mouse cursor.
		ShowCursor(true);

		aeGraphicsAPI::StartUp();

		AE_RESULT Result = aeGraphicsAPI::Instance().InitializeDevice((SIZE_T)m_pData->hWnd);

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
		SwChDesc.OutputWindow = (uint32)m_pData->hWnd;
		SwChDesc.SampleDesc.Count = 1;
		SwChDesc.SampleDesc.Quality = 0;
		SwChDesc.SwapEffect = AEG_SWAP_EFFECT_DISCARD;
		SwChDesc.Windowed = true;

		Result = aeGraphicsAPI::Instance().CreateSwapChain(&SwChDesc);
		aeRenderer::StartUp(aeGraphicsAPI::InstancePtr());

		AEG_COMPILE_SHADER_DESC VertexShaderDesc;
		VertexShaderDesc.FileName = L"..\\Shaders\\Default.hlsl";
		VertexShaderDesc.ShaderMacro = nullptr;
		VertexShaderDesc.EntryPoint = "VSMain";
		VertexShaderDesc.Flags = 0;
		VertexShaderDesc.CompileOptimazation = AEG_COMPILE_DEBUG | AEG_COMPILE_ENABLE_STRICTNESS ;
		VertexShaderDesc.Profile = "vs_5_0";
		m_pData->pVS = aeGraphicsAPI::Instance().CompileVertexShader(&VertexShaderDesc);

		AEG_COMPILE_SHADER_DESC PixelShaderDesc;
		PixelShaderDesc.FileName = L"..\\Shaders\\Default.hlsl";
		PixelShaderDesc.ShaderMacro = nullptr;
		PixelShaderDesc.EntryPoint = "PSMain";
		PixelShaderDesc.Flags = 0;
		PixelShaderDesc.CompileOptimazation = AEG_COMPILE_DEBUG | AEG_COMPILE_ENABLE_STRICTNESS;
		PixelShaderDesc.Profile = "ps_5_0";
		m_pData->pPS = aeGraphicsAPI::Instance().CompilePixelShader(&PixelShaderDesc);

		AEG_BUFFER_DESC ConstBuffer = { 0 };
		ConstBuffer.BindFlags = AEG_BIND_CONSTANT_BUFFER;
		ConstBuffer.ByteWidth = (sizeof(aeWorldMatrices) + 15) & 0xfffffff0;
		ConstBuffer.CPUAccessFlags = AEG_CPU_ACCESS_WRITE;
		ConstBuffer.Usage = AEG_USAGE_DYNAMIC;
		ConstBuffer.MiscFlags = 0;
		ConstBuffer.StructureByteStride = 0;
		m_pData->pCB = aeGraphicsAPI::Instance().CreateConstantBuffer(&ConstBuffer);

		aeRenderer::Instance().SetVertexShader(m_pData->pVS);
		aeRenderer::Instance().SetPixelShader(m_pData->pPS);

		m_pData->xCamera.Init();

		m_pData->xCamera.SetWorld(aeMatrix4(1));

		m_pData->xModel.LoadModel(String("..\\Models\\suzanne.fbx"));

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
		m_pData->xCamera.SetViewMatrix(position, lookAt);
		m_pData->xCamera.SetProjectionMatrix(aeVector4{ 0.01f, 100.0f, 3.1416f / 3, float(cx) / cy });

		void* pData = aeRenderer::Instance().MapConstantBuffer(m_pData->pCB);

		aeWorldMatrices* pMatrix = (aeWorldMatrices*)pData;
		pMatrix->World = m_pData->xCamera.GetWorld();
		pMatrix->View = m_pData->xCamera.GetView();
		pMatrix->Projection = m_pData->xCamera.GetProjection();

		aeRenderer::Instance().UnMapConstantBuffer(m_pData->pCB);

		aeRenderer::Instance().SetVertexShaderConstantBuffer(0, 1, m_pData->pCB, m_pData->pVS);

		m_pData->xModel.LoadToGPU();

		ZeroMemory(&m_pData->xMsg, sizeof(MSG));

		aeGameObject* GO = ae_new<aeGameObject>();

		SPtr<aeModel> Ptr = ae_shared_ptr_new<aeModel>(m_pData->xModel);

		aeModelResource MR;
		MR.m_pModel = Ptr;

		aeRendererAddOn* RA = ae_new<aeRendererAddOn>();
		RA->m_xModel = MR;

		GO->AddComponent(RA);

		aeScene Scene("Suzzane");

		Scene.AddGameObject(GO);

		aeOctris Octris;
		Octris.SegmentMesh(Scene, 200);
		Octris.SaveToFile("Test.obj");

		return 0;
	}

	AE_RESULT WinApplication::StatusUptade()
	{
		// Handle the windows messages.
		if (PeekMessage(&m_pData->xMsg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&m_pData->xMsg);
			DispatchMessage(&m_pData->xMsg);
		}

		return (m_pData->bRunning) ? -1 : 0;
	}

	void WinApplication::Render()
	{
		aeRenderer::Instance().Clear(m_pData->xColor);
		
		m_pData->xCamera.Render();
		m_pData->xModel.Render(aeMatrix4(aeMatrix4::Identity()));

		aeRenderer::Instance().EndScene();
	}

	void WinApplication::Destroy()
	{
		m_pData->xModel.UnloadFromGPU();
		m_pData->xModel.Clear();
		SAFE_RELEASE(m_pData->pIB);
		SAFE_RELEASE(m_pData->pIL);
		SAFE_RELEASE(m_pData->pVB);
		SAFE_RELEASE(m_pData->pVS);
		SAFE_RELEASE(m_pData->pCB);

		aeRenderer::Instance().ShutDown();
		aeGraphicsAPI::Instance().ShutDown();
	}

	void WinApplication::Resize(uint32 X, uint32 Y)
	{
		if (aeGraphicsAPI::IsStarted())
			aeGraphicsAPI::Instance().Resize(X, Y);

		if (m_pData->pCB)
		{
			m_pData->xCamera.SetProjectionMatrix(aeVector4{ 0.01f, 100.0f, 3.1416f / 3, float(X) / Y });

			void* pData = aeRenderer::Instance().MapConstantBuffer(m_pData->pCB);

			aeWorldMatrices* pMatrix = (aeWorldMatrices*)pData;
			pMatrix->World = m_pData->xCamera.GetWorld();
			pMatrix->View = m_pData->xCamera.GetView();
			pMatrix->Projection = m_pData->xCamera.GetProjection();

			aeRenderer::Instance().UnMapConstantBuffer(m_pData->pCB);
		}
	}

	void WinApplication::Stop()
	{
		m_pData->bRunning = false;
	}

	
}
