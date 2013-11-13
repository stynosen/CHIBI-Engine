#pragma once
#include "MainData.h"
#include "Materials/PosTexMaterial.h"
#include "Managers/ImageManager.h"
#include "GameObject.h"

#include <vector>

class Sprite : public GameObject
{
public:
	Sprite(const Texture& texture, double width, double height, const Rect& drawRect);
	virtual			~Sprite(void);
	
	void			DrawOnScreenPos(bool state);
	bool			Initialise();
	void			Paint();

	//Virtual for animation purposes
	virtual void	SetDrawRect(const Rect& drawRect);
	const Rect&		GetDrawRect()const;
	
	//Virtual for animation purposes
	virtual void	SetTexture(const Texture& rexture);
	const Texture&	GetTexture()const;

	PosTexMaterial* GetMaterial();

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