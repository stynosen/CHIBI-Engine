#pragma once
#include "MainData.h"
#include "Materials/PosTexMaterial.h"
#include "Managers/ImageManager.h"
#include "GameObject.h"

#include <vector>

//!A GameObject that will be drawn as a visible texture
/*!It is also possible to draw a part of a sprite using the DrawRect.
Sprites can be created manually, or by using the CreateSprite method of the ImageManager*/
class Sprite : public GameObject
{
public:
	Sprite(//!The tag of the texture that should be drawn
		const Texture& texture, 
		//!The width of the sprite (not the texture)
		double width, 
		//!The height of the spire (not the texture)
		double height, 
		//!The part of the texture that should be drawn
		const Rect& drawRect 
		);
	virtual			~Sprite(void);
	

	//!Draw the rectangle on screen or world position
	/*!True : Screen position
	False : World position*/
	void					DrawOnScreenPos(bool state);
	virtual bool			Initialize();
	virtual void			Paint();

	//!Set the part of the texture that has to be drawn
	virtual void	SetDrawRect(const Rect& drawRect);
	//!Get the part of the texture that has to be drawn
	const Rect&		GetDrawRect()const;

	//!Set texture that has to be drawn
	/*!Textures can be retrieved by calling the GetTexture method of the ImageManager*/
	virtual void	SetTexture(const Texture& rexture);
	//!Get the texture that has to be drawn
	const Texture&	GetTexture()const;

	//!Get the material that is used to draw the sprite on the screen
	PosTexMaterial* GetMaterial();

	//!Change the alpha of the sprite to make it translucent
	/*!If the alpha is 1, it will be opaque
	This is cheaper for the GPU to render, so only use alpha where needed*/
	void			SetAlpha(float alpha);

private:
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	PosTexMaterial				*m_PosTexMaterialPtr;
	ID3D10Buffer				*m_VertexBufferPtr;
	ID3D10Buffer				*m_IndexBufferPtr;

	vector<VertexPosTex>		m_VecVertices;
	vector<DWORD>				m_VecIndices;

	double						m_Width;
	double						m_Height;

	Rect						m_DrawRect;

	Texture						m_Texture;
	float						m_Alpha;

	bool						m_DrawOnScreenPos;

	void						BuildShape();
	void						AddTriangle (unsigned int a, unsigned int b, unsigned c);
	void						BuildVertexBuffer();
	void						BuildIndexBuffer();
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Sprite(Sprite& t);
	Sprite& operator=(Sprite& t);
};