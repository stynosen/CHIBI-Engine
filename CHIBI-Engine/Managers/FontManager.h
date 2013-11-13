#pragma once
#include "Engine/EngineMath.h"
#include "MainData.h"
#include <map>
#include <dwrite.h>

using namespace std;

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

	tstring fontName;
	tstring tag;
	bool italic;
	int size;
	int weight;
	ID3DX10Font* fontPtr;
	IDWriteTextFormat* fontD2DPtr;
};

class FontManager final
{
public:
	
	FontManager();
	~FontManager();

	void AddFont(Font &font);
	void RemoveFont(const tstring& tag);
	void RemoveAllFonts();
	bool IsFontPresent(const tstring& tag);
	Font GetFont(const tstring& tag);

	void DrawString(const tstring& message, const Vector2& pos, const tstring& tag = _T("Default"), const D3DXCOLOR& color = D3DXCOLOR(0,0,0,255));
	Vector2 MesureString(const tstring& message, const tstring& tag = _T("Default"));

	IDWriteTextLayout* CreateTextLayout(const tstring& message, const tstring& fontTag);

private:
	map<tstring,Font>	m_FontPtrMap;
	IDWriteFactory*		m_DWriteFactory;

private:
	FontManager(FontManager& t);
	FontManager& operator=(FontManager& t);
};