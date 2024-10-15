#pragma once
#include "src/ui/contexto/contexto.hpp"
#include "src/util/includes.hpp"

namespace Interface
{
	class UI_DLL_API Colisao2d
	{
	public:
		Colisao2d() = default;
		Colisao2d(const Vector4<int> &quadrado, std::shared_ptr<Contexto> ctx);
		~Colisao2d() = default;
		void defRect(const Vector4<int> &quad);
		bool mouseEmCima() const;
	private:
		Vector4<int> quadrado;
		std::shared_ptr<Contexto> contexto{ nullptr };
		uint raio = 0;
	};
}
