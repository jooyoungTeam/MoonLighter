#include "stdafx.h"
#include "pot.h"

void pot::render()
{
	_img->aniRender(Vector2(_x, _y), _motion, 1.1f);
	D2DRenderer::GetInstance()->DrawRectangle(_rc, D2DRenderer::DefaultBrush::Yellow, 1.f);
}
