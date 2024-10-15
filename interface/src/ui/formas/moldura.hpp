#pragma once
#include "rect.hpp"
#include "linha.hpp"

namespace Interface
{
	namespace Formas
	{
		class UI_DLL_API Moldura : public Rect
		{
		public: 
			Moldura(std::shared_ptr<Contexto>, const Vector4<int>& retangulo = {0, 0, 100, 20});
			Moldura() = default;

			// Sobrecarga do operador de atribuição
			Moldura& operator=(const Moldura& other);

			void atualizar() override;
			void renderizar() const override;
			std::shared_ptr<Contexto> obtCtx() const;
			Vector2<int> posicaoWidget{ 0, 0 };
			const Vector2<int> widgetPadding{ 3, 3 };
			bool ocultar_linhas{ false };
		protected:
			virtual void preAtualizacao() {};
			virtual void posAtualizacao() {};
			std::unique_ptr<Linha>
				linha_d{ nullptr },
				linha_e{ nullptr },
				linha_c{ nullptr }, 
				linha_b{ nullptr };
		};
	}
}