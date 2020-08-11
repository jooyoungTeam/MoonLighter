#include "stdafx.h"
#include "pot.h"

void pot::render()
{
	_img->aniRender(Vector2(_x, _y), _motion, 1.1f);
	D2DRenderer::GetInstance()->FillRectangle(_bar.back, D2D1::ColorF::DimGray, _barAlpha);
	D2DRenderer::GetInstance()->FillRectangle(_bar.middle, D2D1::ColorF::LightSalmon, _barAlpha);
	D2DRenderer::GetInstance()->FillRectangle(_bar.front, D2D1::ColorF::Tomato, _barAlpha);

}
