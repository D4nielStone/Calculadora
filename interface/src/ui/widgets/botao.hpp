#include "texto.hpp"
#include "imagem.hpp"

namespace Interface
{
	namespace Widgets
	{
		class UI_DLL_API Botao : public Texto
		{
		public:
			Botao(const std::string &label_shared, std::function<void()> funcao_click, const std::string& imagePath,bool completo = true);
			Botao(const std::string &label_shared, std::function<void()> funcao_click, bool completo = true);
			Botao(const std::string &label_shared, bool* callback = nullptr, bool completo = true, bool quebrar_linha = true, float divisao_horizontal = 1.f);
			void atualizar() override;
			void renderizar() const override;
		private:
			bool completo{}, gatilho{ false }, * Callback{ nullptr };
			std::function<void()> funcao_click_;
			std::unique_ptr<Imagem> icon{ nullptr };
		};
	}
}