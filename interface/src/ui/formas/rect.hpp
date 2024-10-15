#pragma once
#include <glad/glad.h>
#include "interface.hpp"
#include "src/util/includes.hpp"
#include "src/ui/contexto/contexto.hpp"

namespace Interface
{
	namespace Formas
	{

		class UI_DLL_API Rect
		{
		public:
			Rect() = default;
			Rect(std::shared_ptr<Contexto> ctx, const Vector4<int>& rect = {0, 0, 0, 0});
			Vector4<int> obtRect() const;
			Vector4<float> obtRectNDC() const;
			void defTam(const Vector2 &tam);
			void defPos(const Vector2 &pos);
			void adiTam(const Vector2 &tam);
			void adiPos(const Vector2 &tam);
			void defCor(const Color &cor);
			virtual void atualizar();
			virtual void renderizar() const;
		protected:
			std::shared_ptr<Contexto> contexto{ nullptr };
			Vector4<int> retangulo, tamanhoAnterior;
			Color cor_base	{ 0.2f, 0.2f, 0.2f, 1.f };
			Vector4<float> coord_ndc;
			Size tamanhoDoContextoAnterior;
			Shader shader{ Shader("assets/shaders/quad.vert", "assets/shaders/quad.frag") };
			void definirBuffers();
		};
	}
}
