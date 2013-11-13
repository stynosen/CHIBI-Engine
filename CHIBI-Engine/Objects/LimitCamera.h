#pragma once
#include "Engine/EngineMath.h"
#include "Camera.h"
#include "GameObject.h"
class LimitCamera : public Camera
{
public:
	LimitCamera(const Rect& limit);
	virtual ~LimitCamera();

	bool Initialise();
	void Update();

	void SetLimit(const Rect& limit);

	const Rect&	GetLimit	()const;

private:
	Rect		m_LimitRect;

private:
	LimitCamera(LimitCamera& t);
	LimitCamera& operator=(LimitCamera& t);
};