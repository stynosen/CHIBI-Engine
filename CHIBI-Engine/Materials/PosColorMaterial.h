#pragma once
#include "BaseMaterial.h"
//-----------------------------------------------------
// PosNormTexMaterial Class									
//-----------------------------------------------------

//!A material that uses the flat color shader
class PosColorMaterial : public BaseMaterial
{
public:
	PosColorMaterial(const D3DXCOLOR& color);				// Constructor
	virtual ~PosColorMaterial();		// Destructor

	void SetColor(const D3DXCOLOR& color);
	//-------------------------------------------------
	// Inherited Methods							
	//-------------------------------------------------
	virtual void SetEffectVariables();
	virtual void LoadEffectVariables();
	virtual HRESULT CreateInputLayout();
private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	D3DXCOLOR							m_Color;
	ID3D10EffectVectorVariable			*m_ColorEffectVariable;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	PosColorMaterial(const PosColorMaterial& yRef);									
	PosColorMaterial& operator=(const PosColorMaterial& yRef);	
};