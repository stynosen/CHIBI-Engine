//---------------------------------------------------
//	CHIBI ENGINE v0.1
//  copyright Stijn Doyen
//---------------------------------------------------
//	ImageManager.h
//---------------------------------------------------
#pragma once
#include "Manager.h"

#include "MainData.h"
#include "Engine/EngineMath.h"
#include <map>
#include <vector>

using namespace std;

class Sprite;

//!The struct that contains all the data of a texture
struct Texture
{
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

	//!Set the transparency color.
	/*!This is only for HUD textures. for sprite textures, use a shader for this*/
	void SetTransparencyColor(const D3DXCOLOR& color);

	//!The Direct-X shader resource view interface
	ID3D10ShaderResourceView*	ShaderResourceViewPtr;
	//!The Direct-2D bitmap interface
	ID2D1Bitmap*				D2DBitmapPtr;
	//!The IWIC bitmap converter
	/*!This is stored to change pixel data, for instance when setting the transparency color*/
	IWICFormatConverter*		IWICFormatConverterPtr;
	//!The transparency color of the texture
	D3DXCOLOR					TransparancyColor;
	//!The path to the image file
	tstring						FilePath;
	//!The tag of the texture, so it can be found in the manager
	tstring						Tag;
	//!The texture width
	int							Width;
	//!The texture height
	int							Height;
	//!A 2D array of all the pixel colors
	/*!Only filled after the GetPixeldata method of the ImageManager is called*/
	vector<vector<D3DXCOLOR>>	PixelData;
};

//!Defines how and where the texture will be used
enum IMAGE_USAGE
{
	IMAGE_USAGE_NONE, //!It won't be used at all
	IMAGE_USAGE_SPRITE, //!It will be used as a sprite in game
	IMAGE_USAGE_HUD //!It will be used as a resource for the HUD
};

//!The manager that stores and manages all the textures
class ImageManager final : public Manager
{
public:
	ImageManager(void);
	~ImageManager(void);

	//!Add a texture to the manager
	/*!Returns whether the texture was already present (there is already a texture with given tag)*/
	bool			AddTexture(const tstring& filePath,const tstring& tag, IMAGE_USAGE usage = IMAGE_USAGE_SPRITE);

	//!Set the transparency color.
	/*!This is only for HUD textures. for sprite textures, use a shader for this*/
	void			SetTransparencyColor(const tstring& tag, const D3DXCOLOR& color);

	//!Shortcut to create a sprite with given texture tag, width en height
	Sprite*			CreateSprite(const tstring& tag, int width, int height);
	//!Shortcut to create a sprite with given texture tag and size
	Sprite*			CreateSprite(const tstring& tag, const Vector2& size);

	//!Remove the texture that has given tag
	void			RemoveTexture(const tstring& tag);
	//!Remove all textures
	void			RemoveAllTextures();
	//!Check if there is a texture with a certain tag
	bool			IsTexturePresent(const tstring& tag)const;

	//!Get the texture struct of the texture with given tag
	const Texture&	GetTexture(const tstring& tag);

	//!This method will fill the PixelData vector of the texture
	void	GetPixeldata(const tstring& tag);

	//!This method is called whenever the screen is resized
	void Resize();

private:
	//!Loads the bitmap and creates the Direct-X data
	HRESULT LoadBitmapFromFile(ID2D1RenderTarget *renderTargetPtr, IWICImagingFactory *IWICFactoryPtr, const tstring& filePath, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap **bitmapPtrOut, IWICFormatConverter** converterPtrOut);
	
	//!The IWIC factory to create 2D textures
	IWICImagingFactory* m_IWICImagingFactoryPtr;

	//!A container that stores all the textures
	/*! Tag -> texture*/
	map<tstring,Texture> m_Textures;

private:
	ImageManager(ImageManager& t);
	ImageManager& operator=(ImageManager& t);
};

