#pragma once
#include <string>
#include "unordered_map"
#include "bubbleui.hpp"
#include <freeimage.h>
#include <glad/glad.h>

class GLFWimage;
namespace Bubble {
    namespace Arquivadores {
        class BEUI_DLL_API ImageLoader
        {
        public:
            ImageLoader();
            ImageLoader(const std::string& filepath);
            ~ImageLoader();

            int getWidth() const;
            int getHeight() const;
            int getChannels() const;
            unsigned char* obterDados() const;
            GLFWimage converterParaGlfw();
            bool carregado;
        private:
            std::unordered_map<std::string, ImageLoader*>imagens_carregadas;
            void flipVertical();
            void carregarImagem(const std::string& filepath);
            const char* path;
            int width, height, channels;
            unsigned char* data;
        };
        BEUI_DLL_API unsigned int TextureFromFile(const std::string& directory, int* width = nullptr, int* height = nullptr);
        BEUI_DLL_API unsigned int TextureFromFile(unsigned char* data, unsigned int width, unsigned int height, int format);

        class BEUI_DLL_API TextureLoader
        {
        public:
            static TextureLoader& getInstance();
            GLuint carregarTextura(const std::string& caminho, int* width = nullptr, int* height = nullptr);
        private:
            std::unordered_map<std::string, GLuint> texturasCarregadas;

            // Construtor privado para Singleton
            TextureLoader() {}

            // Desabilitar cópia e atribuição
            TextureLoader(const TextureLoader&) = delete;
            void operator=(const TextureLoader&) = delete;
        };
    }
}
