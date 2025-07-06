#ifndef _DM_RENDERER_VULKAN_COMMAND_POOL_H_INCLUDED_
#define _DM_RENDERER_VULKAN_COMMAND_POOL_H_INCLUDED_

#include <DarkMatter/Renderer/VulkanLogicalDevice.h>

namespace DarkMatter
{
   class VulkanCommandPool
   {
   public:
      VulkanCommandPool(const VulkanLogicalDevice& device, uint32_t queueFamilyIdx);
      ~VulkanCommandPool();

      operator VkCommandPool() const { return m_handle; }
   private:
      const VulkanLogicalDevice& m_device;
      VkCommandPool m_handle;
   };
}

#endif