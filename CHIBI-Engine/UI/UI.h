#pragma once
#include "Objects/GameObject.h"
#include "Managers/ImageManager.h"
#include <set>

class UIElement;
class Sprite;

class UI : public GameObject
{
public:
	UI(void);
	virtual ~UI(void);
	
	bool Initialise();
	void Update();
	void Paint();

	void Resize();

	void AddElement(UIElement* elementPtr, bool front=false);
	void RemoveElement(UIElement* elementPtr);
	void RemoveElement(const tstring& tag);

	ID2D1RenderTarget* GetRenderTarget();

	template <class T>
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
		//Check if the object actualy is of the type
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

