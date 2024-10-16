#include "colisao2d.hpp"

Interface::Colisao2d::Colisao2d(const Vector4<int>& quadrado, std::shared_ptr<Contexto> ctx) : quadrado(quadrado), contexto(ctx)
{
}

void Interface::Colisao2d::defRect(const Vector4<int> &quad)
{
	quadrado = quad;
}

bool Interface::Colisao2d::mouseEmCima() const
{
	if (   contexto->inputs->mousex > quadrado.x 
		&& contexto->inputs->mousex < (quadrado.x + quadrado.w)
		&& contexto->inputs->mousey > quadrado.y 
		&& contexto->inputs->mousey < (quadrado.y + quadrado.h)
	   )
		return true;
	else
		return false;
}