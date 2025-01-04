#pragma once

#define EG_EXPORT __declspec(dllexport)

typedef int EgShaderBool;

enum EgShaderKind
{
	EgShaderKind_VERTEX,
	EgShaderKind_FRAGMENT,
	EgShaderKind_COMPUTE,
	EgShaderKind_GEOMETRY,
	EgShaderKind_TESSCONTROL,
	EgShaderKind_TESSEVALUATION
};

extern "C" {

	EG_EXPORT int egShaderInitialize();
	EG_EXPORT void egShaderFinalize();
	EG_EXPORT EgShaderBool egShaderCompile(EgShaderKind kind, const char* text, unsigned int textLength, void(*callback)(char*, unsigned int), void(*callbackError)(const char*));

}
