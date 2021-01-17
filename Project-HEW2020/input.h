//----------------------------------------------------------------------------
// 
// Project-HEW2020 [input.h]
// キーボード、マオス、コントローラー等のインプット制御
// 
// Date:   2021/01/17
// Author: AT12D187_17_周進
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
	static HWND m_window;						// Stores the window handle
	static LPDIRECTINPUT8 m_pDevice;			// Stores the direct input device
	static LPDIRECTINPUTDEVICE8 m_pMouse;		// Stores the mouse device
	static DIMOUSESTATE m_mouseState;			// Stores the mouse state

	//  Member For Mouse Control
	static unsigned long m_pressStamp;			// Current press stamp, incremented every frame
	static unsigned long m_mouseButtonStamp[3];	// Stamps the last frame for each mouse button
	static POINT m_position;					// Stores the mouse position(cursor)
};
