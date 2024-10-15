#pragma once
#ifdef _WIN32
#ifdef BEUI_EXPORTS
#define UI_DLL_API// __declspec(dllexport)
#else
#define UI_DLL_API// __declspec(dllimport)
#endif
#else
#define BEUI_EXPORTS
#endif