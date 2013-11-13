#pragma once
#include "MainData.h"
#include "Materials/PosColorMaterial.h"
#include "Managers/ImageManager.h"
#include "GameObject.h"
#include <vector>

class FilledRect : public GameObject
{
public:
	FilledRect(const D3DXCOLOR& color, double width, double height);
	virtual ~FilledRect(void);
	
	void SetColor(const D3DXCOLOR& color);

	void DrawOnScreenPos(bool state);
	bool Initialise();
	void Paint();

	PosColorMaterial*	GetMaterial();

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