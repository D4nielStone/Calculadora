#pragma once
#include <string>
#include "src/ui/widgets/widget.hpp"
#include "src/arquivadores/fonte.hpp"

namespace Interface
{
	namespace Widgets
	{
		class UI_DLL_API Texto : public Widget
		{
		public:
			Texto(std::string* label_shared);
			Texto(const std::string& label_shared);
			Texto() = default;
			void atualizar() override;
			void renderizar() const override;
			static void configurar(const uint resolucao = 12, const std::string& font_path = "assets/fontes/consolas/consolas.tff");
		protected:
			// métodos de renderização
			bool desenharSelecao(Vector2 mouse_inicial, Vector2 mouse_final, Vector4<float> char_rect, size_t letra_idx);
			void renderizar_texto(const std::string &frase);

			// !variáveis privadas
			size_t texto_cursor_index{ 0 };		// index da posição do cursor no texto
			Vector4<float> texto_cursor_pos;	// posição normalizada do cursor
			bool selecionando_texto{ false };	// texto está selecionado?
			const uint resolucao{14};				// resolução da fonte
			const uint lines_box_limite{3};		// limite de linhas para escrever
			uint largura_texto;					// largura do texto
			float DivisaoHorizontal{ 1.f };		// divisão para alihamento de largura = largura painel/divisao horizontal
			Vector2 box_size, box_pos, line_pos;
			const Vector2 letra_padding{3, 3};
			std::string frase;
			Color cor, cor_de_selecao{ 0.678f, 0.847f, 0.902f, 1.0f};
			Vector2 pos_texto;
			Vector4<int> char_rect, char_fundo_rect;
			std::vector<LetraRect> letras_rect;
			Vector4<int> area_de_selecao;
			Shader shader = Shader("assets/shaders/texto.vert", "assets/shaders/texto.frag"), shaderQuad = Shader("assets/shaders/quad.vert", "assets/shaders/quad.frag");
			std::string* label_shared{ nullptr };
		};
	}
}