#pragma once
#include "Engine/ChibiEngine.h"

using namespace std;
class UI;

//!The UIElement base class
/*!All UI elements inherit this base class.\n
You can also create custom UIElements by creating a class that inherits this class*/
class UIElement
{
friend class UI;

public:
	//!The constructor
	UIElement(
		//!The tag that is used to find the element in the UI
		const tstring& tag
		);

	virtual ~UIElement(void);

	//!Show or hide the element
	void SetHidden(bool hidden);

	//!Called whenever the window is resized
	/*!This will be called by the UI. 
	You should not call this method manually, as it won't change anything unless the window is actually resized*/
	virtual void Resize(){};

	//!Check if the element is hidden
	bool IsHidden()const;

	//!Check if the element is initialized
	bool IsInitialized()const;
	
	//!Get the tag of the element
	const tstring& GetTag()const;

	//!Get the position of the element (screen-space)
	const Vector2& GetPos()const;
	
	//!Set the position of the element (screen-space)
	void SetPosition(const Vector2& newPos);
	//!Shift the position of the element (screen-space)
	void Translate(const Vector2& pos);

	//!Initialize the element
	virtual bool Initialize(){ return true; };
	//!Initialize the element
	virtual void Update(){};
	//!Paint the element
	virtual void Paint(){};

	//!Get the address of the UI that contains this UIElement
	UI* GetUI()const;

protected:
	//!Set the UI
	/*!This will not add the element to the UI!.\n
	To add this element to a UI, use the AddElement of the UI instead*/
	void SetUI(UI* uiPtr);
	
	//!The position of the element
	Vector2 m_Position;

	//!The address of the UI object
	UI*		m_UIPtr;

private:

	friend UI;
	void PaintElement();

	friend UI;
	bool InitialiseElement();

	bool	m_Initialised;
	bool	m_Hidden;

	tstring m_Tag;

	UIElement(UIElement& t);
	UIElement& operator=(UIElement& t);
};

