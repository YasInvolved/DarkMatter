#ifndef _DM_RENDERER_VULKAN_LOGICAL_DEVICE_H_INCLUDED_
#define _DM_RENDERER_VULKAN_LOGICAL_DEVICE_H_INCLUDED_

#include "VulkanPhysicalDevice.h"

namespace DarkMatter
{
   class VulkanLogicalDevice
   {
   public:
      VulkanLogicalDevice(const VulkanPhysicalDevice& physicalDevice);
      ~VulkanLogicalDevice();

      operator VkDevice() const { return m_handle; }

   private:
      bool m_isInitialized = false;

      const VkPhysicalDevice& m_physicalDevice;
      VkDevice m_handle = nullptr;
   };
}

#endif