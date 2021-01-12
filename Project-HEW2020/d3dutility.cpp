//----------------------------------------------------------------------------
// 
// Project-HEW2020 [d3dutility.cpp]
// Direct3D関連モジュール
// 
// Date:   2020/10/22
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include "d3dutility.h"
#include "config.h"
#include <atlstr.h>

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
LPDIRECT3D9 D3DUtility::pD3D = NULL;          // Direct3Dインターフェース
LPDIRECT3DDEVICE9 D3DUtility::pDevice = NULL; // Direct3Dデバイスインターフェース
LPDIRECTINPUT8 D3DUtility::pDirectInput = NULL;
LPDIRECTINPUTDEVICE8 D3DUtility::pMouseDevice = NULL;
DIMOUSESTATE D3DUtility::m_state = { 0 };

// Direct3D関連の初期化
bool D3DUtility::Init(HWND hWnd, HINSTANCE hInstance)
{
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (NULL == pD3D)
	{
		MessageBox(NULL, "Direct3Dインターフェースの作成に失敗しました", "エラー", MB_OK);
		return false;
	}

    // デバイスの取得に必要な情報構造体の作成
    D3DPRESENT_PARAMETERS d3dpp = {};
    d3dpp.BackBufferWidth = SCREEN_WIDTH;                       // バックバッファの横幅
    d3dpp.BackBufferHeight = SCREEN_HEIGHT;                     // バックバッファの縦幅
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;                    // バックバッファのフォーマット
    d3dpp.BackBufferCount = 1;                                  // バックバッファの数
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                   // スワップ方法の設定
    d3dpp.Windowed = TRUE;                                      // ウィンドウ or フルスクリン
    d3dpp.EnableAutoDepthStencil = TRUE;                        // 深度バッファ・ステンシルバッファの使用
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                  // 深度バッファ・ステンシルバッファのフォーマット
    d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // フルスクリーン時のリフレッシュレートの指定
    //d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;   // リフレッシュレートとPresent処理の関係
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // リフレッシュレートとPresent処理の関係

    // Create Input Devices
    DirectInput8Create(hInstance, 0x0800, IID_IDirectInput8, (void**)&pDirectInput, NULL);
    pDirectInput->CreateDevice(GUID_SysMouse, &pMouseDevice, NULL);
    pMouseDevice->SetDataFormat(&c_dfDIMouse);
    pMouseDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    pMouseDevice->Acquire();

    // Direct3Dデバイスの取得
    HRESULT hr;
    hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &pDevice);

    // HRESULT型変数は成功や失敗が値として入っているので
    // 失敗や成功だけ判定する場合はマクロを利用する　FAILED(hr) SUCCEEDED(hr)
    if (FAILED(hr)) MessageBox(NULL, "Direct3Dデバイスの取得に失敗しました", "エラー", MB_OK);

    // UVアドレッシングモードの設定
    pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
    pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
    //g_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 255, 0, 255));

    // テクスチャフィルダリングの設定
    pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
    pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
    pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
    //g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    //g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
    //g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
    pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);

    // アルファブレンドの設定
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // アルファブレンドを有効にする
    // 半透明…描画色 = 今から描画するRGB * 今から描画するα + 画面のRGB * ( 1 - 今から描画するα )
    pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    // 頂点カラーとテクスチャのブレンドの設定
    pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

    return true; // 初期化成功
}

// Direct3D関連の終了処理
void D3DUtility::Uninit(void)
{
    if (pDevice)
    {
        pDevice->Release();
        pDevice = NULL;
    }
    if (pD3D)
    {
        pD3D->Release();
        pD3D = NULL;
    }

    if (pMouseDevice)
    {
        pMouseDevice->Unacquire();
        pMouseDevice = NULL;
    }
    if (pDirectInput)
    {
        pDirectInput->Release();
        pDirectInput = NULL;
    }
}

// Direct3Dのデバイスを渡す
LPDIRECT3DDEVICE9 D3DUtility::GetDevice(void)
{
    return pDevice;
}

void D3DUtility::ReadDevice(void)
{
    static HRESULT hr;
    while (true)
    {
        pMouseDevice->Poll();
        if (SUCCEEDED(hr = pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_state)))
            break;
        if (hr != DIERR_INPUTLOST && hr != DIERR_NOTACQUIRED)
            return;

        // Reacquire the device if the focus was lost.
        if (FAILED(pMouseDevice->Acquire()))
            return;
    }
}

DIMOUSESTATE D3DUtility::GetMouseState(void)
{
    D3DUtility::ReadDevice();
    return m_state;
}