#pragma once
#include "src/ui/painel/painel.hpp"
namespace Interface
{
	class Calculadora : public Painel
	{
	public:
		Calculadora(std::shared_ptr<Contexto> contexto);
	};
}