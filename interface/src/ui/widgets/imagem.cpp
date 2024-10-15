#include "imagem.hpp"
#include "src/ui/painel/painel.hpp"
#include "src/arquivadores/imageloader.hpp"

using namespace Interface::Widgets;
Imagem::Imagem(uint id, const Vector2<int> &size, const bool &auto_resize) : ID(id), rect({ 0, 0, size.x, size.y }), preencher(auto_resize)
{
}

Imagem::Imagem(const std::string& path, int size_percentage, Vector2<int> *posicao) : posicao_ptr(posicao)
{
    auto &gerenciador = Bubble::Arquivadores::TextureLoader::getInstance();
    ID = gerenciador.carregarTextura(path, &rect.w, &rect.h);
    rect.w *= static_cast<int>(static_cast<float>(size_percentage) / 100);
    rect.h *= static_cast<int>(static_cast<float>(size_percentage) / 100);
}

Imagem::Imagem(const std::string& path, const Vector2<int>& size)
{
    auto& gerenciador = Bubble::Arquivadores::TextureLoader::getInstance();
    ID = gerenciador.carregarTextura(path, &rect.w, &rect.h);
    rect.w = size.x;
    rect.h = size.y;
}

void Imagem::atualizar()
{
    if (preencher)
    {
        rect.w = painel->obterRetangulo().w;
        rect.h = painel->obterRetangulo().h - painel->posicaoWidget.y;
    }
    rect = { painel->obterRetangulo().x + painel->posicaoWidget.x, painel->obterRetangulo().y + painel->posicaoWidget.y, rect.w, rect.h };
    
    rect.y += padding ? painel->widgetPadding.y : 0;
    switch (alinhamentoHorizontal)
    {
    case Alinhamento::Esquerda:
        rect.x += padding ? painel->widgetPadding.x : 0;
        break;
    case Alinhamento::Direita:
        rect.x += painel->obterRetangulo().w - rect.w;
        rect.x -= padding ? painel->widgetPadding.x : 0;
        break;
    case Alinhamento::Centro:
        rect.x += painel->obterRetangulo().w / 2 - rect.w / 2;
    }
    if (posicao_ptr)
    {
        rect.x = posicao_ptr->x;
        rect.y = posicao_ptr->y;
    }
    if (quebrarLinha)
    {
        painel->posicaoWidget.x = 0;
        painel->posicaoWidget.y += rect.h + painel->widgetPadding.y*2;
    }
    else
    {
        painel->posicaoWidget.x += rect.w + painel->widgetPadding.x;
    }
}

// Atualiza o retângulo do corpo_do_widget para a imagem
void Imagem::renderizar() const
{
    if (!deveRenderizar)
        return;
    Vector4<float> rectf = paraNDC(rect, contexto);
    shader.use();
    shader.setVec2("quadrado.posicao", rectf.x, rectf.y);
    shader.setVec2("quadrado.tamanho", rectf.w, rectf.h);
    shader.setInt("textura", 0);
    shader.setBool("flip", flip);

    glBindTexture(GL_TEXTURE_2D, ID);
    glBindVertexArray(rect_vertex.VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(rect_vertex.indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Imagem::defID(uint newID)
{
    return ID = newID;
}

Vector4<int> Imagem::obtRect() const
{
    return rect;
}
