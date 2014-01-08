#pragma once
#include "MainData.h"

class D3DXInitialiser;
class InputManager;


//########################################################################
//	MOUSE STATE
//########################################################################
//!Left mouse button virtual key
#define VK_MOUSE_LEFT 256
//!Right mouse button virtual key
#define VK_MOUSE_RIGHT 257
//!A class that contains information of the state of the mouse at a certain frame
class MouseState final
{
public:
	
	//!Check if a mouse key is down
	bool IsKeyDown(int key)const;
	//!Get the angle of the mouse scroll
	const short GetScroll()const;
	//!Get the position of the mouse cursor
	const POINTS& GetPos()const;

private:

	friend InputManager;
	MouseState(void);
	friend InputManager;
	MouseState(const MouseState& other);
	friend InputManager;
	~MouseState(void);

	friend D3DXInitialiser;
	//!Tell the MouseState where the mouse cursor is located
	/*!This method will be used in the input message loop, only call it manually if you know what you are doing!*/
	void SetPos(const POINTS& newPos);

	friend D3DXInitialiser;
	//!Tell the MouseState a mouse button is pressed or released
	/*!This method will be used in the input message loop, only call it manually if you know what you are doing!*/
	void Setkey(int key, bool pressed);

	friend D3DXInitialiser;
	//!Tell the MouseState the mouse scroll has been rotated
	/*!This method will be used in the input message loop, only call it manually if you know what you are doing!*/
	void Scroll(short delta);

	//!The current position of the mouse
	POINTS m_MousePos;
	//!An integer that contains data of which keys are pressed/released
	int m_MouseKeys;
	//!The amount of scrolling since last update
	short m_DeltaScroll;

private:
	MouseState& operator=(MouseState& t);
};


//########################################################################
//	KEYBOARD STATE
//########################################################################
//!A class that contains information of the state of the keyboard at a certain frame
class KeyboardState final
{
public:

	//!Check if a key is down
	const bool IsKeyDown(int key);
	//!Get the entire keyboard snapshot
	BYTE* GetKeyState();
private:
	//!The keyboard snapshot
	BYTE* m_KeybordState;

private:

	friend InputManager;
	KeyboardState(void);
	friend InputManager;
	~KeyboardState(void);

	//!Set the state of all keys
	/*!This method will be used by the InputManager, only call it manually if you know what you are doing!*/
	friend D3DXInitialiser;
	void SetKeyState(BYTE* newKeyState, bool keepOld = false);

	KeyboardState(KeyboardState& t);
	KeyboardState& operator=(KeyboardState& t);
};