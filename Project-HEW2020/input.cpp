//----------------------------------------------------------------------------
// 
// C++ Module [input.cpp]
// Used for controlling with mouse, keyboard and gamepad
// 
// Author: CycleDM (Jin Zhou) @HAL_Tokyo_95097_AT12D187_17
// Date:   2021/01/17
// Update: 2021/01/19
// 
//----------------------------------------------------------------------------
#include "input.h"

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

// Macros
#define DIRECTINPUT_VERSION 0x0800
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = NULL;}}

HWND Input::m_window;
LPDIRECTINPUT8 Input::m_pDirectInput;

LPDIRECTINPUTDEVICE8 Input::m_pKeyboard;
LPDIRECTINPUTDEVICE8 Input::m_pMouse;
DIMOUSESTATE Input::m_mouseState;

unsigned long Input::m_recordStamp;

//  Members for device control
char Input::m_keyState[256];
unsigned long Input::m_keyPressStamp[256];
unsigned long Input::m_mouseButtonStamp[3];
POINT Input::m_position;

void Input::Init(HWND hWnd, HINSTANCE hInstance)
{
	// Initialize all members
	Uninit();
	m_window = NULL;
	m_pDirectInput = NULL;
	m_pMouse = NULL;
	m_mouseState = {};
	m_recordStamp = 0;
	memset(m_keyState, 0, sizeof(m_keyState));
	memset(m_keyPressStamp, 0, sizeof(m_keyPressStamp));
	memset(m_mouseButtonStamp, 0, sizeof(m_mouseButtonStamp));
	m_position = { 0, 0 };

	m_window = hWnd;
	if (NULL == hInstance)
	{
		hInstance = GetModuleHandle(NULL);
	}

	// Create Input Devices
	DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL);

	// Keyboard
	m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL);
	m_pKeyboard->SetDataFormat(&c_dfDIKeyboard);
	m_pKeyboard->SetCooperativeLevel(m_window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	m_pKeyboard->Acquire();

	// Mouse
	m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL);
	m_pMouse->SetDataFormat(&c_dfDIMouse);
	m_pMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	m_pMouse->Acquire();
}

void Input::Uninit()
{
	SAFE_RELEASE(m_pMouse);
	SAFE_RELEASE(m_pKeyboard);
	SAFE_RELEASE(m_pDirectInput);
}

void Input::Update()
{
	static HRESULT hr;

	// Poll the keyboard device until it succeeds
	// or returns nothing
	while (true)
	{
		m_pKeyboard->Poll();
		if (SUCCEEDED(hr = m_pKeyboard->GetDeviceState(256, (LPVOID)&m_keyState)))
		{
			break;
		}
		if (hr != DIERR_INPUTLOST && hr != DIERR_NOTACQUIRED)
		{
			return;
		}
		// Reacquire the device if the focus was lost
		if (FAILED(m_pKeyboard->Acquire()))
		{
			return;
		}
	}

	// Poll the mouse device until it succeeds
	// or returns nothing
	while (true)
	{
		m_pMouse->Poll();
		if (SUCCEEDED(hr = m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseState)))
		{
			break;
		}
		if (hr != DIERR_INPUTLOST && hr != DIERR_NOTACQUIRED)
		{
			return;
		}
		// Reacquire the device if the focus was lost
		if (FAILED(m_pMouse->Acquire()))
		{
			return;
		}
	}

	// Get the relative(client) position of the mouse
	GetCursorPos(&m_position);
	ScreenToClient(m_window, &m_position);

	// Increment the press stamp (each frame)
	m_recordStamp++;
}

// Keyboard
bool Input::GetKeyPress(char key)
{
	return (m_keyState[key] & 0x80);
}

bool Input::GetKeyTrigger(char key)
{
	if (!GetKeyPress(key)) return false;

	bool flag = true;

	if (m_keyPressStamp[key] == m_recordStamp - 1 || m_keyPressStamp[key] == m_recordStamp)
	{
		flag = false;
	}

	m_keyPressStamp[key] = m_recordStamp;

	return flag;
}

bool Input::GetKeyRelease(char key)
{
	if (GetKeyPress(key)) return false;
	
	bool flag = !GetKeyPress(key) && !GetKeyTrigger(key);

	if (m_keyPressStamp[key] == m_recordStamp - 1 || m_keyPressStamp[key] == m_recordStamp)
	{
		flag = false;
	}

	m_keyPressStamp[key] = m_recordStamp;

	return flag;
}

// Mouse
bool Input::GetMouseButtonPress(char button)
{
	return (m_mouseState.rgbButtons[button] & 0x80);
}

bool Input::GetMouseButtonTrigger(char button)
{
	if (!GetMouseButtonPress(button)) return false;

	bool flag = true;

	if (m_mouseButtonStamp[button] == m_recordStamp - 1 || m_mouseButtonStamp[button] == m_recordStamp)
	{
		flag = false;
	}

	m_mouseButtonStamp[button] = m_recordStamp;

	return flag;
}

bool Input::GetMouseButtonRelease(char button)
{
	if (GetMouseButtonPress(button)) return false;
	
	bool flag = !GetMouseButtonPress(button) && !GetMouseButtonTrigger(button);

	if (m_mouseButtonStamp[button] == m_recordStamp - 1 || m_mouseButtonStamp[button] == m_recordStamp)
	{
		flag = false;
	}

	m_mouseButtonStamp[button] = m_recordStamp;

	return flag;
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