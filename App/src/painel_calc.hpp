#pragma once
#include "src/ui/painel/painel.hpp"
namespace BubbleUI
{
	class Calculadora : public Painel
	{
	public:
		Calculadora(std::shared_ptr<Contexto> contexto);
	};
}