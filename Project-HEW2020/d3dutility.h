//----------------------------------------------------------------------------
// 
// Project-HEW2020 [d3dutility.h]
// Direct3D関連モジュール
// 
// Date:   2020/10/22
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#pragma once

#include <d3d9.h>

class D3DUtility
{
public:
	static bool Init(HWND hWnd);
	static void Uninit(void);
	static LPDIRECT3DDEVICE9 GetDevice(void);
	
private:
	static LPDIRECT3D9 pD3D;
	static LPDIRECT3DDEVICE9 pDevice;
};