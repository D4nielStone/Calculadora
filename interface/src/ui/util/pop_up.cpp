#include "pop_up.hpp"
#include "src/ui/items/item_menu.hpp"

Interface::Util::PopUp::PopUp(std::shared_ptr<Contexto> contexto)
{
	Moldura::Moldura(contexto);
	inputs = contexto->inputs; 
	this->contexto = contexto;
	this->retangulo = retangulo;
	Rect::Rect(contexto, retangulo);
	colisao = Colisao2d({},contexto);
	linha_d = std::make_unique<Formas::Linha>(Vector4<int>{ 0, 0, 0, 0 }, contexto);
	linha_b = std::make_unique<Formas::Linha>(Vector4<int>{ 0, 0, 0, 0 }, contexto);
	linha_e = std::make_unique<Formas::Linha>(Vector4<int>{ 0, 0, 0, 0 }, contexto);
	linha_c = std::make_unique<Formas::Linha>(Vector4<int>{ 0, 0, 0, 0 }, contexto);
	linha_d->defCor({ 0.35f, 0.35f, 0.35f });
	linha_b->defCor({ 0.35f, 0.35f, 0.35f });
	linha_e->defCor({ 0.55f, 0.55f, 0.55f });
	linha_c->defCor({ 0.55f, 0.55f, 0.55f });
}

void Interface::Util::PopUp::posAtualizacao()
{
	altura = 0;
	posicaoWidget = { 0, 0 };
	for (auto& item : lista_items)
	{
		item->definirEscondido(!vmostrar);
		item->atualizar();
		if (item->largura > largura)
			largura = item->largura;
		altura += item->altura;
	}

	colisao.defRect(retangulo);
	mouseEmCima = colisao.mouseEmCima();
	if (vmostrar && inputs->mouseEnter == GLFW_RELEASE)
		podeEsconder = true;
	if (vmostrar && inputs->mouseEnter == GLFW_PRESS && !mouseEmCima && podeEsconder)
	{
		esconder();
		podeEsconder = false;
	}
}

void Interface::Util::PopUp::mostrar()
{
	if (!vmostrar)
	{
		this->retangulo = { static_cast<int>(inputs->mousex), static_cast<int>(inputs->mousey), largura, altura };
		vmostrar = true;
	}
}

void Interface::Util::PopUp::esconder()
{
	vmostrar = false;
}

void Interface::Util::PopUp::renderizar() const
{
	if (escondido()) return; 
	Moldura::renderizar();
	for (auto& item : lista_items)
	{
		item->renderizar();
	}
}

void Interface::Util::PopUp::adiItem(std::shared_ptr<Interface::Items::ItemMenu> item)
{
	item->defMoldura(this);
	lista_items.emplace_back(item);
}

bool Interface::Util::PopUp::temItems() const
{
	return (lista_items.size() != 0);
}

bool Interface::Util::PopUp::escondido() const
{
	return !vmostrar;
}
