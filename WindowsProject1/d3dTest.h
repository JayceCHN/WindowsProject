#pragma once
#include<d3d9.h>  
#pragma comment(lib, "d3d9.lib")  
#pragma comment(lib, "d3dx9.lib")  
#define WINDOW_CLASS "UGPDX"  
#define WINDOW_NAME "Blank D3D Window"  

class d3dTest
{
public:
	d3dTest();
	~d3dTest();

	bool InitializeD3D(HWND hWnd, bool fullscreen);
	void RenderScene();
	bool IsInit();

	bool bIsInit;
	LPDIRECT3D9 g_D3D = NULL;
	LPDIRECT3DDEVICE9 g_D3DDevice = NULL;
};

