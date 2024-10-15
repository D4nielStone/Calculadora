#pragma once
#include "glad/glad.h"
#include "interface.hpp"
#include "src/util/includes.hpp"
#include "src/ui/contexto/contexto.hpp"

namespace Interface
{
	namespace Formas
	{

		class UI_DLL_API Linha
		{
		public:
			Linha() = default;
			Linha(const Vector4<int> &posicoes, std::shared_ptr<Contexto> ctx);
			void defPos(const Vector4<int> &posicoes);
			void defCor(const Color &cor);
			void atualizar();
			void renderizar() const;
		protected:
			std::shared_ptr<Contexto> contexto;
			Vector4<int> posicoes, tamanhoAnterior;
			Color cor_base;
		private:	
			Vector4<float> coord_ndc;
			Size tamanhoDoContextoAnterior;
			Shader shader = Shader("assets/shaders/linha.vert", "assets/shaders/linha.frag");
		};
	}
}
