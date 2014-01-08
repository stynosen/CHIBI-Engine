#pragma once
#include "Engine/ChibiEngine.h"
#include "UIElement.h"

//!A UIelement to draw a string on a UI
/*!Make sure that the font you want to use to write the text, is added to the FontManager*/
class UIString : public UIElement
{

public:

	//!Create a string element that can be drawn on a UI
	UIString(
		//!The tag of this element, in the UI
		const tstring& tag, 
		//!The message that should be drawn on the screen
		const tstring& message, 
		//!The position on the screen
		const Vector2& pos, 
		//!The color of the message
		const D3DXCOLOR& color = D3DXCOLOR(0,0,0,1), 
		//!The font tag that should be used to drawn the string
		const tstring& fontTag = _T("Default")
		);

	//!Create a string element that can be drawn on a UI
	UIString(
		//!The tag of this element, in the UI
		const tstring& tag,
		//!The message that should be drawn on the screen
		const tstring& message,
		//!The x position on the screen
		double x,
		//!The y position on the screen
		double y,
		//!The color of the message
		const D3DXCOLOR& color = D3DXCOLOR(0, 0, 0, 1),
		//!The font tag that should be used to drawn the string
		const tstring& fontTag = _T("Default")
		);
	

	//!Change the color of the string
	void SetColor(const D3DXCOLOR& color);

	//!Change the font of the string
	void SetFont(const tstring& font);

	//!Change the content of the string
	void SetValue(const tstring& value);


	virtual ~UIString(void);

	virtual void Resize();

	virtual bool Initialize();
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