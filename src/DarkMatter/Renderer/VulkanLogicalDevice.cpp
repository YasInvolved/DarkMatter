#include "VulkanLogicalDevice.h"

using VulkanLogicalDevice = DarkMatter::VulkanLogicalDevice;

VulkanLogicalDevice::VulkanLogicalDevice(const VulkanPhysicalDevice& physicalDevice)
   : m_physicalDevice(physicalDevice)
{ }

VulkanLogicalDevice::~VulkanLogicalDevice()
{
   if (m_isInitialized)
      vkDestroyDevice(m_handle, nullptr);
}