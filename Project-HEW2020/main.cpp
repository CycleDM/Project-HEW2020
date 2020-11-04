//----------------------------------------------------------------------------
// 
// Project-HEW2020 [main.cpp]
// ���[���֐��A��������
// 
// Date:   2020/10/22
// Author: AT12D187_17_���i
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
#define WINDOW_CAPTION "�Q�[���^�C�g���u����v"

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool Init(HWND hWnd);
void Update(void);
void Draw(void);
void Uninit(void);

//-----------------------------------------------------------------------------
// �O���[�o���ϐ��錾
//-----------------------------------------------------------------------------
static HWND g_hWnd = NULL; // �E�B���h�E�n���h��
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
	wc.lpszClassName = CLASS_NAME;						// Window Class��
	wc.hInstance = hInstance;							// �E�C���h�E�n���h��
	wc.hCursor = LoadCursorA(NULL, IDC_ARROW);			// �J�[�\��
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);	// �w�i�F
	RegisterClass(&wc);

	const DWORD WINDOW_STYLE = WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX);

	RECT window_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRect(&window_rect, WINDOW_STYLE, FALSE);

	int window_width = window_rect.right - window_rect.left;
	int window_height = window_rect.bottom - window_rect.top;

	// 1.���j�^�[�̉𑜓x
	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);
	// 2.�o�[�`�����f�X�N�g�b�v�̉𑜓x
	int virtual_desktop_width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int virtual_desktop_height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	// 3.�o�[�`�����f�X�N�g�b�v����̍��W
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

	// �Q�[���̃��[�����[�v
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
			// �����̓Q�[������
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
		if (MessageBox(hWnd, "�{���ɏI�����Ă�낵���ł����H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK)
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

// �Q�[���V�X�e���̏�����
bool Init(HWND hWnd)
{
	// Direct3D�̏�����
	if (!D3DUtility_Init(hWnd))
	{
		MessageBox(NULL, "Direct3D�̏������Ɏ��s���܂���", "�G���[", MB_OK);
		return false;
	}
	
	// �����Ɋe��̏���������������
	do
	{
		// �L�[�{�[�h�̏�����
		Keyboard_Init();
		// �V�X�e���^�C�}�[�̏�����
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

// �Q�[���V�X�e���̍X�V
void Update(void)
{
	// �����Ɋe��̍X�V����������
	do
	{
		Game_Update();
		// ...
		// ...
		// ...
	} while (0);

	// �v��
	double time = SystemTimer_GetTime();
	if (time - g_BaseTime > 1.0)
	{
		g_FPS = (g_FrameCount - g_BaseFrame) / (time - g_BaseTime);
		g_BaseTime = time;
		g_BaseFrame = g_FrameCount;
	}
	g_FrameCount++;
}

// �Q�[���V�X�e���̕`��
void Draw(void)
{
	// Direct3D�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = D3DUtility_GetDevice();
	if (!pDevice) return;

	// ��ʂ̃N���A -> �w�i�F�̎w��
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(90, 90, 128, 255), 1.0f, 0);
	// �`��o�b�`���߂̊J�n
	pDevice->BeginScene();

	// �����Ɋe��̕`�揈��������
	do
	{
		Game_Draw();
		// ...
		// ...
		// ...
		// FPS�\��
		char buf[64];
		sprintf(buf, "FPS=%.2f", g_FPS);
		DebugFont_Draw(0.0f, 0.0f, buf);
	} while (0);

	// �`��o�b�`���߂̏I��
	pDevice->EndScene();
	// �o�b�N�o�b�t�@���t���b�v�i�^�C�~���O��D3DPRESENT_PARAMETERS�̐ݒ�ɂ��j
	pDevice->Present(NULL, NULL, NULL, NULL);
}

// �Q�[���V�X�e���̏I������
void Uninit(void)
{
	Game_Uninit();
	DebugFont_Uninit();
	// Direct3D�̏I������
	D3DUtility_Uninit();
}