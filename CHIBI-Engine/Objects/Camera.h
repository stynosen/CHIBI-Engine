#pragma once
#include "Engine/EngineMath.h"
#include "GameObject.h"

//!The base camera class
/*!It is possible to create custom camera's by creating a class that inherits this one.
By doing this you could create a shaky cam, a free cam, ...*/
class Camera
{
public:
	Camera();
	virtual ~Camera();

	//!The initialization of the camera
	/*!The world, view and projection matrices are calculated in this method*/
	virtual bool Initialize();

	//!Update of the camera
	/*!The world, and view matrices are recalculated in this method
	Please note that the current camera is updated automatically by the SceneManager.
	It is however possible to update non-active cameras by calling this method manually*/
	virtual void Update();

	//!Get the world matrix
	/*!This method is called by most effects to make sure the objects are drawn at the correct screen position*/
	const D3DXMATRIX& GetMatWorld()const;
	//!Get the view matrix
	/*!This method is called by most effects to make sure the objects are drawn at the correct screen position*/
	const D3DXMATRIX& GetMatView()const;
	//!Get the projection matrix
	/*!This method is called by most effects to make sure the objects are drawn at the correct screen position*/
	const D3DXMATRIX& GetMatProj()const;
	//!Get the worldViewProjection matrix
	/*!This method is called by most effects to make sure the objects are drawn at the correct screen position*/
	const D3DXMATRIX& GetWorldViewproj()const;

	//!Set the position of the camera
	void SetPosition(const Vector2& pos);
	//!Move the camera over a given distance
	void Translate	(const Vector2& movement);
	//!Scale the camera's view
	/*!Note that the scale method will multiply the current scale with given scale.
	To change the scale to a given scale, use the SetScale method instead*/
	void Scale(const double& scale);
	//!Change the camera's view scale
	void SetScale	(const double& scale);
	//!Rotate the camera
	/*!Note that the Rotate method will add the given angle to the current angle.
	To change the angle to a given angle, use the SetRotation method instead*/
	void Rotate(const double& angle);
	//!Change the camera's rotation
	void SetRotation(const double& angle);

	//!Get the position of the camera
	const Vector2&	GetPosition()const;
	//!Get the scale of the camera
	const double&	GetScale()const;
	//!Get the rotation of the camera
	const double&	GetRotation	()const;

	//!Get the rectangle that represents the bounding box of the current view-space
	/*!This bounding box is used to make sure GameObjects that are not on the screen, are not drawn*/
	const Rect&		GetViewportRect()const;

private:
	D3DXMATRIX	m_MatWorld;
	D3DXMATRIX	m_MatView;
	D3DXMATRIX	m_MatProj;
	Vector2		m_Velocity;
	Vector2		m_Position;
	double		m_Scale;
	double		m_Rotation;
	Rect		m_ViewportRect;


private:
	Camera(Camera& t);
	Camera& operator=(Camera& t);
};