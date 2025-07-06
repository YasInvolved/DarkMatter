#include <DarkMatter/Renderer/VulkanCommandPool.h>
#include <iostream>

using VulkanCommandPool = DarkMatter::VulkanCommandPool;

VulkanCommandPool::VulkanCommandPool(const VulkanLogicalDevice& device, uint32_t queueFamilyIdx)
   : m_device(device)
{
   const VkCommandPoolCreateInfo createInfo =
   {
      .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .queueFamilyIndex = queueFamilyIdx
   };

   if (vkCreateCommandPool(m_device, &createInfo, nullptr, &m_handle) != VK_SUCCESS)
      throw std::runtime_error(fmt::format("Failed to create a command pool for queue family idx {}", queueFamilyIdx));
}

VulkanCommandPool::~VulkanCommandPool()
{
   assert(m_handle != VK_NULL_HANDLE && "Destructor called twice");

   vkDestroyCommandPool(m_device, m_handle, nullptr);
   m_handle = VK_NULL_HANDLE;
}