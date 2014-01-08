#pragma once
#include "MainData.h"
#include "Materials/PosTexMaterial.h"
#include "Managers/ImageManager.h"
#include "GameObject.h"
#include <vector>
#include <map>

#include "Sprite.h"

class Animation;
struct KeyFrame;
class AnimationSet;

//!A class that handles animates sprites based on an XML file
class AnimatedSprite
{
public:
	AnimatedSprite(const tstring& animationSetName, GameObject* parentPtr);
	virtual			~AnimatedSprite();
	
	//!Initializes the animated sprite
	bool			Initialize();
	//!Update the animated sprite to advance the animation
	virtual void	Update();
	//!Paint the animated sprite
	void			Paint(const D3DXMATRIX& matTransform = D3DXMATRIX(1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f));
	
	//!Play an animation in the map
	void			PlayAnimation(const tstring& animTag,bool reset = true);
	
	//!Set the current animation to another frame
	void			JumpToFrame(const int frame);
	
	//!Go to the next frame
	void			NextFrame();

	//!Start or resume the animation
	void			Play();

	//!Pause the animation at the current KeyFrame
	void			Pause();

	//!Get the paused state
	bool			IsPlaying();

	//!Reset the animation to the first KeyFrame
	void			Reset(bool stop = false);
	
	//!Alter animation speed (1 = normal)
	void			SetAnimationSpeed(double speed);
	//!Get animation speed (1 = normal)
	const double	GetAnimationSpeed()const;

	//!Get the current KeyFrame
	const KeyFrame GetCurrentKeyFrame()const;
	//!Get the current animation tag
	const tstring&		 GetCurrentAnimationTag()const;

private:
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	//!Set the draw rect
	void						SetDrawRect(const Rect& drawRect);
	//!Set the texture
	void						SetTexture(const tstring& textureTag);

	//!Is there an animation with given name?
	bool						HasAnimation(const tstring& animationTag);

	//!Build the shape
	void						BuildShape();

	//!Add a triangle
	void						AddTriangle (unsigned int a, unsigned int b, unsigned c);

	//!Build the vertex buffer
	void						BuildVertexBuffer();

	//!Build the index buffer
	void						BuildIndexBuffer();

	//!The address of the parent object
	GameObject					*m_ParentPtr;

	//!The material to render the animated sprite with
	PosTexMaterial				*m_PosTexMaterialPtr;

	//!the vertex buffer of the sprite
	ID3D10Buffer				*m_VertexBufferPtr;

	//!The index buffer of the sprite
	ID3D10Buffer				*m_IndexBufferPtr;

	//!A vector contained all the vertices of the sprite
	vector<VertexPosTex>		m_VecVertices;
	//!A vector contained all the indices of the sprite
	vector<DWORD>				m_VecIndices;

	//!The rectangle that defines the source of the current frame
	Rect						m_DrawRect;

	//!The tag of the current texture
	tstring						m_CurrentTextureTag;

	//!The alpha value, for transparency
	float						m_Alpha;

	//!The AnimationSet that is being rendered to this sprite
	AnimationSet*				m_AnimationSetPtr;

	//!The tag of the animation set
	tstring						m_AnimationSetName;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	AnimatedSprite(AnimatedSprite& t);
	AnimatedSprite& operator=(AnimatedSprite& t);
};