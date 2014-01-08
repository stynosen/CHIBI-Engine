#pragma once
#include "MainData.h"
#include "Materials/PosColorMaterial.h"
#include "Managers/ImageManager.h"
#include "GameObject.h"
#include <vector>

//!A rectangle with a certain color
class FilledRect : public GameObject
{
public:
	FilledRect(const D3DXCOLOR& color, double width, double height);
	virtual ~FilledRect(void);
	
	//!Change the color of the rectangle
	void SetColor(const D3DXCOLOR& color);

	//!Draw the rectangle on screen or world position
	/*!True : Screen position
	False : World position*/
	void DrawOnScreenPos(bool state);

	virtual bool Initialize();
	virtual void Paint();

	//!Get the material that used to draw the filled rectangle
	PosColorMaterial*	GetMaterial();

	//!Get the size of the rectangle
	const Vector2& GetSize()const;

private:
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	PosColorMaterial		*m_PosColorMaterialPtr;
	ID3D10Buffer			*m_VertexBufferPtr;
	ID3D10Buffer			*m_IndexBufferPtr;

	D3DXCOLOR				m_Color;

	vector<VertexPos>		m_VecVertices;
	vector<DWORD>			m_VecIndices;

	Vector2 m_Size;

	bool m_DrawOnScreenPos;

	void BuildShape();
	void AddTriangle (unsigned int a, unsigned int b, unsigned c);
	void BuildVertexBuffer();
	void BuildIndexBuffer();
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	FilledRect(FilledRect& t);
	FilledRect& operator=(FilledRect& t);
};