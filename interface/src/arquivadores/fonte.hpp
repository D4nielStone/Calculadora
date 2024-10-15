#pragma once
#include "interface.hpp"
#include "string"
#include <map>
#include <ft2build.h>
#include <src/util/includes.hpp>
#include FT_FREETYPE_H

namespace Bubble
{
	namespace Arquivadores
	{
		struct UI_DLL_API Character
		{
			uint TextureID;  // ID handle of the glyph texture
			Vector2 Size;       // Size of glyph
			Vector2 Bearing;    // Offset from baseline to left/top of glyph
			FT_Pos Advance;    // Offset to advance to next glyph
		};
		UI_DLL_API std::map<char32_t, Character>* obterCaracteres();
		UI_DLL_API void carregarFonte(std::string path);
		UI_DLL_API void definirResolucao(int resolution);
	}
}