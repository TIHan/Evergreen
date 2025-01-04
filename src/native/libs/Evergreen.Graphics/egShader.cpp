#include <stdexcept>
#include <glslang_c_interface.h>
#include <glslang/Public/resource_limits_c.h>

#include "egShader.h"

static glsl_include_result_t* include_local_callback(void* ctx, const char* header_name, const char* includer_name, size_t include_depth)
{
	char buf[1024];
	snprintf(buf, sizeof(buf), "Shaders/%s", header_name);

	FILE* file;
	if (fopen_s(&file, buf, "r") != 0)
	{
		throw std::exception("Unable to open file");
	}

	fseek(file, 0L, SEEK_END);
	long fileSize = ftell(file);
	rewind(file);

	char* fileBuffer = new char[fileSize];
	size_t bytesRead = fread(fileBuffer, sizeof(char), fileSize, file);

	fclose(file);

	glsl_include_result_t* result = new glsl_include_result_t();
	result->header_name = header_name;
	result->header_data = fileBuffer;
	result->header_length = bytesRead;
	return result;
}

extern "C" {

	EG_EXPORT int egShaderInitialize()
	{
		return glslang_initialize_process();
	}

	EG_EXPORT void egShaderFinalize()
	{
		glslang_finalize_process();
	}

	EG_EXPORT EgShaderBool egShaderCompile(
			EgShaderKind kind, 
			const char* text, 
			unsigned int textLength, 
			void(*callback)(char*, unsigned int), 
			void(*callbackError)(const char*))
	{
		glslang_stage_t stage;
		switch (kind)
		{
		case EgShaderKind_VERTEX:
			stage = GLSLANG_STAGE_VERTEX;
			break;

		case EgShaderKind_FRAGMENT:
			stage = GLSLANG_STAGE_FRAGMENT;
			break;

		case EgShaderKind_COMPUTE:
			stage = GLSLANG_STAGE_COMPUTE;
			break;

		case EgShaderKind_GEOMETRY:
			stage = GLSLANG_STAGE_GEOMETRY;
			break;

		case EgShaderKind_TESSCONTROL:
			stage = GLSLANG_STAGE_TESSCONTROL;
			break;

		case EgShaderKind_TESSEVALUATION:
			stage = GLSLANG_STAGE_TESSEVALUATION;
			break;

		default:
			callbackError("Invalid shader kind");
			return false;
		}

		glslang_input_t input = { };
		input.language = GLSLANG_SOURCE_GLSL;
		input.stage = stage;
		input.client = GLSLANG_CLIENT_VULKAN;
		input.client_version = GLSLANG_TARGET_VULKAN_1_3;
		input.target_language_version = GLSLANG_TARGET_SPV_1_3;
		input.target_language = GLSLANG_TARGET_SPV;
		input.code = text;
		input.default_version = 450;
		input.default_profile = GLSLANG_NO_PROFILE;
		input.force_default_version_and_profile = false;
		input.forward_compatible = false;
		input.messages = GLSLANG_MSG_DEFAULT_BIT;
		input.resource = glslang_default_resource();
		input.callbacks.include_local = include_local_callback;

		glslang_shader_t* shader = glslang_shader_create(&input);
		if (!shader)
		{
			callbackError("Unable to create shader");
			return false;
		}

		if (!glslang_shader_preprocess(shader, &input))
		{
			callbackError(glslang_shader_get_info_log(shader));
			glslang_shader_delete(shader);
			return false;
		}

		if (!glslang_shader_parse(shader, &input))
		{
			callbackError(glslang_shader_get_info_log(shader));
			glslang_shader_delete(shader);
			return false;
		}

		auto program = glslang_program_create();
		glslang_program_add_shader(program, shader);
		if (!glslang_program_link(program, GLSLANG_MSG_SPV_RULES_BIT | GLSLANG_MSG_VULKAN_RULES_BIT))
		{
			callbackError(glslang_shader_get_info_log(shader));
			glslang_program_delete(program);
			glslang_shader_delete(shader);
			return false;
		}

		glslang_spv_options_t options;
		options.generate_debug_info = false;
		options.strip_debug_info = true;
		options.disable_optimizer = false;
		options.optimize_size = false;
		options.disassemble = false;
		options.validate = false;
		options.emit_nonsemantic_shader_debug_info = false;
		options.emit_nonsemantic_shader_debug_source = false;

		glslang_program_SPIRV_generate_with_options(program, stage, &options);

		auto dataLength = glslang_program_SPIRV_get_size(program) * sizeof(unsigned int);
		auto data = (char*)glslang_program_SPIRV_get_ptr(program);
		callback(data, dataLength);

		glslang_program_delete(program);
		glslang_shader_delete(shader);

		return true;
	}

}