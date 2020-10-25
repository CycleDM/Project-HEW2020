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

bool D3DUtility_Init(HWND hWnd);
void D3DUtility_Uninit(void);
LPDIRECT3DDEVICE9 D3DUtility_GetDevice(void);