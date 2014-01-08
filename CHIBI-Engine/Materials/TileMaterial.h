#pragma once
#include "MainData.h"
#include "Engine/EngineMath.h"
#include "BaseMaterial.h"
//-----------------------------------------------------
// PosNormTexMaterial Class									
//-----------------------------------------------------

//!A material that uses the tile material, and supports instanced drawing
class TileMaterial : public BaseMaterial
{
public:
	TileMaterial();				// Constructor
	virtual ~TileMaterial();		// Destructor

	void SetTexture(ID3D10ShaderResourceView* texture);
	void SetAlpha(float alpha);
	
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

	ID3D10EffectShaderResourceVariable	*m_DiffuseMapVariabelePtr;
	ID3D10ShaderResourceView			*m_TextureResourceViewPtr;

	float								m_Alpha;
	ID3D10EffectScalarVariable			*m_AlphaVariablePtr;
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	TileMaterial(const TileMaterial& yRef);									
	TileMaterial& operator=(const TileMaterial& yRef);	
};

 
