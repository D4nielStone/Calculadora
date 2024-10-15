#include "moldura.hpp"

using namespace Interface::Formas;

Moldura::Moldura(std::shared_ptr<Contexto> contexto, const Vector4<int>& retangulo)
{
	this->contexto = contexto;
	this->retangulo = retangulo;
	Rect::Rect(contexto, retangulo);
	linha_d = std::make_unique<Linha>(Vector4<int>{0, 0, 0, 0}, contexto);
	linha_b = std::make_unique<Linha>(Vector4<int>{0, 0, 0, 0}, contexto);
	linha_e = std::make_unique<Linha>(Vector4<int>{0, 0, 0, 0}, contexto);
	linha_c = std::make_unique<Linha>(Vector4<int>{0, 0, 0, 0}, contexto);
	linha_d->defCor({ 0.35f, 0.35f, 0.35f });
	linha_b->defCor({ 0.35f, 0.35f, 0.35f });
	linha_e->defCor({ 0.55f, 0.55f, 0.55f });
	linha_c->defCor({ 0.55f, 0.55f, 0.55f });
}

Moldura& Moldura::operator=(const Moldura& other)
{
	// Evitar auto-atribuição
	if (this == &other)
		return *this;

	// Copiar os atributos da classe base (Rect)
	Rect::operator=(other);

	// Copiar os atributos da classe Moldura
	this->posicaoWidget = other.posicaoWidget;
	this->ocultar_linhas = other.ocultar_linhas;

	// Copiar os ponteiros únicos para Linhas (clonar os objetos)
	this->linha_d = other.linha_d ? std::make_unique<Linha>(*other.linha_d) : nullptr;
	this->linha_e = other.linha_e ? std::make_unique<Linha>(*other.linha_e) : nullptr;
	this->linha_c = other.linha_c ? std::make_unique<Linha>(*other.linha_c) : nullptr;
	this->linha_b = other.linha_b ? std::make_unique<Linha>(*other.linha_b) : nullptr;

	return *this;
}

void Moldura::atualizar()
{
	preAtualizacao();
	Rect::atualizar();
	if (ocultar_linhas)
		return;
	linha_d->defPos({
			retangulo.x + retangulo.w + 1,
			retangulo.y - 1,
			static_cast<int>(retangulo.x + retangulo.w + 1),
			static_cast<int>(retangulo.y + retangulo.h + 1)
		});
	linha_e->defPos({
			retangulo.x,
			retangulo.y - 1,
			static_cast<int>(retangulo.x),
			static_cast<int>(retangulo.y + retangulo.h + 1)
		});
	linha_c->defPos({
			retangulo.x,
			retangulo.y - 1,
			static_cast<int>(retangulo.x + retangulo.w),
			static_cast<int>(retangulo.y)
		});
	linha_b->defPos({
			retangulo.x,
			retangulo.y + retangulo.h + 1,
			static_cast<int>(retangulo.x + retangulo.w),
			static_cast<int>(retangulo.y + retangulo.h+1)
		});
	linha_b->atualizar();
	linha_c->atualizar();
	linha_d->atualizar();
	linha_e->atualizar();

	linha_d->defCor(cor_base - 0.1f);
	linha_b->defCor(cor_base - 0.1f);
	linha_e->defCor(cor_base - 0.1f);
	linha_c->defCor(cor_base - 0.1f);

	posAtualizacao();
}

void Moldura::renderizar() const
{
	Rect::renderizar();
	if (ocultar_linhas)return;
	linha_c->renderizar();
	linha_e->renderizar();
	linha_d->renderizar();
	linha_b->renderizar();
}

std::shared_ptr<Interface::Contexto> Moldura::obtCtx() const
{
	return contexto;
}