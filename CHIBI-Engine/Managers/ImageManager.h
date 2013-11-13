//---------------------------------------------------
//	CHIBI ENGINE v0.1
//  copyright Stijn Doyen
//---------------------------------------------------
//	ImageManager.h
//---------------------------------------------------
#pragma once
#include "MainData.h"
#include "Engine/EngineMath.h"
#include <map>
#include <vector>

using namespace std;

class Sprite;

struct Texture
{
	ID3D10ShaderResourceView*	ShaderResourceViewPtr;
	ID2D1Bitmap*				D2DBitmapPtr;
	IWICFormatConverter*		IWICFormatConverterPtr;
	D3DXCOLOR					TransparancyColor;
	tstring						FilePath;
	tstring						Tag;
	int							Width;
	int							Height;
	vector<vector<D3DXCOLOR>>	PixelData;

	Texture(const tstring& path, const tstring& tag, int height, int width)
	{
		ShaderResourceViewPtr	= nullptr;
		D2DBitmapPtr			= nullptr;
		IWICFormatConverterPtr	= nullptr;
		FilePath				= path;
		Width					= width;
		Height					= height;
		Tag						= tag;
		TransparancyColor		= D3DXCOLOR(0,0,0,0);
		PixelData.resize(0);
	}

	Texture()
	{
		ShaderResourceViewPtr	= nullptr;
		D2DBitmapPtr			= nullptr;
		IWICFormatConverterPtr	= nullptr;
		FilePath				= _T("");
		Tag						= _T("");
		Width					= 0;
		Height					= 0;
		TransparancyColor		= D3DXCOLOR(0,0,0,0);
		PixelData.resize(0);
	}

	void SetTransparencyColor(const D3DXCOLOR& color);
};

enum IMAGE_USAGE
{
	IMAGE_USAGE_NONE,
	IMAGE_USAGE_SPRITE,
	IMAGE_USAGE_HUD
};

class ImageManager final
{
public:
	ImageManager(void);
	~ImageManager(void);

	//Returns whether the texture was already present (there is already a texture with given tag)
	bool			AddTexture(const tstring& filePath,const tstring& tag, IMAGE_USAGE usage = IMAGE_USAGE_SPRITE);

	//Set the transparency color.
	//This is only for HUD textures. for sprite textures, use a shader for this
	void			SetTransparencyColor(const tstring& tag, const D3DXCOLOR& color);

	//Shortcut to create a sprite with given texture tag, width en height
	Sprite*			CreateSprite(const tstring& tag, int width, int height);
	Sprite*			CreateSprite(const tstring& tag, const Vector2& size);

	void			RemoveTexture(const tstring& tag);
	void			RemoveAllTextures();
	bool			IsTexturePresent(const tstring& tag)const;

	//Get the texture struct of the texture with given tag
	const Texture&	GetTexture(const tstring& tag);

	//This method will fil the PixelData vector of the texture
	void	GetPixeldata(const tstring& tag);

	void Resize();

private:
	HRESULT LoadBitmapFromFile(ID2D1RenderTarget *renderTargetPtr, IWICImagingFactory *IWICFactoryPtr, const tstring& filePath, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap **bitmapPtrOut, IWICFormatConverter** converterPtrOut);
	
	IWICImagingFactory* m_IWICImagingFactoryPtr;
	// Tag -> texture
	map<tstring,Texture> m_Textures;

private:
	ImageManager(ImageManager& t);
	ImageManager& operator=(ImageManager& t);
};

