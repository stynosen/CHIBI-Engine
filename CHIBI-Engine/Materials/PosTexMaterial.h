#pragma once
#include "MainData.h"
#include "Engine/EngineMath.h"
#include "BaseMaterial.h"
//-----------------------------------------------------
// PosNormTexMaterial Class									
//-----------------------------------------------------

//!A material that uses the textured material
class PosTexMaterial : public BaseMaterial
{
public:
	PosTexMaterial(ID3D10ShaderResourceView* shaderResourceViewPtr);				// Constructor
	virtual ~PosTexMaterial();		// Destructor

	void SetTextureMatrix(const D3DXMATRIX& matTex);
	void SetAlpha(float alpha);
	void SetTexture(ID3D10ShaderResourceView* texture);
	void SetSize(const Vector2& size);
	
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

	ID3D10EffectMatrixVariable			*m_MatTexVariablePtr;
	D3DXMATRIX							m_MatTex;

	ID3D10EffectVectorVariable			*m_SizeAlphaPriorityVariablePtr;
	D3DXVECTOR4							m_SizeAlphaPriority;

	static ID3D10ShaderResourceView*	m_LastUsedTexturePtr;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	PosTexMaterial(const PosTexMaterial& yRef);									
	PosTexMaterial& operator=(const PosTexMaterial& yRef);	
};

 
