#include "VulkanPhysicalDevice.h"

using VulkanPhysicalDevice = DarkMatter::VulkanPhysicalDevice;

VulkanPhysicalDevice::VulkanPhysicalDevice(VkPhysicalDevice device)
   : m_handle(device)
{}

VulkanPhysicalDevice::~VulkanPhysicalDevice()
{ }