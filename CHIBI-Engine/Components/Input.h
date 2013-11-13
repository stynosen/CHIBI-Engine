#pragma once
#include "MainData.h"
//########################################################################
//	MOUSE STATE
//########################################################################

#define VK_MOUSE_LEFT 256
#define VK_MOUSE_RIGHT 257

class MouseState final
{
public:


	MouseState(void);
	MouseState(const MouseState& other);
	~MouseState(void);
	
	//Check if a mousekey is down
	bool IsKeyDown(int key)const;
	//Get the angle of the mouse scroll
	const short GetScroll()const;
	//Get the position of the mouse cursor
	const POINTS& GetPos()const;

	//Tell the MouseState where the mouse cursor is located
	//This method will be used in the input message loop, only call it manualy if you know what you are doing!
	void SetPos(const POINTS& newPos);
	//Tell the MouseState a mousebutton is pressed or released
	//This method will be used in the input message loop, only call it manualy if you know what you are doing!
	void Setkey(int key, bool pressed);
	//Tell the MouseState the mouse scroll has been rotated
	//This method will be used in the input message loop, only call it manualy if you know what you are doing!
	void Scroll(short delta);

private:
	POINTS m_MousePos;
	int m_MouseKeys;
	short m_DeltaScroll;

private:
	MouseState& operator=(MouseState& t);
};


//########################################################################
//	KEYBOARD STATE
//########################################################################
class KeyboardState final
{
public:

	KeyboardState(void);
	~KeyboardState(void);

	//Check if a key is down
	const bool IsKeyDown(int key);
	//Set the state of all keys
	//This method will be used by the inputmanager, only call it manualy if you know what you are doing!
	void SetKeyState(BYTE* newKeyState, bool keepOld = false);
	//get the entire keyboard snapshot
	BYTE* GetKeyState();
private:
	//The keyboard snapshot
	BYTE* m_KeybordState;

private:
	KeyboardState(KeyboardState& t);
	KeyboardState& operator=(KeyboardState& t);
};