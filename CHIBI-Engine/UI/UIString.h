#pragma once
#include "Engine/ChibiEngine.h"
#include "UIElement.h"

class UIString : public UIElement
{

public:
	UIString(const tstring& tag, const tstring& message, const Vector2& pos, const D3DXCOLOR& color = D3DXCOLOR(0,0,0,1), const tstring& fontTag = _T("Default"));
	UIString(const tstring& tag, const tstring& message, double x, double y, const D3DXCOLOR& color = D3DXCOLOR(0,0,0,1), const tstring& fontTag = _T("Default"));
	
	virtual ~UIString(void);

	void Resize();

	void SetColor(const D3DXCOLOR& color);
	void SetFont(const tstring& font);
	void SetValue(const tstring& value);

	virtual bool Initialise();
	virtual void Paint();
	
private:

	D3DXCOLOR				m_Color;
	tstring					m_Message;
	tstring					m_FontTag;

	IDWriteTextLayout*		m_TextLayoutPtr;
	ID2D1SolidColorBrush*	m_BrushPtr;

	UIString(UIString& t);
	UIString& operator=(UIString& t);
};