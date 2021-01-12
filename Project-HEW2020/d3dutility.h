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
#include <d3dx9.h>
#include <dinput.h>

class D3DUtility
{
public:
	static bool Init(HWND hWnd, HINSTANCE hInstance);
	static void Uninit(void);
	static LPDIRECT3DDEVICE9 GetDevice(void);
	static void ReadDevice(void);
	static DIMOUSESTATE GetMouseState(void);
	
private:
	static LPDIRECT3D9 pD3D;
	static LPDIRECT3DDEVICE9 pDevice;
	static LPDIRECTINPUT8 pDirectInput;
	static LPDIRECTINPUTDEVICE8 pMouseDevice;
	static DIMOUSESTATE m_state;
};