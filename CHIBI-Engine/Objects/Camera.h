#pragma once
#include "Engine/EngineMath.h"
#include "GameObject.h"
class Camera
{
public:
	Camera();
	virtual ~Camera();

	virtual bool Initialise();
	virtual void Update();

	const D3DXMATRIX& GetMatWorld()const;
	const D3DXMATRIX& GetMatView()const;
	const D3DXMATRIX& GetMatProj()const;
	const D3DXMATRIX& GetWorldViewproj()const;

	void SetPosition(const Vector2& pos);
	void Translate	(const Vector2& pos);
	void Scale		(const double& scale);
	void SetScale	(const double& scale);
	void Rotate		(const double& angle);
	void SetRotation(const double& angle);

	const Vector2&	GetPosition	()const;
	const double&	GetScale	()const;
	const double&	GetRotation	()const;

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