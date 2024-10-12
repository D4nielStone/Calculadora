#include "painel_calc.hpp"
#include <src/ui/widgets/caixa_de_texto.hpp>
#include <src/ui/widgets/botao.hpp>

BubbleUI::Calculadora::Calculadora(std::shared_ptr<Contexto> contexto)
{
	Nome = "Calculadora";
	configurar(contexto);
	selecionado = true;
	preenchido = true;
	adicionarWidget(std::make_shared<BubbleUI::Widgets::CaixaTexto>(nullptr, "expressao", true));
	adicionarWidget(std::make_shared<BubbleUI::Widgets::Botao>("7", nullptr, true, false, 4.f));
	adicionarWidget(std::make_shared<BubbleUI::Widgets::Botao>("8", nullptr, true, false, 4.f));
	adicionarWidget(std::make_shared<BubbleUI::Widgets::Botao>("9", nullptr, true, false, 4.f));
	adicionarWidget(std::make_shared<BubbleUI::Widgets::Botao>("*", nullptr, true, true, 4.f));
	adicionarWidget(std::make_shared<BubbleUI::Widgets::Botao>("4", nullptr, true, false, 4.f));
	adicionarWidget(std::make_shared<BubbleUI::Widgets::Botao>("5", nullptr, true, false, 4.f));
	adicionarWidget(std::make_shared<BubbleUI::Widgets::Botao>("6", nullptr, true, false, 4.f));
	adicionarWidget(std::make_shared<BubbleUI::Widgets::Botao>("-", nullptr, true, true, 4.f));
	adicionarWidget(std::make_shared<BubbleUI::Widgets::Botao>("1", nullptr, true, false, 4.f));
	adicionarWidget(std::make_shared<BubbleUI::Widgets::Botao>("2", nullptr, true, false, 4.f));
	adicionarWidget(std::make_shared<BubbleUI::Widgets::Botao>("3", nullptr, true, false, 4.f));
	adicionarWidget(std::make_shared<BubbleUI::Widgets::Botao>("+", nullptr, true, true, 4.f));
	adicionarWidget(std::make_shared<BubbleUI::Widgets::Botao>("¬", nullptr, true, false, 4.f));
	adicionarWidget(std::make_shared<BubbleUI::Widgets::Botao>("0", nullptr, true, false, 4.f));
	adicionarWidget(std::make_shared<BubbleUI::Widgets::Botao>(".", nullptr, true, false, 4.f));
	adicionarWidget(std::make_shared<BubbleUI::Widgets::Botao>("=", nullptr, true, false, 4.f));
}