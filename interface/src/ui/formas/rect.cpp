#include "rect.hpp"

using namespace Interface::Formas;
// Dentro da classe Rect, adicione um buffer para instâncias
uint instanceVBO;

// Vamos criar uma estrutura para armazenar as transformações de cada instância
struct Instancia {
    Vector2 posicao;
    Vector2 tamanho;
    Color cor;
};

std::vector<Instancia> instancias; // Armazena todas as instâncias

Rect::Rect(std::shared_ptr<Contexto> ctx, const Vector4<int> &rect) : retangulo(rect), contexto(ctx)
{
    definirBuffers();
}

// Deve retornar o tamanho/posicao
Vector4<int> Rect::obtRect() const
{
    return retangulo;
}

Vector4<float> Rect::obtRectNDC() const
{
    return coord_ndc;
}

void Rect::defTam(const Vector2 &tam)
{
    retangulo.w = tam.x;
    retangulo.h = tam.y;
}

void Rect::defPos(const Vector2 &pos)
{
    retangulo.x = static_cast<float>(pos.x);
    retangulo.y = static_cast<float>(pos.y);
}

void Rect::adiTam(const Vector2 &tam)
{
    retangulo.w += tam.x;
    retangulo.h += tam.y;
}

void Rect::adiPos(const Vector2 &pos)
{
    retangulo.x += pos.x;
    retangulo.y += pos.y;
}
// Deve definir cor base
void Rect::defCor(const Color &cor)
{
    cor_base = cor;
}
// Deve atualizar
void Rect::atualizar()
{
    if (tamanhoDoContextoAnterior != contexto->tamanho || tamanhoAnterior != retangulo)
    {
        coord_ndc = paraNDC(retangulo, contexto);
        tamanhoAnterior = retangulo;
        tamanhoDoContextoAnterior = contexto->tamanho;
    }
}

// Deve renderizar
void Rect::renderizar() const
{
    shader.use();
    shader.setVec2("quadrado.tamanho", coord_ndc.w, coord_ndc.h);
    shader.setVec2("quadrado.posicao", coord_ndc.x, coord_ndc.y);
    shader.setCor("quadrado.cor", cor_base);
    glBindVertexArray(rect_vertex.VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(rect_vertex.indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

// deve definir buffers do quadrado
void Rect::definirBuffers()
{
    if (rect_vertex.carregado)    return;
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
       // Debug::emitir(Debug::Erro, "Glad");
        return;
    }

    // Define os vértices para um quadrado
    rect_vertex.vertices = {
        // Posições     // Coordenadas de textura
        0.f, 0.f,     0.0f, 0.0f,
        1.f, 0.f,     1.0f, 0.0f,
        1.f, 1.f,     1.0f, 1.0f,
        0.f, 1.f,     0.0f, 1.0f
    };

    rect_vertex.indices = {
        0, 2, 1, // Primeiro triângulo
        2, 0, 3  // Segundo triângulo
    };

    glGenVertexArrays(1, &rect_vertex.VAO);
    glGenBuffers(1, &rect_vertex.VBO);
    glGenBuffers(1, &rect_vertex.EBO);

    glBindVertexArray(rect_vertex.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, rect_vertex.VBO);
    glBufferData(GL_ARRAY_BUFFER, rect_vertex.vertices.size() * sizeof(float), rect_vertex.vertices.data(), GL_STATIC_DRAW); // Corrigido para tamanho em bytes

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rect_vertex.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, rect_vertex.indices.size() * sizeof(uint), rect_vertex.indices.data(), GL_STATIC_DRAW); // Corrigido para tamanho em bytes

    // Atributos de posição
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Atributos de coordenadas de textura
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    rect_vertex.carregado = true;
}