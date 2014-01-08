#pragma once
#include "Engine/ChibiEngine.h"
#include "UIElement.h"

//!A UIelement to draw a texture on a UI
/*!Make sure that the texture you want to use, is added to the ImageManager using the IMAGE_USAGE_HUD flag*/
class UIBitmap : public UIElement
{

public:
	//!Create a bitmap that can be drawn on a UI
	UIBitmap(
		//!The tag of this element, in the UI
		const tstring& tag,
		//!The tag of the texture to be drawn
		const tstring& imageTag, 
		//!The position on the screen
		const Vector2& position
	);

	//!Create a bitmap that can be drawn on a UI
	UIBitmap(
		//!The tag of this element, in the UI
		const tstring& tag,
		//!The tag of the texture to be drawn
		const tstring& imageTag,
		//!The x position on the screen
		double x = 0,
		//!The y position on the screen
		double y = 0
	);

	//!Create a bitmap that can be drawn on a UI
	UIBitmap(
		//!The tag of this element, in the UI
		const tstring& tag,
		//!The tag of the texture to be drawn
		const tstring& imageTag, 
		//!The rectangle that should be extracted from the texture
		const Rect& sourceRect, 
		//!The position on the screen
		const Vector2& position
	);

	//!Create a bitmap that can be drawn on a UI
	UIBitmap(
		//!The tag of this element, in the UI
		const tstring& tag,
		//!The tag of the texture to be drawn
		const tstring& imageTag,
		//!The rectangle that should be extracted from the texture
		const Rect& sourceRect,
		//!The x position on the screen
		double x = 0,
		//!The y position on the screen
		double y = 0
	);

	//!Set the scale of the bitmap (uniform scale)
	void SetScale(double scale);
	//!Set the scale of the bitmap (per axis scale)
	void SetScale(const Vector2& newScale);
	//!Set the rotation of the bitmap
	void SetRotation(double newRotation);

	//!Get the current scale of the bitmap
	const Vector2& GetScale()const;
	//!Get the current rotation of the bitmap
	const double& GetRotation()const;

	//!Scale the bitmap
	/*!Note that the scale method will multiply the current scale with given scale.
	To change the scale to a given scale, use the SetScale method instead*/
	void Scale(double scale);

	//!Scale the bitmap
	/*!Note that the scale method will multiply the current scale with given scale.
	To change the scale to a given scale, use the SetScale method instead*/
	void Scale(const Vector2& scale);

	//!Rotate the bitmap
	/*!Note that the Rotate method will add the given angle to the current angle.
	To change the angle to a given angle, use the SetRotation method instead*/
	void Rotate(double rotation);

	//!Set the part of the texture that has to be drawn
	void SetSourceRect(const Rect& rect);

	//!Get the part of the texture that has to be drawn
	const Rect& GetSourceRect()const;

	//!Set the opacity of the bitmap
	void SetOpacity(double opacity);

	//!Get the opacity of the bitmap
	double GetOpacity()const;

	//!Center of texture is center of rotation
	void RotateAroundCenter();

	//!Top left corner is center of rotation
	void RotateAroundCorner();


	virtual void Resize();

	virtual ~UIBitmap(void);

	virtual bool Initialize();
	virtual void Update();
	virtual void Paint();
	
private:

	tstring				m_TextureTag;
	bool				m_RotateAroundCenter;

	double				m_Angle;
	Vector2				m_Scale;

	D2D1_MATRIX_3X2_F	m_MatRotate;
	D2D1_MATRIX_3X2_F	m_MatScale;
	D2D1_MATRIX_3X2_F	m_MatTranslate;
	D2D1_MATRIX_3X2_F	m_MatCenter;
	D2D1_MATRIX_3X2_F	m_MatCenterNeg;

	D2D1_MATRIX_3X2_F	m_MatTransform;

	double				m_Opacity;

	Rect				m_SourceRect;

	UIBitmap(UIBitmap& t);
	UIBitmap& operator=(UIBitmap& t);
};