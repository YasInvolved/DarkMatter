#include "VulkanPhysicalDevice.h"

using VulkanPhysicalDevice = DarkMatter::VulkanPhysicalDevice;

VulkanPhysicalDevice::VulkanPhysicalDevice(VkPhysicalDevice device)
   : m_handle(device)
{}

VulkanPhysicalDevice::~VulkanPhysicalDevice()
{ }

const gtl::vector<VkPhysicalDevice> VulkanPhysicalDevice::getPhysicalDevices(VkInstance instance)
{
   uint32_t count;
   vkEnumeratePhysicalDevices(instance, &count, nullptr);
   gtl::vector<VkPhysicalDevice> nativeHandles(count);
   vkEnumeratePhysicalDevices(instance, &count, nativeHandles.data());

   gtl::vector<VkPhysicalDevice> devices;
   devices.reserve(nativeHandles.size());

   for (auto handle : nativeHandles)
   {
      devices.emplace_back(handle);
   }

   return devices;
}