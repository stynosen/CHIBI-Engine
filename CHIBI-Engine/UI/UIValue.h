#pragma once
#include "Engine/ChibiEngine.h"
#include "UIElement.h"

class UIValue : public UIElement
{
public:
	enum UIValueType
	{
		UIValueType_INT,UIValueType_UINT,UIValueType_FLOAT,UIValueType_DOUBLE,UIValueType_STRING
	};

	UIValue(const tstring& tag, void* addressPtr, UIValueType type, const Vector2& pos, const D3DXCOLOR& color = D3DXCOLOR(0,0,0,1), const tstring& fontTag = _T("Default"));
	UIValue(const tstring& tag, void* addressPtr, UIValueType type, double x, double y, const D3DXCOLOR& color = D3DXCOLOR(0,0,0,1), const tstring& fontTag = _T("Default"));
	
	virtual ~UIValue(void);

	void Resize();

	void SetColor(const D3DXCOLOR& color);
	void SetFont(const tstring& font);
	void SetValue(void* adressPtr, UIValueType type);

	void SetNrOfDecimals(UINT nr);

	virtual bool Initialise();
	virtual void Update();
	virtual void Paint();
	
private:
	void SetString(const tstring& value);

	void*					m_AddressPtr;
	UIValueType				m_ValueType;

	UINT					m_NrOfDecimals;

	D3DXCOLOR				m_Color;
	tstring					m_Message;
	tstring					m_FontTag;

	IDWriteTextLayout*		m_TextLayoutPtr;
	ID2D1SolidColorBrush*	m_BrushPtr;

	UIValue(UIValue& t);
	UIValue& operator=(UIValue& t);
};