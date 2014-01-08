#pragma once
#include "Engine/EngineMath.h"
#include "Camera.h"
#include "GameObject.h"

//!A camera that can not leave a certain rectangle
/*!If the screen is larger than the limit rectangle, the camera will be focused on the center of the rectangle.
TODO: The parts outside of the rectangle, will be turned black*/
class LimitCamera : public Camera
{
public:
	LimitCamera(const Rect& limit);
	virtual ~LimitCamera();

	virtual bool Initialize();
	virtual void Update();

	//!Change the limited rectangle
	void SetLimit(const Rect& limit);

	//!get the limited rectangle
	const Rect&	GetLimit	()const;

private:
	Rect		m_LimitRect;

private:
	LimitCamera(LimitCamera& t);
	LimitCamera& operator=(LimitCamera& t);
};