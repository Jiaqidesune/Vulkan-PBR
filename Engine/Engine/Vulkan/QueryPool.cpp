#include "QueryPool.h"
#include "Device.h"

#include "../Common/Logger.h"

namespace Vulkan
{
	QueryPool::QueryPool(const std::shared_ptr<Device>& device, VkQueryType query_type,
		uint32_t query_count, VkQueryPipelineStatisticFlags pipeline_statistics)
		:m_device(device), m_count(query_count)
	{
		VkQueryPoolCreateInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
		info.queryType = query_type;
		info.queryCount = query_count;
		info.pipelineStatistics = pipeline_statistics;

		if (vkCreateQueryPool(device->GetHandle(), &info, nullptr, &m_query_pool) != VK_SUCCESS)
			K_ERROR("Failed to create Query Pool");
	}

	QueryPool::~QueryPool()
	{
		if (m_query_pool)
			vkDestroyQueryPool(m_device->GetHandle(), m_query_pool, nullptr);
	}

	VkResult QueryPool::GetResults(uint32_t first_query, uint32_t query_count, size_t data_size, void* data,
		VkDeviceSize stride, VkQueryResultFlags flags) const 
	{
		return vkGetQueryPoolResults(m_device->GetHandle(), m_query_pool, first_query, query_count, data_size, data,
			stride, flags);
	}

	VkResult QueryPool::GetResults64(uint32_t first_query, uint32_t query_count, uint64_t* data,
		VkQueryResultFlags flags) const 
	{
		return vkGetQueryPoolResults(m_device->GetHandle(), m_query_pool, first_query, query_count,
			query_count * sizeof(uint64_t), (void*)data, sizeof(uint64_t),
			flags | VK_QUERY_RESULT_64_BIT);
	}

	VkResult QueryPool::GetResults32(uint32_t first_query, uint32_t query_count, uint32_t* data,
		VkQueryResultFlags flags) const 
	{
		return vkGetQueryPoolResults(m_device->GetHandle(), m_query_pool, first_query, query_count,
			query_count * sizeof(uint32_t), (void*)data, sizeof(uint32_t),
			flags & (~VK_QUERY_RESULT_64_BIT));
	}

	VkResult QueryPool::GetResults(size_t data_size, void* data, VkDeviceSize stride, VkQueryResultFlags flags) const
	{
		return GetResults(0, m_count, data_size, data, stride, flags);
	}

	VkResult QueryPool::GetResults64(uint64_t* data, VkQueryResultFlags flags) const
	{
		return GetResults64(0, m_count, data, flags);
	}

	VkResult QueryPool::GetResults32(uint32_t* data, VkQueryResultFlags flags) const 
	{
		return GetResults32(0, m_count, data, flags);
	}
}