#pragma once
#include "src/ui/widgets/texto.hpp"
#include "interface.hpp"

namespace Interface
{
	class Painel;
	class UI_DLL_API Aba : public Widgets::Texto
	{
	public:
		Aba() = default;
		Aba(Painel* painel);
		void atualizar() override;
		void renderizar() const override;
		Formas::Rect* obterCorpo() const;
	private:
		std::vector<LetraRect> letras_rect;
		std::unique_ptr<Formas::Rect>corpo_rect;
	};
}