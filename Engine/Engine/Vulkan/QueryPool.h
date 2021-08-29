#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include <vector>

#include "DeviceObjectBase.h"

namespace Vulkan
{
	class QueryPool : public DeviceObjectBase
	{
	public:
		QueryPool(const std::shared_ptr<Device>& device, VkQueryType query_type,
			uint32_t query_count, VkQueryPipelineStatisticFlags pipeline_statistics = 0);

		~QueryPool();

		VkResult GetResults(uint32_t first_query, uint32_t query_count, size_t data_size, void* data, VkDeviceSize stride,
			VkQueryResultFlags flags) const;
		VkResult GetResults(size_t data_size, void* data, VkDeviceSize stride, VkQueryResultFlags flags) const;

		VkResult GetResults64(uint32_t first_query, uint32_t query_count, uint64_t* data, VkQueryResultFlags flags) const;
		VkResult GetResults64(uint64_t* data, VkQueryResultFlags flags) const;

		VkResult GetResults32(uint32_t first_query, uint32_t query_count, uint32_t* data, VkQueryResultFlags flags) const;
		VkResult GetResults32(uint32_t* data, VkQueryResultFlags flags) const;

		// Getters
		VkQueryPool GetHandle() const { return m_query_pool; }
		uint32_t GetCount() const { return m_count; }
		const std::shared_ptr<Device>& GetDevicePtr() const override { return m_device; };
	private:
		std::shared_ptr<Device> m_device;

		VkQueryPool m_query_pool{ VK_NULL_HANDLE };
		uint32_t m_count{ 0 };
	};
}