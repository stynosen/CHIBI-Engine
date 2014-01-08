//---------------------------------------------------
//	CHIBI ENGINE v0.1
//  copyright Stijn Doyen
//---------------------------------------------------
//	ChibiEngine.h	
//---------------------------------------------------
#pragma once
#include "MainData.h"

class Game;

class SceneManager;
class ImageManager;
class InputManager;
class EffectManager;
class TimerManager;
class FontManager;
class AnimationManager;
class ActionManager;

#include "GameTimer.h"

#include "Debug.h"

#include "D3DXInitialiser.h"
#include "EngineMath.h"

#define CHIBI (ChibiEngine::GetSingleton())
#define D3DXDEVICE (ChibiEngine::GetSingleton()->GetD3DXInit()->GetDevice())

//!The actual engine class
/*!This static class will be the middle-man between your game and all the engine classes and managers.
You can call methods of this class by simply writing CHIBI->NAME_OF_CLASS().*/
class ChibiEngine final
{
public:
	~ChibiEngine(void);
	static	ChibiEngine* GetSingleton();
	void	CreateDX(HINSTANCE hInstance);

	//!Get the pointer to the D3DXInitialiser
	/*!Normally you won't need this, but it can be useful if you want to do graphic related things.
	You can retrieve the D3Device, back buffer, ... by getting it out of this object*/
	D3DXInitialiser*	GetD3DXInit();

	//!Get the current SceneManager
	SceneManager*		GetSceneManager();
	//!Get the current InputManager
	InputManager*		GetInputManager();
	//!Get the current ImageManager
	ImageManager*		GetImageManager();
	//!Get the current EffectManager
	EffectManager*		GetEffectManager();
	//!Get the current TimerManager
	TimerManager*		GetTimerManager();
	//!Get the current FontManager
	FontManager*		GetFontManager();
	//!Get the current AnimationManager
	AnimationManager*	GetAnimationManager();
	//!Get the current ActionManager
	ActionManager*		GetActionManager();
	
	//!Shortcut to retrieve the DeltaTime (in seconds)
	/*!This is the same as calling
	CHIBI->GetTimerManager()->GetDeltaTime()*/
	double				GetDeltaTime();

	//!Shortcut to retrieve the D3DDevice
	/*!This is the same as calling
	CHIBI->GetD3DXInit()->GetD3DDevice()*/
	ID3D10Device*		GetD3DDevice();

	//!Get the current FPS
	/*!This will return the average number of frames in the last second*/
	int					GetFPS();

private:
	ChibiEngine();
	static ChibiEngine* m_EnginePtr;

	//!This updates all the managers of the engine
	/*!This will be called by the game, do not call this yourself or everything will be updated twice*/
	friend Game;
	void Update();

	//!This will notify the engine that 
	/*!This will be called by the graphics handler to notify that the screen has been resized
	The engine will the, notify the SceneManager, which will in its turn notify all the GameObjects*/
	friend D3DXInitialiser;
	void Resize();


	//!this method will update the FPS
	/*!This is called by the game once per frame, do not call it yourself*/
	friend Game;
	void				UpdateFPS();


	D3DXInitialiser*	m_D3DXInitPtr;
	SceneManager*		m_ScenemanagerPtr;
	InputManager*		m_InputManagerPtr;
	ImageManager*		m_ImageManagerPtr;
	EffectManager*		m_EffectManagerPtr;
	TimerManager*		m_TimerManagerPtr;
	FontManager*		m_FontManagerPtr;
	AnimationManager*	m_AnimationManagerPtr;;
	ActionManager*		m_ActionManagerPtr;

	//FPS calculation
	int					m_NrOfFrames;
	int					m_FPS;
	double				m_FPSTime;

private:
	ChibiEngine(ChibiEngine& t);
	ChibiEngine& operator=(ChibiEngine& t);
};