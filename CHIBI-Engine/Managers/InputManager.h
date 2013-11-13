//---------------------------------------------------
//	CHIBI ENGINE v0.1
//  copyright Stijn Doyen
//---------------------------------------------------
//	InputManager.h
//---------------------------------------------------
#pragma once
#include "MainData.h"
#include "Components/Input.h"
#include "Engine/EngineMath.h"

#include <functional>
#include <vector>
#include <map>
#include <mutex>
#include <thread>

using namespace std;

enum KEYSTATE
{
	KEYSTATE_DOWN
	,KEYSTATE_UP
	,KEYSTATE_PRESSED
	,KEYSTATE_RELEASED
	,KEYSTATE_GONE
};

class InputManager final
{
public:

	InputManager();
	~InputManager();
	void Update();
	
	//Checks the keystate without taking the messagebox into account  (if the message got removed, it will still return true)
	bool CheckKeyState(int key, KEYSTATE state);
	//Checks the keystate but takes the messagebox into account (if the message got removed, it will return false)
	bool CheckMessage(int key, KEYSTATE state);
	//Make sure this input will not be triggered by another object
	void RemoveMessage(int key, KEYSTATE state);

	const Vector2 GetMouseDelta();
	const Vector2 GetMousePos();

	//This is used by the input message loop, don't use it unless you know what you are doing
	//It can be used to simulate input
	MouseState* GetNextMouseState();

	//If there is a listener, this method will be fired at every keypress to send the character that was pressed
	//This method is for instance used for a textbox
	void HandleCharInput(tchar character);

	//Adds a listener so the characters of the keypesses will be sended wtrough the lambda
	void AddListener(function<void(tchar)> listener);

	//Remove the listener, we don't need it anymore
	void RemoveListener();
	DWORD UpdateMessageBox();


private:

	MouseState*					m_CurMouseStatePtr;
	MouseState*					m_PrevMouseStatePtr;
	MouseState*					m_NextMouseStatePtr;

	KeyboardState*				m_CurKeyboardStatePtr;
	KeyboardState*				m_PrevKeyboardStatePtr;

	multimap<int,KEYSTATE>		m_DeletedMessages;

	bool						m_NewPosSet;
	bool						m_LeftMouse;
	bool						m_RightMouse;
	function<void(tchar)>		m_Listener;

	HANDLE						m_HandleThread;
	DWORD						m_IdThread;
	mutex						m_MessageBoxMutex;
	bool						m_Updating;
	bool						m_Run;

private:
	InputManager(InputManager& t);
	InputManager& operator=(InputManager& t);
};
