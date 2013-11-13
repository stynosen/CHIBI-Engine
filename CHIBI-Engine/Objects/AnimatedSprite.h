#pragma once
#include "MainData.h"
#include "Materials/PosTexMaterial.h"
#include "Managers/ImageManager.h"
#include "GameObject.h"
#include <vector>
#include <map>

#include "Sprite.h"

class Animation;
struct AnimationFrame;
class AnimationSet;

class AnimatedSprite
{
public:
	AnimatedSprite(const tstring& animationSetName, GameObject* parentPtr);
	virtual			~AnimatedSprite();
	
	bool			Initialise();
	virtual void	Update();
	void			Paint(const D3DXMATRIX& matTransform = D3DXMATRIX(1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f));
	
	//Play an animation in the map
	void			PlayAnimation(const tstring& animTag,bool reset = true);
	
	//Set the current animation to another frame
	void			JumpToFrame(const int frame);
	
	//Go to the next frame
	void			NextFrame();

	//Start or resume the animation
	void			Play();

	//Pause the animation at the current keyframe
	void			Pause();

	//Get the paused state
	bool			IsPlaying();

	//Reset the animation to the first keyframe
	void			Reset(bool stop = false);
	
	//Alter animation speed (1 = normal)
	void			SetAnimationSpeed(double speed);
	const double	GetAnimationSpeed()const;

	//Get the current animation info
	const AnimationFrame GetCurrentAnimationFrame()const;
	const tstring&		 GetCurrentAnimationTag()const;

private:
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	void						SetDrawRect(const Rect& drawRect);
	void						SetTexture(const tstring& textureTag);

	bool						HasAnimation(const tstring& animationTag);

	void						BuildShape();
	void						AddTriangle (unsigned int a, unsigned int b, unsigned c);
	void						BuildVertexBuffer();
	void						BuildIndexBuffer();

	
	GameObject					*m_ParentPtr;

	PosTexMaterial				*m_PosTexMaterialPtr;
	ID3D10Buffer				*m_VertexBufferPtr;
	ID3D10Buffer				*m_IndexBufferPtr;

	vector<VertexPosTex>		m_VecVertices;
	vector<DWORD>				m_VecIndices;

	Rect						m_DrawRect;

	tstring						m_CurrentTextureTag;
	float						m_Alpha;

	AnimationSet*				m_AnimationSetPtr;
	tstring						m_AnimationSetName;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	AnimatedSprite(AnimatedSprite& t);
	AnimatedSprite& operator=(AnimatedSprite& t);
};