#include "aba.hpp"
#include "src/ui/widgets/texto.hpp"
#include "painel.hpp"

Interface::Aba::Aba(Painel *painel)
{
    frase = painel->nome();
    this->painel = painel;
    contexto = painel->obterContexto();
    configurar();
    Texto::Texto(frase);
    corpo_rect = std::make_unique<Formas::Rect>(painel->obterContexto());
}

void Interface::Aba::atualizar()
{
    painel->posicaoWidget = { 0, -static_cast<int>(letra_padding.y*2) + 4 };

    renderizar_texto(frase);

    painel->posicaoWidget = { 0, corpo_rect->obtRect().h };

    corpo_rect->defPos({static_cast<int>(painel->obterRetangulo().x), static_cast<int>(painel->obterRetangulo().y)});
    corpo_rect->defTam({ painel->obterRetangulo().w, 22});
    box_pos = {corpo_rect->obtRect().x, corpo_rect->obtRect().y};
    box_size = { corpo_rect->obtRect().w, corpo_rect->obtRect().h };
    corpo_rect->atualizar();
}

void Interface::Aba::renderizar() const
{
    corpo_rect->renderizar();
    Texto::renderizar();
}

Interface::Formas::Rect* Interface::Aba::obterCorpo() const
{
    return corpo_rect.get();
}
