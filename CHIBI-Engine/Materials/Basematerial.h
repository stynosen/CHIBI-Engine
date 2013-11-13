#pragma once
#include "MainData.h"
#include "Engine/EngineMath.h"
#include "EngineVertex.h"

#include <map>

using namespace std;
class Camera;
//-----------------------------------------------------
// PosNormTexMaterial Class									
//-----------------------------------------------------

class BaseMaterial
{
public:
	BaseMaterial();				// Constructor
	virtual ~BaseMaterial();		// Destructor

	void SetEffect(const tstring& effectName);
	void UpdateMatrix(const D3DXMATRIX& matWorld, Camera* cameraPtr);
	void UpdateMatrixScreen(const D3DXMATRIX& matWorld, Camera* cameraPtr);
	void SetDrawPriority(int priority);

	ID3D10EffectTechnique* GetTechnique();
	bool SetTechnique(const tstring& techniqueName);
	//-------------------------------------------------
	// Inherited Methods							
	//-------------------------------------------------
	void Commit();

protected:
	virtual void SetEffectVariables(){};
	virtual void LoadEffectVariables(){};
	virtual HRESULT CreateInputLayout()=0;

protected:
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	ID3D10Effect						*m_EffectPtr;
	ID3D10EffectTechnique				*m_CurrentTechniquePtr;
	map<tstring, ID3D10EffectTechnique*> m_Techniques;
	ID3D10InputLayout					*m_InputLayoutPtr;

	D3DXMATRIX							m_MatWorld;
	ID3D10EffectMatrixVariable			*m_WorldVariablePtr;

	D3DXMATRIX							m_MatView;
	ID3D10EffectMatrixVariable			*m_ViewVariablePtr;

	D3DXMATRIX							m_MatViewInv;
	ID3D10EffectMatrixVariable			*m_ViewInvVariablePtr;

	D3DXMATRIX							m_MatViewProj;
	ID3D10EffectMatrixVariable			*m_ViewProjVariablePtr;

	ID3D10EffectMatrixVariable			*m_WorldViewProjectionVariable;
	D3DXMATRIX							m_MatWorldViewProjection;

	int									m_DrawPriority;
	ID3D10EffectScalarVariable			*m_DrawPriorityEffectVariablePtr;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	BaseMaterial(const BaseMaterial& yRef);
	BaseMaterial& operator=(const BaseMaterial& yRef);
};


