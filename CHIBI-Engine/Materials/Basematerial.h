#pragma once
#include "MainData.h"
#include "Engine/EngineMath.h"
#include "EngineVertex.h"

#include <map>

using namespace std;
class Camera;

//!The Base material class
/*!You can create custom materials by inheriting this class*/
class BaseMaterial
{
public:
	BaseMaterial();	
	virtual ~BaseMaterial();

	//!Link the effect to this material
	/*!Don't forget to add the effect to the EffectManager before using it in a material*/
	void SetEffect(const tstring& effectName);

	//!update the world, view and projection matrix of the material
	/*!This should be called in the Draw method of the object that uses this material*/
	void UpdateMatrix(const D3DXMATRIX& matWorld, Camera* cameraPtr);

	//!update the world matrix to draw on screen space instead of world space
	/*!This should be called in the Draw method of the object that uses this material*/
	void UpdateMatrixScreen(const D3DXMATRIX& matWorld, Camera* cameraPtr);

	//!Set the draw priority of the material
	/*!The highest priority will be drawn first (behind everything else)*/
	void SetDrawPriority(int priority);

	//!Get the pointer to the current technique
	ID3D10EffectTechnique* GetTechnique();

	//!Set the technique of the material
	/*!Make sure that the technique is actually present in the shader file*/
	bool SetTechnique(const tstring& techniqueName);

	//!Push all the effects to the shader
	void Commit();

protected:
	//!Set the effect variables out of the shader
	virtual void SetEffectVariables(){};

	//!Load the effect variables out of the shader
	virtual void LoadEffectVariables(){};

	//!Create the InputLayout of the shader
	/*!In a future update this will be automated*/
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


