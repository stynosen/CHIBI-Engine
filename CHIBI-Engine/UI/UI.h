#pragma once
#include "Objects/GameObject.h"
#include "Managers/ImageManager.h"
#include <set>

class UIElement;
class Sprite;

//!A GameObject that can be used to draw a UI on the screen
/*!To add data, you must create UIElement objects, and add them to this object using the AddElement method.\n
Always make sure the UI is last in the scene, so it's drawn on top of everything (since the UI has no priority!)*/
class UI : public GameObject
{
public:
	UI(void);
	virtual ~UI(void);
	
	virtual bool Initialize();
	virtual void Update();
	virtual void Paint();

	virtual void Resize();

	//!Add a UIElement to the UI
	void AddElement(
		//!The element that should be added
		UIElement* elementPtr, 
		//!Add it to the front (elements in the front are drawn first (behind the rest)
		bool front=false);

	//!Remove an element form the UI
	void RemoveElement(UIElement* elementPtr);

	//!Remove an element form the UI, by searching it by its name
	void RemoveElement(const tstring& tag);

	//!get the Render target that is used to draw the UI upon
	/*!Not yet implemented, so it will return the Render target of the Back-buffer*/
	ID2D1RenderTarget* GetRenderTarget();

	template <class T>
	//!Get a UIElement by its name
	/*!Use the type of the element that you are searching for as the template*/
	T* GetElementByTag(const tstring& tag)
	{
		if(m_UIElementsMap.find(tag)==m_UIElementsMap.end())
		{
			Log(_T("UI Element \"") + tag + _T("\" can't be found in this UI\nCheck the log for errors"), MESSAGE_LEVEL_ERROR);
			return nullptr;
		}

		UIElement* elementPtr = m_UIElementsMap[tag];
		if(elementPtr == nullptr)
			return nullptr;
		//Check if the object actually is of the type
		T* derivedElementPtr = dynamic_cast<T*>(elementPtr);
		ASSERT(derivedElementPtr != nullptr, _T("Mismatching object type"));
		return derivedElementPtr;
	}

private:
	//The D2D texture we can render to a plane
	ID3D10Texture2D*			m_UITexturePtr;
	ID2D1RenderTarget*			m_RenderTargetPtr;
	ID3D10ShaderResourceView*	m_ShaderResourceViewPtr;

	Texture						m_Texture;
	Sprite*						m_SpritePtr;

	//We keep a map and a list so we can search elements in the pair, but keep the order within the list
	list<UIElement*> m_UIElements;
	map<tstring,UIElement*> m_UIElementsMap;

private:
	UI(UI& t);
	UI& operator=(UI& t);
};

