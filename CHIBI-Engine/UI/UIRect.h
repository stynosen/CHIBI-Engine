#pragma once
#include "Engine/ChibiEngine.h"
#include "UIElement.h"

class UIRect : public UIElement
{

public:
	UIRect(const tstring& tag, bool filled, const D3DXCOLOR& color, const Rect& values);
	UIRect(const tstring& tag, bool filled, const D3DXCOLOR& color, const Vector2& size, const Vector2& pos);
	UIRect(const tstring& tag, bool filled, const D3DXCOLOR& color, const Vector2& size);
	UIRect(const tstring& tag, bool filled, const D3DXCOLOR& color, double width, double height);
	
	virtual ~UIRect(void);

	void Resize();

	const Vector2& GetSize()const;

	void SetColor(const D3DXCOLOR& color);
	void SetSize(const Vector2& size);

	virtual bool Initialise();
	virtual void Paint();
	
private:

	bool					m_Filled;
	D3DXCOLOR				m_Color;
	Vector2					m_Size;
	
	ID2D1SolidColorBrush*	m_BrushPtr;

	UIRect(UIRect& t);
	UIRect& operator=(UIRect& t);
};