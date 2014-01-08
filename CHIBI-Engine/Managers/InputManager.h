//---------------------------------------------------
//	CHIBI ENGINE v0.1
//  copyright Stijn Doyen
//---------------------------------------------------
//	InputManager.h
//---------------------------------------------------
#pragma once
#include "Manager.h"

#include "MainData.h"
#include "Components/Input.h"
#include "Engine/EngineMath.h"

#include <functional>
#include <vector>
#include <map>
#include <mutex>
#include <thread>

using namespace std;

//!The state of a key
enum KEYSTATE
{
	KEYSTATE_DOWN //!The key is down (it was already down last frame)
	,KEYSTATE_UP //!The key is up (it wasn't pressed last frame)
	,KEYSTATE_PRESSED //!The key is pressed (it wasn't pressed last frame, but it is now)
	, KEYSTATE_RELEASED //!The key is released (it was pressed last frame, but isn't anymore)
	,KEYSTATE_GONE //!The key was removed from the massage-box, but is allowed again (Only for the message-box)
};

//!The manager that checks and handles all input
class InputManager final : public Manager
{
public:

	InputManager();
	~InputManager();
	void Update();
	
	//!Checks the KeyState without taking the message box into account  (if the message got removed, it will still return true)
	bool CheckKeyState(int key, KEYSTATE state);
	//!Checks the KeyState but takes the message box into account (if the message got removed, it will return false)
	bool CheckMessage(int key, KEYSTATE state);
	//!Make sure this input will not be triggered by another object
	void RemoveMessage(int key, KEYSTATE state);

	//!Get the last movement of the mouse
	const Vector2 GetMouseDelta();
	//!Get the current position of the mouse
	const Vector2 GetMousePos();

	//!Returns the next mouse state
	/*!This is used by the input message loop, don't use it unless you know what you are doing
	It can be used to simulate input*/
	MouseState* GetNextMouseState();

	//!Let the manager know a character key has been pressed
	/*!If there is a listener, this method will be fired at every key press to send the character that was pressed
	This method is for instance used for a text box*/
	void HandleCharInput(tchar character);

	//!Adds a listener so the characters of the key presses will be send trough the lambda
	void AddListener(function<void(tchar)> listener);

	//!Remove the listener
	void RemoveListener();
	//!Allow the messages that aren't triggered anymore to be re-added
	DWORD UpdateMessageBox();


private:

	//!The current state of the mouse
	MouseState*					m_CurMouseStatePtr;
	//!The last state of the mouse
	MouseState*					m_PrevMouseStatePtr;
	//!The next state of the mouse
	MouseState*					m_NextMouseStatePtr;

	//!The current state of the keyboard
	KeyboardState*				m_CurKeyboardStatePtr;
	//!The last state of the keyboard
	KeyboardState*				m_PrevKeyboardStatePtr;

	//!The messages that aren't allowed anymore
	multimap<int,KEYSTATE>		m_DeletedMessages;


	//!Is left mouse triggered
	bool						m_LeftMouse;
	//!Is right mouse triggered
	bool						m_RightMouse;
	//!A lambda that will be fired every key press
	function<void(tchar)>		m_Listener;

	//!The handle of the input thread
	HANDLE						m_HandleThread;
	//!The id of the input thread
	DWORD						m_IdThread;
	//!The mutex of the input thread
	mutex						m_MessageBoxMutex;
	//!Is the message box being updated?
	bool						m_Updating;
	//!Is the thread running?
	bool						m_Run;

private:
	InputManager(InputManager& t);
	InputManager& operator=(InputManager& t);
};
