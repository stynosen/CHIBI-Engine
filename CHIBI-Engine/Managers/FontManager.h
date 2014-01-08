#pragma once
#include "Manager.h"

#include "Engine/EngineMath.h"
#include "MainData.h"
#include <map>
#include <dwrite.h>

using namespace std;

//!A struct that contains font information
struct Font
{
	Font()
	{
		fontName = _T("");
		tag = _T("");
		italic = false;
		size = 16;
		weight = FW_NORMAL;
		fontPtr = nullptr;
		fontD2DPtr = nullptr;
	}

	Font(const tstring& newFontName, const tstring& newTag)
	{
		fontName = newFontName;
		tag = newTag;
		italic = false;
		size = 16;
		weight = FW_NORMAL;
		fontPtr = nullptr;
		fontD2DPtr = nullptr;
	}

	//!The name of the font
	tstring fontName;
	//!The tag of the font in the manager
	tstring tag;
	//!Write strings in italic
	bool italic;
	//!The size of the string
	int size;
	//!The weight of the string
	/*!Use the DWRITE_FONT_WEIGHT enum*/
	int weight;
	//!The address of the Direct-x font interface
	ID3DX10Font* fontPtr;
	//!The address of the Direct Write font interface
	/*!This is used to draw strings onto a HUD or GUI*/
	IDWriteTextFormat* fontD2DPtr;
};

//!The manager that stores and manages all the fonts
class FontManager final : public Manager
{
public:
	
	FontManager();
	~FontManager();

	//!Add a font to the manager
	void AddFont(Font &font);
	//!Remove a font from the manager
	void RemoveFont(const tstring& tag);
	//!Remove all fonts from the manager
	void RemoveAllFonts();
	//!Check if a font is present
	bool IsFontPresent(const tstring& tag);
	//!Retrieve the font with given tag
	Font GetFont(const tstring& tag);

	//!Draw a string on the screen
	void DrawString
	(	//!The content of the message
		const tstring& message, 
		//!The position on the screen where the font should be drawn
		const Vector2& pos, 
		//!The tag of the font that should be used
		const tstring& tag = _T("Default"), 
		//!The color of the message
		const D3DXCOLOR& color = D3DXCOLOR(0,0,0,255) 
	);

	//!Calculate the size if you would write a wont with a given tag
	Vector2 MesureString(const tstring& message, const tstring& tag = _T("Default"));

	//!Create a text layout interface to draw strings onto a HUD or GUI
	/*!This used by the UIString and UIValue objects*/
	IDWriteTextLayout* CreateTextLayout(const tstring& message, const tstring& fontTag);

private:
	//!The map that stores all fonts
	map<tstring,Font>	m_FontPtrMap;
	//!The Direct-Write factory used to create the 2D fonts
	IDWriteFactory*		m_DWriteFactory;

private:
	FontManager(FontManager& t);
	FontManager& operator=(FontManager& t);
};