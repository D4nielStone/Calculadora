#include "botao.hpp"
#include "src/ui/painel/painel.hpp"

BubbleUI::Widgets::Botao::Botao(const std::string& label_shared, std::function<void()>funcao_click, bool completo)
    : completo(completo)
,   funcao_click_(funcao_click)
{
    cor = { 1, 1, 1 };
    frase = label_shared;
    resolucao = 12;
    configurar();
    letra_padding = {5, 5};
}

BubbleUI::Widgets::Botao::
Botao(const std::string &label_shared, std::function<void()> function, const std::string& imagePath, bool completo) : completo(completo)
,   funcao_click_(function)
{
    icon = std::make_unique<Imagem>(imagePath, Vector2{ 20, 20 });
    cor = { 1, 1, 1 };
    frase = label_shared;
    resolucao = 12;
    configurar();
    letra_padding = {5, 5};
}

BubbleUI::Widgets::Botao::Botao(const std::string& label_shared, bool* callback, bool completo, bool quebrar_linha, float d_h)
    : completo(completo), Callback(callback)
{
    DivisaoHorizontal = d_h;
    quebrarLinha = quebrar_linha;
    cor = { 1, 1, 1 };
    frase = label_shared;
    resolucao = 12;
    configurar();
    letra_padding = { 5, 5 };
}

void BubbleUI::Widgets::Botao::atualizar()
{
    if (icon)
        icon->atualizar();

    Texto::atualizar();
    moldura.defPos({ static_cast<int>(box_pos.x), static_cast<int>(box_pos.y) });
    // largura se completo ou não
    if (completo)
    {
        moldura.defTam({ static_cast<int>((painel->obterRetangulo().w / DivisaoHorizontal) - painel->widgetPadding.x * 2), static_cast<int>(box_size.y) });
        colisao.defRect({ box_pos.x, box_pos.y, static_cast<int>((painel->obterRetangulo().w/DivisaoHorizontal) - painel->widgetPadding.x * 2), (int)box_size.y});
    }
    else
    {
        moldura.defTam({ largura_texto + letra_padding.x * 2, static_cast<int>(box_size.y) });
        colisao.defRect({ box_pos.x, box_pos.y, (int)largura_texto + letra_padding.x * 2, (int)box_size.y });
    }
    moldura.atualizar();
    //reseta gatilho
    moldura.ocultar_linhas = true;
    if (inputs->mouseEnter == GLFW_RELEASE)gatilho = true;
    //calcula click
    if(Callback)
    *Callback = false;
    if (colisao.mouseEmCima() && inputs->mouseEnter == GLFW_PRESS && gatilho)
    {
        moldura.ocultar_linhas = false;
        if (funcao_click_)
        {
            funcao_click_();
            if(Callback)
            *Callback = true;
            gatilho = false;
        }
    }
    else if(colisao.mouseEmCima() && inputs->mouseEnter == GLFW_PRESS)
    {
        moldura.ocultar_linhas = false;
    }
    //calcula cor
    if(colisao.mouseEmCima())
        moldura.defCor({ 0.4f, 0.03f, 0.4f});
    else
        moldura.defCor({ 0.25f, 0.25f, 0.25f });
}

void BubbleUI::Widgets::Botao::renderizar() const
{
    moldura.renderizar();
    Texto::renderizar();

    if (icon)
        icon->renderizar();
}
