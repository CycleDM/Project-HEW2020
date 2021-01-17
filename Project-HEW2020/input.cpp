//----------------------------------------------------------------------------
// 
// Project-HEW2020 [input.cpp]
// キーボード、マオス、コントローラー等のインプット制御
// 
// Date:   2021/01/17
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include "input.h"
#include <atlstr.h>

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = NULL;}}

HWND Input::m_window;						// Stores the window handle
LPDIRECTINPUT8 Input::m_pDevice;			// Stores the direct input device
LPDIRECTINPUTDEVICE8 Input::m_pMouse;		// Stores the mouse device
DIMOUSESTATE Input::m_mouseState;			// Stores the mouse state

//  Member For Mouse Control
unsigned long Input::m_pressStamp;			// Current press stamp, incremented every frame
unsigned long Input::m_mouseButtonStamp[3];	// Stamps the last frame for each mouse button
POINT Input::m_position;					// Stores the mouse position(cursor)

void Input::Init(HWND hWnd, HINSTANCE hInstance)
{
	// Initialize all members
	Uninit();
	m_window = NULL;
	m_pDevice = NULL;
	m_pMouse = NULL;
	m_mouseState = {};
	m_pressStamp = 0;
	memset(m_mouseButtonStamp, 0, sizeof(m_mouseButtonStamp));
	m_position = { 0, 0 };

	m_window = hWnd;
	// Create Input Device
	DirectInput8Create(hInstance, 0x0800, IID_IDirectInput8, (void**)&m_pDevice, NULL);
	m_pDevice->CreateDevice(GUID_SysMouse, &m_pMouse, NULL);
	m_pMouse->SetDataFormat(&c_dfDIMouse);
	m_pMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	m_pMouse->Acquire();
}

void Input::Uninit()
{
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pMouse);
}

void Input::Update()
{
	static HRESULT hr;
	// Poll the mouse device until it succeeds
	// or returns nothing
	while (true)
	{
		m_pMouse->Poll();
		if (SUCCEEDED(hr = m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseState)))
			break;
		if (hr != DIERR_INPUTLOST && hr != DIERR_NOTACQUIRED)
			return;

		// Reacquire the device if the focus was lost.
		if (FAILED(m_pMouse->Acquire()))
			return;
	}

	// Get the relative(client) position of the mouse
	GetCursorPos(&m_position);
	ScreenToClient(m_window, &m_position);

	// Increment the press stamp (each frame)
	m_pressStamp++;
}

// Return whether specific mouse button was pressed or not
//	Parameters:
//	button ... 0: left. 1: right. 2: middle
bool Input::GetMouseButtonPress(char button)
{
	return (m_mouseState.rgbButtons[button] & 0x80);
}

// Return whether specific mouse button was triggered or not
//	Parameters:
//	button ... 0: left. 1: right. 2: middle
bool Input::GetMouseButtonTrigger(char button)
{
	if (!GetMouseButtonPress(button)) return false;

	bool pressed = true;

	if (m_mouseButtonStamp[button] == m_pressStamp - 1 || m_mouseButtonStamp[button] == m_pressStamp)
	{
		pressed = false;
	}

	m_mouseButtonStamp[button] = m_pressStamp;

	return pressed;
}

// Return the mouse position
long Input::GetMouseX()
{
	return m_position.x;
}

// Return the mouse position
long Input::GetMouseY()
{
	return m_position.y;
}

// Return the mouse moving speed
long Input::GetMouseDeltaX()
{
	return m_mouseState.lX;
}

// Return the mouse moving speed
long Input::GetMouseDeltaY()
{
	return m_mouseState.lY;
}

// Return the mouse wheel speed
long Input::GetMouseDeltaWheel()
{
	return m_mouseState.lZ;
}