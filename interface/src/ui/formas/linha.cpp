#include "linha.hpp"

using namespace Interface::Formas;

Linha::Linha(const Vector4<int> &pos, std::shared_ptr<Contexto> ctx) : posicoes(pos), contexto(ctx)
{
    cor_base = { 0.4f, 0.f, 0.4f, 0.9f };
    if (!linha_vertex.carregado)
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            //Debug::emitir(Debug::Erro, "Failed to initialize GLAD");
            return;
        }
        glGenBuffers(1, &linha_vertex.VBO);
        glBindBuffer(GL_ARRAY_BUFFER, linha_vertex.VBO);
        glGenVertexArrays(1, &linha_vertex.VAO);
        glBindVertexArray(linha_vertex.VAO);
        linha_vertex.carregado = true;
    }
}
void Linha::defPos(const Vector4<int> &pos)
{
    posicoes = pos;
}
// Deve definir cor base
void Linha::defCor(const Color &cor)
{
    cor_base = cor;
}

void Linha::atualizar()
{
    if (tamanhoDoContextoAnterior != contexto->tamanho || tamanhoAnterior != posicoes)
    {
        coord_ndc = paraNDCLinha(posicoes, contexto);
        tamanhoAnterior = posicoes;
        tamanhoDoContextoAnterior = contexto->tamanho;
    }
}
// Deve renderizar
void Linha::renderizar() const
{
    shader.use();
    shader.setVec2("linha.pos1", coord_ndc.x, coord_ndc.y);
    shader.setVec2("linha.pos2", coord_ndc.w, coord_ndc.h);
    shader.setCor("cor", cor_base);

    glBindVertexArray(linha_vertex.VAO);
    glDrawArrays(GL_LINES, 0, 2);
}