//----------------------------------------------------------------------------
// 
// Project-HEW2020 [main.cpp]
// メーン関数、総合制御
// 
// Date:   2020/10/22
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include "config.h"
#include "system_timer.h"
#include "keyboard.h"
#include "d3dutility.h"
#include "sprite.h"
#include "game.h"
#include "controller.h"
#include "debug_font.h"

#define CLASS_NAME "GameWindow"
#define WINDOW_CAPTION "ゲームタイトル「未定」"

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool Init(HWND hWnd);
void Update(void);
void Draw(void);
void Uninit(void);

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
static HWND g_hWnd = NULL; // ウィンドウハンドル
static int g_FrameCount = 0;
static int g_BaseFrame = 0;
static double g_BaseTime = 0;
static double g_FPS = 0.0;
static double g_ReserveTime = 0.0f;

//-----------------------------------------------------------------------------
// Window Process
//-----------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Window Class
	WNDCLASS wc = {};
	ZeroMemory(&wc, sizeof(wc));
	wc.lpfnWndProc = WndProc;							// Window Process
	wc.lpszClassName = CLASS_NAME;						// Window Class名
	wc.hInstance = hInstance;							// ウインドウハンドル
	wc.hCursor = LoadCursorA(NULL, IDC_ARROW);			// カーソル
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);	// 背景色
	RegisterClass(&wc);

	const DWORD WINDOW_STYLE = WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX);

	RECT window_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRect(&window_rect, WINDOW_STYLE, FALSE);

	int window_width = window_rect.right - window_rect.left;
	int window_height = window_rect.bottom - window_rect.top;

	// 1.モニターの解像度
	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);
	// 2.バーチャルデスクトップの解像度
	int virtual_desktop_width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int virtual_desktop_height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	// 3.バーチャルデスクトップ左上の座標
	int virtual_desktop_x = GetSystemMetrics(SM_XVIRTUALSCREEN);
	int virtual_desktop_y = GetSystemMetrics(SM_YVIRTUALSCREEN);
	// Offset
	int offset_x = max((desktop_width - window_width) / 2, 0);
	int offset_y = max((desktop_height - window_height) / 2, 0);

	HWND hWnd = CreateWindow(
		CLASS_NAME,
		WINDOW_CAPTION,
		WINDOW_STYLE,
		offset_x, offset_y,
		window_width, window_height,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (NULL == hWnd) return 0;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	if (!Init(hWnd)) return 0;

	// ゲームのメーンループ
	MSG msg = {};
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// ここはゲーム処理
			double time = SystemTimer_GetTime();
			if ((time - g_ReserveTime) < 1.0f / 60.0f)
			{
				Sleep(0);
				continue;
			}
			g_ReserveTime = time;

			Update();
			Draw();
			//Scene_ExecuteChange();
		}
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
	case WM_ACTIVATEAPP:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard_ProcessMessage(uMsg, wParam, lParam);
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, "本当に終了してよろしいですか？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK)
		{
			DestroyWindow(hWnd);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	};

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// ゲームシステムの初期化
bool Init(HWND hWnd)
{
	// Direct3Dの初期化
	if (!D3DUtility_Init(hWnd))
	{
		MessageBox(NULL, "Direct3Dの初期化に失敗しました", "エラー", MB_OK);
		return false;
	}
	
	// ここに各種の初期化処理を入れる
	do
	{
		// キーボードの初期化
		Keyboard_Init();
		// システムタイマーの初期化
		SystemTimer_Init();

		DebugFont_Init();
		Game_Init();
		// ...
		// ...
		// ...
	} while (0);
	g_ReserveTime = g_BaseTime = SystemTimer_GetTime();
	g_FrameCount = g_BaseFrame = 0;
	g_FPS = 0.0;

	return true;
}

// ゲームシステムの更新
void Update(void)
{
	// ここに各種の更新処理を入れる
	do
	{
		Game_Update();
		// ...
		// ...
		// ...
	} while (0);

	// 計測
	double time = SystemTimer_GetTime();
	if (time - g_BaseTime > 1.0)
	{
		g_FPS = (g_FrameCount - g_BaseFrame) / (time - g_BaseTime);
		g_BaseTime = time;
		g_BaseFrame = g_FrameCount;
	}
	g_FrameCount++;
}

// ゲームシステムの描画
void Draw(void)
{
	// Direct3Dデバイスの取得
	LPDIRECT3DDEVICE9 pDevice = D3DUtility_GetDevice();
	if (!pDevice) return;

	// 画面のクリア -> 背景色の指定
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(90, 90, 128, 255), 1.0f, 0);
	// 描画バッチ命令の開始
	pDevice->BeginScene();

	// ここに各種の描画処理を入れる
	do
	{
		Game_Draw();
		// ...
		// ...
		// ...
		// FPS表示
		char buf[64];
		sprintf(buf, "FPS=%.2f", g_FPS);
		DebugFont_Draw(0.0f, 0.0f, buf);
	} while (0);

	// 描画バッチ命令の終了
	pDevice->EndScene();
	// バックバッファをフリップ（タイミングはD3DPRESENT_PARAMETERSの設定による）
	pDevice->Present(NULL, NULL, NULL, NULL);
}

// ゲームシステムの終了処理
void Uninit(void)
{
	Game_Uninit();
	DebugFont_Uninit();
	// Direct3Dの終了処理
	D3DUtility_Uninit();
}