#pragma once

#include <vulkan/vulkan.h>
#include <string>

#include <shaderc/shaderc.h>

namespace RHI
{
	enum class ShaderKind
	{
		Vertex = 0,
		Fragment,
		Compute,
		Geometry,
		TessellationControl,
		TessellationEvaulation,
	};

	class Device;

	class Shader
	{
	public:
		Shader(const Device* device)
			: device(device) { }

		~Shader();

		bool compileFromFile(const char* path);
		bool compileFromFile(const char* path, ShaderKind kind);
		bool reload();
		void clear();

		inline VkShaderModule getShaderModule() const { return shaderModule; }

	private:
		bool compileFromSourceInternal(const char* path, const char* sourceData, size_t sourceSize, shaderc_shader_kind kind);

	private:
		const Device* device;

		std::string shaderPath;
		VkShaderModule shaderModule{ VK_NULL_HANDLE };
	};

}
