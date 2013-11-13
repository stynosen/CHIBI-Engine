//---------------------------------------------------
//	CHIBI ENGINE v0.1
//  copyright Stijn Doyen
//---------------------------------------------------
//	D3DXInitialiser.h	
//---------------------------------------------------
#pragma once
#include "MainData.h"
#include "DXGIDebug.h"

struct GameSettings
{
	UINT width;
	UINT height;
	std::tstring windowTitle;
	bool enableResize;
	D3DXCOLOR bgColor;
};

class D3DXInitialiser
{
public:
	D3DXInitialiser(HINSTANCE hInstance);
	virtual ~D3DXInitialiser(void);
	
	//Public memberfunctions
	bool						Initialise();
	bool						OnResize();

	static LRESULT CALLBACK		WndProcStatic (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void						PreparePaint();

	ID3D10Device*				GetDevice();	
	IDXGISwapChain*				GetSwapChain();
	ID3D10Texture2D*			GetDepthStencilBuffer();
	ID3D10RenderTargetView*		GetRenderTargetView();
	ID3D10DepthStencilView*		GetDepthStencilView();
	ID2D1Factory*				GetD2DFactory();
	ID2D1RenderTarget*			GetBackBufferRenderTarget();

	HWND						GetWindow();
	HINSTANCE					GetHINSTANCE();
	const std::tstring&			GetTitle()const;

	int							GetWidth();
	void						SetWidth(int width);
	
	int							GetHeight();
	void						SetHeight(int height);

	void						SetWindowTitle(const std::tstring& title);
	bool						IsRunning();

	void						SetBGColor(const D3DXCOLOR& color);

	void						EnableResize(bool enable);


private:
	//Private memberfunctions
	bool						OpenWindow();
	HRESULT						CreateD3DDeviceAndSwapchain(IDXGIAdapter *pAdapter, D3D10_DRIVER_TYPE driverType, UINT flags, ID3D10Device1 **ppDevice, IDXGISwapChain **ppswapChain);
	bool						InitializeDirectX();
	void						SetWindowInfo();

	//Direct X related pointers
	ID3D10Device*				m_D3DDevicePtr;
	ID3D10Device1*				m_D3DDevice1Ptr;
	IDXGISwapChain*				m_SwapChainPtr;
	IDXGIDebug*					m_DXGIDebugPtr;
	ID3D10Texture2D*			m_DepthStencilBufferPtr;
	ID3D10RenderTargetView*		m_RenderTargetViewPtr;
	ID3D10DepthStencilView*		m_DepthStencilViewPtr;
	ID2D1Factory*				m_D2DFactoryPtr;
	ID2D1RenderTarget*			m_BackBufferRenderTargetPtr;
	
	HINSTANCE					m_GameInst;
	HWND						m_MainWindow;

	// Derived class should set these in derived constructor to customize starting values.
	std::tstring				m_WindowTitle;
	D3DXCOLOR					m_BGColor;

	int							m_WindowWidth;
	int							m_WindowHeight;
	int							m_BackbufferWidth;
	int							m_BackbufferHeight;

	bool						m_IsResizing;
	bool						m_IsPaused;
	bool						m_IsMinimized;
	bool						m_IsMaximized;
	bool						m_EnableResize;
};

