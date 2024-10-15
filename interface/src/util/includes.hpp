#pragma once
#include <vector>
#include <iostream>
#include <cstdio>
#include <iostream>
#include "src/arquivadores/shader.hpp"
#include <interface.hpp>
#include <any>
#include <src/ui/contexto/contexto.hpp>

// Definição da estrutura Vector4
template <typename T>
struct Vector4
{
    T x, y, w, h;
    Vector4(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}
    Vector4(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

    // Deve somar
    Vector4 operator+(const Vector4& other) const
    {
        return Vector4{ x + other.x, y + other.y, w + other.w, h + other.h };
    };
    Vector4 operator+(const float other) const
    {
        return Vector4{ x + other, y + other, w + other, h + other };
    };
    Vector4& operator+=(const Vector4& other)
    {
        x += other.x;
        y += other.y;
        w += other.w;
        h += other.h;
        return *this;
    };
    Vector4& operator+=(const float other)
    {
        x += other;
        y += other;
        w += other;
        h += other;
        return *this;
    };
    // Deve subtrair
    Vector4 operator-(const Vector4& other) const
    {
        return Vector4{ x - other.x, y - other.y, w - other.w, h - other.h };
    };
    Vector4 operator-(const float other) const
    {
        return Vector4{ x - other, y - other, w - other, h - other };
    };
    Vector4& operator-=(const Vector4& other)
    {
        x -= other.x;
        y -= other.y;
        w -= other.w;
        h -= other.h;
        return *this;
    };
    Vector4& operator-=(const float other)
    {
        x -= other;
        y -= other;
        w -= other;
        h -= other;
        return *this;
    };
    // Deve multiplicar
    Vector4 operator*(const Vector4& other) const
    {
        return Vector4{ x * other.x, y * other.y, w * other.w, h * other.h };
    };
    Vector4 operator*(float other) const
    {
        return Vector4{ x * other, y * other, w * other, h * other };
    };
    Vector4& operator*=(const Vector4& other)
    {
        x *= other.x;
        y *= other.y;
        w *= other.w;
        h *= other.h;
        return *this;
    };
    Vector4& operator*=(float other)
    {
        x *= other;
        y *= other;
        w *= other;
        h *= other;
        return *this;
    };
    // Deve dividir
    Vector4 operator/(const Vector4& other) const
    {
        return Vector4{ x / other.x, y / other.y, w / other.w, h / other.h };
    };
    Vector4 operator/(float other) const
    {
        return Vector4{ x / other, y / other, w / other, h / other };
    };
    Vector4& operator/=(const Vector4& other)
    {
        x /= other.x;
        y /= other.y;
        w /= other.w;
        h /= other.h;
        return *this;
    };
    Vector4& operator/=(float other)
    {
        x /= other;
        y /= other;
        w /= other;
        h /= other;
        return *this;
    };
    // Operador de igualdade (==)
    bool operator==(const Vector4& other) const
    {
        return x == other.x && y == other.y && w == other.w && h == other.h;
    }
    // Operador de diferença (!=)
    bool operator!=(const Vector4& other) const
    {
        return !(*this == other);
    }

    Vector4() : x(0), y(0), w(0), h(0) {};
};

struct Vector2
{
    int x = 0, y = 0;
    // Operador de soma (+)
    Vector2 operator+(const Vector2& other) const
    {
        return { x + other.x && y + other.y };
    }
    // Operador de subtacao (-)
    Vector2 operator-(const Vector2& other) const
    {
        return { x - other.x && y - other.y };
    }
    // Operador de igualdade (==)
    bool operator==(const Vector2& other) const
    {
        return x == other.x && y == other.y;
    }

    // Operador de diferença (!=)
    bool operator!=(const Vector2& other) const
    {
        return !(*this == other);
    }
};
struct Vector3
{
    int x = 0, y = 0, z = 0;
    // Operador de soma (+)
    Vector3 operator+(const Vector3& other) const
    {
        return { x + other.x && y + other.y && z + other.z };
    }
    // Operador de igualdade (==)
    bool operator==(const Vector3& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    // Operador de diferença (!=)
    bool operator!=(const Vector3& other) const
    {
        return !(*this == other);
    }
};
struct Vector2f
{
    float x = 0, y = 0;
    // Operador de igualdade (==)
    bool operator==(const Vector2f& other) const
    {
        return x == other.x && y == other.y;
    }

    // Operador de diferença (!=)
    bool operator!=(const Vector2f& other) const
    {
        return !(*this == other);
    }
    // Operador de soma (+)
    Vector2f operator+(const Vector2f& other) const
    {
        return {x + other.x, y+other.y};
    }
};

struct Color 
{
    float r = 0.7f, g = 0.7f, b = 0.7f, a = 1.f;

    Color operator-(const float& other) const
    {
        return { r - other, g - other, b - other , 1.f};
    }
};

struct Vertex {
    std::vector<float> vertices;
    std::vector<uint> indices;
    std::vector<float> uvs;
    std::vector<float> normals;
    std::string nome = "malha sem nome";
    uint VAO = 0, EBO = 0, VBO = 0;
    bool carregado = false;
};

struct LetraRect
{
    Vector4<float> rect;
    uint ID;
};

Vector4<float> paraNDC(const Vector4<int> retangulo, std::shared_ptr<Interface::Contexto> contexto);

Vector4<float> paraNDCLinha(const Vector4<int> retangulo, std::shared_ptr<Interface::Contexto> contexto);

typedef std::pair<bool*, const char*>                   CheckBoxID     ;
typedef std::pair<std::string*, const char*>            CaixaDeTextoID ;
typedef std::pair<Color*, const char*>                  SeletorDeCorID ;
typedef std::pair<std::vector<std::any>, const char*>   ArvoreID       ;

extern UI_DLL_API Vertex rect_vertex;
extern UI_DLL_API Vertex linha_vertex;