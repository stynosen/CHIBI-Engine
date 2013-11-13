#pragma once
#include "Engine/ChibiEngine.h"
#include "UIElement.h"

class UIBitmap : public UIElement
{

public:
	UIBitmap(const tstring& tag, const tstring& imageTag, const Vector2& position);
	UIBitmap(const tstring& tag, const tstring& imageTag, double x = 0, double y = 0);
	UIBitmap(const tstring& tag, const tstring& imageTag, const Rect& sourceRect, const Vector2& position);
	UIBitmap(const tstring& tag, const tstring& imageTag, const Rect& sourceRect, double x = 0, double y = 0);

	void SetScale(double scale);
	void SetScale(const Vector2& newScale);
	void SetRotation(double newRotation);

	const Vector2& GetScale()const;
	const double& GetRotation()const;

	void Scale(double scale);
	void Scale(const Vector2& scale);
	void Rotate(double rotation);

	void SetSourceRect(const Rect& rect);
	const Rect& GetSourceRect()const;

	void SetOpacity(double opacity);
	double GetOpacity()const;

	//Center of texture is center of rotation
	void RotateAroundCenter();

	//Top left corner is center of rotation
	void RotateAroundCorner();

	void Resize();

	virtual ~UIBitmap(void);

	virtual bool Initialise();
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