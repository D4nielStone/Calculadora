#include "separador.hpp"
#include "painel.hpp"

using namespace Interface;

Separador::Separador(const Lado side, Painel* p) :contexto(p->obterContexto()), inputs(p->obterContexto()->inputs), lado(side), painel(p), colisao(Colisao2d({}, p->obterContexto()))
{
}

void Separador::atualizar()
{
	if (!painel->selecionado)
		return;
	atualizarColisao();
	atualizarArrasto();
	atualizarCursor();
}

bool Separador::cursor() const
{
	return colisao.mouseEmCima();
}

void Separador::atualizarColisao()
{
	switch (lado)
	{
	case DIREITA:
		colisao.defRect({
			painel->obterRetangulo().x + painel->obterRetangulo().w -2,
			painel->obterRetangulo().y,
			10,
			painel->obterRetangulo().h
			});
		break;
	case ESQUERDA:
		colisao.defRect({
			painel->obterRetangulo().x - 10,
			painel->obterRetangulo().y,
			12,
			painel->obterRetangulo().h
			});
		break;
	case CIMA:
		colisao.defRect({
			painel->obterRetangulo().x,
			painel->obterRetangulo().y - 10,
			painel->obterRetangulo().w,
			12
			});
		break;
	case BAIXO:
		colisao.defRect({
			painel->obterRetangulo().x,
			painel->obterRetangulo().y + painel->obterRetangulo().h - 2,
			painel->obterRetangulo().w,
			12
			});
		break;
	default:
		break;
	}
}

void Separador::atualizarCursor()
{
	if (colisao.mouseEmCima() && painel->selecionado)
	{
		switch (lado)
		{
		case DIREITA:
			contexto->cursor = contexto->cursor_horizontal;
			break;
		case ESQUERDA:
			contexto->cursor = contexto->cursor_horizontal;
			break;
		case CIMA:
			contexto->cursor = contexto->cursor_vertical;
			break;
		case BAIXO:
			contexto->cursor = contexto->cursor_vertical;
			break;
		default:
			break;
		}
		if (inputs->mouseEnter == GLFW_RELEASE)
			mouse_1click = true;
		if (mouse_1click && inputs->mouseEnter == GLFW_PRESS)
		{
			arrastando = true;
			mouse_1click = false;
		}
	}
	else
		mouse_1click = false;

}

void Separador::atualizarArrasto()
{
	if (arrastando && inputs->mouseEnter == GLFW_PRESS)
	{
		painel->arrastando = true;
		painel->redimensionamentoAtual = lado;
		switch (lado)
		{
		case DIREITA:
			contexto->cursor = contexto->cursor_horizontal;
				painel->adicionarTamanho({ static_cast<int>(inputs->mousex) - mouse_pos_ini.x, 0 });
			break;
		case ESQUERDA:
			contexto->cursor = contexto->cursor_horizontal;
			if(!painel->preenchido)
				painel->adicionarPosicao({ static_cast<int>(inputs->mousex - mouse_pos_ini.x), 0 });
				painel->adicionarTamanho({ -static_cast<int>(inputs->mousex - mouse_pos_ini.x), 0 });
			break;
		case CIMA:
				contexto->cursor = contexto->cursor_vertical;
			if (!painel->preenchido)
				painel->adicionarPosicao({ 0,static_cast<int>(inputs->mousey - mouse_pos_ini.y) });
				painel->adicionarTamanho({ 0,-static_cast<int>(inputs->mousey - mouse_pos_ini.y) });
			break;
		case BAIXO:
			contexto->cursor = contexto->cursor_vertical;
				painel->adicionarTamanho({ 0, static_cast<int>(inputs->mousey - mouse_pos_ini.y) });
			break;
		default:
			break;
		}
	}
	else
		arrastando = false;
	mouse_pos_ini = { static_cast<int>(inputs->mousex), static_cast<int>(inputs->mousey) };
}