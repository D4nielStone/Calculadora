#include "imagem.hpp"
#include "texto.hpp"
#include "src/ui/painel/separador.hpp"

namespace Interface
{
	namespace Widgets
	{
		class UI_DLL_API SeletorDeCor : public Texto
		{
		public:
			SeletorDeCor(Color* cor, const std::string& label, const Alinhamento& alinhamento = Alinhamento::Centro);
			void atualizar() override;
			void renderizar() const override;
			void defPainel(Painel* painel) override;
			void calcularCor();
		private:
			Color* cor_callback{ nullptr };
			const uint raio{ 48 };
			float angulo{}, hue{}, saturacao{}, brilho{0.5};
			std::unique_ptr<Imagem> arco_cor{ nullptr };
		};
	}
}