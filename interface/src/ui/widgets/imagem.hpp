#pragma once
#include "widget.hpp"

namespace Interface
{
	namespace Widgets
	{
		class UI_DLL_API Imagem : public Widget
		{
		public:
			Imagem(uint id, const Vector2<int>& size = { 100, 100 }, const bool& auto_resize = true);
			Imagem(const std::string& path, int size_percentage, Vector2<int>* posicao = nullptr);
			Imagem(const std::string& path, const Vector2<int>& size = {16, 16});
			void atualizar() override;
			void renderizar() const override;
			bool defID(uint newID);
			Vector4<int> obtRect() const;
			bool deveRenderizar{ true }, flip{ false }, padding{ false };
		private:
			uint ID;
			Vector2<int>* posicao_ptr{ nullptr };
			Vector4<int> rect;
			Shader shader = Shader("assets/shaders/imagem.vert", "assets/shaders/imagem.frag");
			bool preencher{ false };
		};
	}
}