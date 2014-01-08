#pragma once
#include "Engine/ChibiEngine.h"
#include "UIElement.h"

//!A UIelement to draw a rectangle on a UI
class UIRect : public UIElement
{

public:
	//!Create a rectangle that can be drawn on a UI
	UIRect(
		//!The tag of this element, in the UI
		const tstring& tag, 
		//!Should the rectangle be filled or just lines 
		bool filled, 
		//!The color of the rectangle
		const D3DXCOLOR& color, 
		//!The actual rectangle that has to be drawn
		const Rect& values
		);

	//!Create a rectangle that can be drawn on a UI
	UIRect(
		//!The tag of this element, in the UI
		const tstring& tag,
		//!Should the rectangle be filled or just lines
		bool filled,
		//!The color of the rectangle
		const D3DXCOLOR& color, 
		//!The size of the rectangle (width, height)
		const Vector2& size, 
		//!The position of the rectangle (top-left corner)
		const Vector2& pos
		);

	//!Create a rectangle that can be drawn on a UI
	UIRect(
		//!The tag of this element, in the UI
		const tstring& tag,
		//!Should the rectangle be filled or just lines
		bool filled,
		//!The color of the rectangle
		const D3DXCOLOR& color, 
		//!The size of the rectangle
		const Vector2& size
		);

	//!Create a rectangle that can be drawn on a UI
	UIRect(
		//!The tag of this element, in the UI
		const tstring& tag,
		//!Should the rectangle be filled or just lines
		bool filled,
		//!The color of the rectangle
		const D3DXCOLOR& color, 
		//!The width of the rectangle
		double width, 
		//!The height of the rectangle
		double height
		);
	

	//!Get the size of the rectangle
	const Vector2& GetSize()const;

	//!Change the color of the rectangle
	void SetColor(const D3DXCOLOR& color);
	//!Change the size of the rectangle
	void SetSize(const Vector2& size);



	virtual ~UIRect(void);

	virtual void Resize();

	virtual bool Initialize();
	virtual void Paint();
	
private:

	bool					m_Filled;
	D3DXCOLOR				m_Color;
	Vector2					m_Size;
	
	ID2D1SolidColorBrush*	m_BrushPtr;

	UIRect(UIRect& t);
	UIRect& operator=(UIRect& t);
};