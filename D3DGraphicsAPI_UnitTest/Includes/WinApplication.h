#pragma once
#include <aeApplication.h>
#include <aeGraphicsAPI.h>
#include <aeVector4.h>
#include <aeMatrix4.h>
#include <windows.h>

namespace aeEngineSDK
{
	struct Vertex
	{
		aeVector4 Position;
	};

	struct MatrixBuffer
	{
		aeMatrix4 World;
		aeMatrix4 View;
		aeMatrix4 Projection;
	};

	class WinApplication : public aeApplication
	{
	protected:
		virtual AE_RESULT Init();
		virtual AE_RESULT StatusUptade();
		virtual void Render();
		virtual void Destroy();

		bool m_bRunning;

		aeConstantBuffer* m_pCB;
		aeVertexBuffer* m_pVB;
		aeIndexBuffer* m_pIB;
		aeVertexShader* m_pVS;
		aePixelShader* m_pPS;
		aeInputLayout* m_pIL;

		MatrixBuffer m_xCamera;
		Vector<Vertex> m_xModel;
		Vector<uint32> m_xModelIndex;

		MSG m_xMsg;

		String m_pszApplicationName;
		HINSTANCE m_hInstance;
		HWND m_hWnd;

		friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	public:
		WinApplication();
		WinApplication(const WinApplication& A) { *this = A; }
		virtual ~WinApplication() {}

		void Resize(uint32 X, uint32 Y);
	};
}