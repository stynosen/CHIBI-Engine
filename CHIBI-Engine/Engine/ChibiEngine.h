//---------------------------------------------------
//	CHIBI ENGINE v0.1
//  copyright Stijn Doyen
//---------------------------------------------------
//	ChibiEngine.h	
//---------------------------------------------------
#pragma once
#include "MainData.h"

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

class ChibiEngine final
{
public:
	~ChibiEngine(void);
	static	ChibiEngine* GetSingleton();
	void	CreateDX(HINSTANCE hInstance);

	void Update();
	void Resize();

	D3DXInitialiser*	GetD3DXInit();
	SceneManager*		GetSceneManager();
	InputManager*		GetInputManager();
	ImageManager*		GetImageManager();
	EffectManager*		GetEffectManager();
	TimerManager*		GetTimerManager();
	FontManager*		GetFontManager();
	AnimationManager*	GetAnimationManager();
	ActionManager*		GetActionManager();
	
	//Shortcuts for easyer use
	double				GetDeltaTime();
	ID3D10Device*		GetD3DDevice();

	//FPS
	void				UpdateFPS();
	int					GetFPS();

private:
	ChibiEngine();
	static ChibiEngine* m_EnginePtr;
	
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