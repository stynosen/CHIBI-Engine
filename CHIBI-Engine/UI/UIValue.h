#pragma once
#include "Engine/ChibiEngine.h"
#include "UIString.h"

//!A UIElement that can be used to draw the content of a pointer to a HUD
/*!This is very useful when you want to draw the score (the actual score pointer) to the screen. 
This way you don't have to call the SetValue of the UIString every frame.\n
Make sure that the font you want to use to write the text, is added to the FontManager*/
class UIValue : public UIString
{
public:
	enum UIValueType
	{
		UIValueType_INT,UIValueType_UINT,UIValueType_FLOAT,UIValueType_DOUBLE,UIValueType_STRING
	};

	//!Create a value string element that can be drawn on a UI
	UIValue(
		//!The tag of this element, in the UI
		const tstring& tag, 
		//!The address of the data value that you want to draw to the screen
		void* addressPtr, 
		//!The data type of the address
		UIValueType type, 
		//!The draw position on the screen
		const Vector2& pos, 
		//!The color of the string
		const D3DXCOLOR& color = D3DXCOLOR(0,0,0,1), 
		//!The tag of the font
		const tstring& fontTag = _T("Default")
		);

	//!Create a value string element that can be drawn on a UI
	UIValue(
		//!The tag of this element, in the UI
		const tstring& tag,
		//!The address of the data value that you want to draw to the screen
		void* addressPtr,
		//!The data type of the address
		UIValueType type,
		//!The draw x-position on the screen
		double x,
		//!The draw y-position on the screen
		double y,
		//!The color of the string
		const D3DXCOLOR& color = D3DXCOLOR(0, 0, 0, 1),
		//!The tag of the font
		const tstring& fontTag = _T("Default")
		);
	

	//!Change the value to another pointer
	void SetValue(void* adressPtr, UIValueType type);

	//!Set the number of decimals (behind the floating point)
	void SetNrOfDecimals(UINT nr);

	virtual ~UIValue(void);
	virtual void Update();
private:
	void*					m_AddressPtr;
	UIValueType				m_ValueType;

	UINT					m_NrOfDecimals;

	UIValue(UIValue& t);
	UIValue& operator=(UIValue& t);
};