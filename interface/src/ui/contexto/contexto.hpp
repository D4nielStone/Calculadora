#pragma once
#include "src/arquivadores/shader.hpp"
#include "src/inputs/inputs.hpp"
#include "interface.hpp"
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <memory>

struct Size
{
    int width = 1, height = 1;
    // Operador de igualdade (==)
    bool operator==(const Size& other) const
    {
        return width == other.width && height == other.height;
    }
    // Operador de diferen�a (!=)
    bool operator!=(const Size& other) const
    {
        return !(*this == other);
    }
};

namespace Interface
{
    // Cont�m informa��es gerais para os paineis e widgets
    struct UI_DLL_API Contexto
    {
        GLFWwindow* glfwWindow{ nullptr }; // Janela glfw do contexto em quest�o
        GLFWcursor* cursor_horizontal{ nullptr };   // Cursor glfw
        GLFWcursor* cursor_texto{ nullptr };        // Cursor glfw
        GLFWcursor* cursor_vertical{ nullptr };     // Cursor glfw
        GLFWcursor* cursor_normal{ nullptr };       // Cursor glfw
        GLFWcursor* cursor{ nullptr }; // Cursor � ser usado
        std::string NomeDoProjeto, VercaoDaEngine{"0.1 Aplha.1"}, VercaoOpengl, NomeGpu, dirDoProjeto;
        std::shared_ptr<Bubble::Inputs::Inputs> inputs{ nullptr }; // Inputs da janela glfw
        Size tamanho; // Tamanho da janela glfw

        Contexto();

        // Destructor to manage resources
        ~Contexto();
    };
}
