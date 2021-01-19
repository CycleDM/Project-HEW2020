//----------------------------------------------------------------------------
// 
// C++ Module [input.h]
// Used for controlling with mouse, keyboard and gamepad
// 
// Author: CycleDM (Jin Zhou)
// Date:   2021/01/17
// Update: 2021/01/19
// 
//----------------------------------------------------------------------------
#pragma once

#include <d3dx9.h>
#include <dinput.h>

class Input
{
public:
	static void Init(HWND hWnd, HINSTANCE hInstance);
	static void Uninit();
	static void Update();

	// Return whether specific keyboard key was pressed or not
	//	Parameters:
	//	key ... specific keyboard key [DIK_*]
	static bool GetKeyPress(char key);
	// Return whether specific keyboard key was triggered or not
	//	Parameters:
	//	key ... specific keyboard key [DIK_*]
	static bool GetKeyTrigger(char key);
	
	// Return whether specific mouse button was pressed or not
	//	Parameters:
	//	button ... 0: left. 1: right. 2: middle
	static bool GetMouseButtonPress(char button);
	// Return whether specific mouse button was triggered or not
	//	Parameters:
	//	button ... 0: left. 1: right. 2: middle
	static bool GetMouseButtonTrigger(char button);
	// Return the mouse position
	static long GetMouseX();
	// Return the mouse position
	static long GetMouseY();
	// Return the mouse moving speed
	static long GetMouseDeltaX();
	// Return the mouse moving speed
	static long GetMouseDeltaY();
	// Return the mouse wheel speed
	static long GetMouseDeltaWheel();

private:
	static HWND m_window;							// Stores the window handle
	static LPDIRECTINPUT8 m_pDirectInput;			// DirectInput object
	
	static LPDIRECTINPUTDEVICE8 m_pKeyboard;		// Keyboard device
	static LPDIRECTINPUTDEVICE8 m_pMouse;			// Mouse device
	static DIMOUSESTATE m_mouseState;				// Stores the mouse state

	//  Members for device control
	static unsigned long m_pressStamp;				// Current press stamp, incremented every frame

	static char m_keyState[256];					// Stores the state of the keyboard keys
	static unsigned long m_keyPressStamp[256];		// Stamps the lase frame for each keyboard key
	static unsigned long m_mouseButtonStamp[3];		// Stamps the last frame for each mouse button
	static POINT m_position;						// Stores the mouse position(cursor)
};
