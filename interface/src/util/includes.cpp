#include "includes.hpp"
Vertex rect_vertex;
Vertex linha_vertex;

Vector4<float> paraNDC(const Vector4<int> retangulo, std::shared_ptr<Interface::Contexto> contexto)
{
    Vector4<float> coord_ndc(0.f, 0.f, 0.f, 0.f);
    coord_ndc.w = (retangulo.w * 2.f) / contexto->tamanho.width;
    coord_ndc.h = -(2.0f * retangulo.h) / contexto->tamanho.height;
    coord_ndc.x = (retangulo.x * 2.f) / contexto->tamanho.width - 1.f;
    coord_ndc.y = 1.0f - (2.0f * retangulo.y) / contexto->tamanho.height;

    return coord_ndc;
}