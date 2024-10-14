#pragma once
#include "bubbleui.hpp"
#include "string"
#include <map>
#include <ft2build.h>
#include <src/util/includes.hpp>
#include FT_FREETYPE_H

namespace Bubble
{
	namespace Arquivadores
	{
		struct BEUI_DLL_API Character
		{
			unsigned int TextureID;  // ID handle of the glyph texture
			Vector2 Size;       // Size of glyph
			Vector2 Bearing;    // Offset from baseline to left/top of glyph
			FT_Pos Advance;    // Offset to advance to next glyph
		};
		BEUI_DLL_API std::map<char32_t, Character>* obterCaracteres();
		BEUI_DLL_API void carregarFonte(std::string path);
		BEUI_DLL_API void definirResolucao(int resolution);
	}
}