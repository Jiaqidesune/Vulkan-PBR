#pragma once

#include <vulkan/vulkan.h>
#include <vector>

struct VulkanRendererContext;

namespace RHI
{
	class VulkanUtils
	{
	public:
		static uint32_t findMemoryType(
			const VulkanRendererContext& context,
			uint32_t typeFilter,
			VkMemoryPropertyFlags properties);

		static VkSampler createSampler(
			const VulkanRendererContext& context,
			uint32_t mipLevels);

		static VkShaderModule createShaderModule(
			const VulkanRendererContext& context,
			const uint32_t* bytecode,
			size_t bytecodeSize);

		static VkImageView createImageView(
			const VulkanRendererContext& context,
			VkImage image,
			VkFormat format,
			VkImageAspectFlags aspectFlags,
			VkImageViewType viewType,
			uint32_t baseMipLevel = 0,
			uint32_t numMipLevels = 1,
			uint32_t baseLayer = 0,
			uint32_t numLayers = 1);

		static void createImageCube(
			const VulkanRendererContext& context,
			uint32_t width,
			uint32_t height,
			uint32_t mipLevels,
			VkSampleCountFlagBits numSamples,
			VkFormat format,
			VkImageTiling tiling,
			VkImageUsageFlags usage,
			VkMemoryPropertyFlags memoryProperties,
			VkImage& image,
			VkDeviceMemory& memory);

		static void createImage2D(const VulkanRendererContext& context,
			uint32_t width,
			uint32_t height,
			uint32_t mipLevels,
			VkSampleCountFlagBits numSamples,
			VkFormat format,
			VkImageTiling tiling,
			VkImageUsageFlags usage,
			VkMemoryPropertyFlags memoryProperties,
			VkImage& image,
			VkDeviceMemory& memory);

		static void createBuffer(const VulkanRendererContext& context,
			VkDeviceSize size,
			VkBufferUsageFlags usage,
			VkMemoryPropertyFlags memoryProperties,
			VkBuffer& buffer,
			VkDeviceMemory& memory);

		// Helper functions recording and excuting a command buffer
		static void transitionImageLayout(
			const VulkanRendererContext& context,
			VkImage image,
			VkFormat format,
			VkImageLayout oldLayout,
			VkImageLayout newLayout,
			uint32_t baseMipLevel = 0,
			uint32_t numMipLevels = 1,
			uint32_t baseLayer = 0,
			uint32_t numLayers = 1);

		static void copyBuffer(
			const VulkanRendererContext& context,
			VkBuffer src,
			VkBuffer dst,
			VkDeviceSize size);

		// Which part of the buffer is going to be copied and which part of the image
		static void copyBufferToImage(
			const VulkanRendererContext& context,
			VkBuffer src,
			VkImage dst,
			uint32_t width,
			uint32_t height);

		static void generateImage2DMipmaps(
			const VulkanRendererContext& context,
			VkImage image,
			uint32_t width,
			uint32_t height,
			uint32_t mipLevels,
			VkFormat format,
			VkFilter filter);

		static void bindCombinedImageSampler(
			const VulkanRendererContext& context,
			VkDescriptorSet descriptorSet,
			int binding,
			VkImageView imageView,
			VkSampler sampler);

		static void bindUniformBuffer(
			const VulkanRendererContext& context,
			VkDescriptorSet descriptorSet,
			int binding,
			VkBuffer buffer,
			VkDeviceSize offset,
			VkDeviceSize size);

		static VkSampleCountFlagBits getMaxUsableSampleCount(const VulkanRendererContext& context);

		// Helper functions recording and excuting a command buffer
		static VkCommandBuffer beginSingleTimeCommands(const VulkanRendererContext& context);
		static void endSingleTimeCommands(const VulkanRendererContext& context, VkCommandBuffer commandBuffer);
	private:
		static bool hasStencilComponent(VkFormat format);
	};
}