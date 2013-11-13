#pragma once
#include "Engine/ChibiEngine.h"

using namespace std;
class UI;

class UIElement
{
friend class UI;

public:
	UIElement(const tstring& tag);
	virtual ~UIElement(void);
	void SetHidden(bool hidden);

	virtual void Resize(){};

	bool IsHidden()const;
	bool IsInitialised()const;
	
	const tstring& GetTag()const;

	const Vector2& GetPos()const;
	
	void SetPosition(const Vector2& newPos);
	void Translate(const Vector2& pos);

	virtual bool Initialise(){ return true; };
	virtual void Update(){};
	virtual void Paint(){};

	void PaintElement();
	bool InitialiseElement();

	UI* GetUI()const;

protected:
	void SetUI(UI* uiPtr);
	
	Vector2 m_Position;
	UI*		m_UIPtr;

private:
	bool	m_Initialised;
	bool	m_Hidden;

	tstring m_Tag;

	UIElement(UIElement& t);
	UIElement& operator=(UIElement& t);
};

