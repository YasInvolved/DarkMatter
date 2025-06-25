#include "VulkanPhysicalDevice.h"

using VulkanPhysicalDevice = DarkMatter::VulkanPhysicalDevice;

VulkanPhysicalDevice::VulkanPhysicalDevice(VkPhysicalDevice device)
   : m_handle(device)
{
   uint32_t count;
   vkGetPhysicalDeviceQueueFamilyProperties(m_handle, &count, nullptr);
   gtl::vector<VkQueueFamilyProperties> queueFamilyProperties(count);
   vkGetPhysicalDeviceQueueFamilyProperties(m_handle, &count, queueFamilyProperties.data());
   
   auto areTypesSupported = [this](const VkQueueFlags queueFlags, const VkQueueFlags bits)
      {
         return queueFlags & bits == bits;
      };

   for (uint32_t i = 0; i < count; i++)
   {
      const auto& queueFamilyProperty = queueFamilyProperties[i];

      if (areTypesSupported(queueFamilyProperty.queueFlags, VK_QUEUE_GRAPHICS_BIT))
      {
         m_queueFamilies.graphics = i;
         continue;
      }
      
      else if (!m_queueFamilies.compute.has_value() && areTypesSupported(queueFamilyProperty.queueFlags, VK_QUEUE_COMPUTE_BIT | ~VK_QUEUE_TRANSFER_BIT))
      {
         m_queueFamilies.compute = i;
         continue;
      }

      else if (!m_queueFamilies.transfer.has_value() && areTypesSupported(queueFamilyProperty.queueFlags, VK_QUEUE_TRANSFER_BIT | ~VK_QUEUE_COMPUTE_BIT))
      {
         m_queueFamilies.transfer = i;
         continue;
      }

      // TODO: rest of the families are not needed for now, implement them later
   }
}

VulkanPhysicalDevice::~VulkanPhysicalDevice()
{ }

const gtl::vector<VulkanPhysicalDevice> VulkanPhysicalDevice::getPhysicalDevices(VkInstance instance)
{
   uint32_t count;
   vkEnumeratePhysicalDevices(instance, &count, nullptr);
   gtl::vector<VkPhysicalDevice> nativeHandles(count);
   vkEnumeratePhysicalDevices(instance, &count, nativeHandles.data());

   gtl::vector<VulkanPhysicalDevice> devices;
   devices.reserve(nativeHandles.size());

   for (auto handle : nativeHandles)
   {
      devices.emplace_back(handle);
   }

   return devices;
}

const gtl::vector<VkExtensionProperties> VulkanPhysicalDevice::getAvailableExtensions(const std::string_view layerName) const
{
   uint32_t count;
   vkEnumerateDeviceExtensionProperties(m_handle, layerName.data(), &count, nullptr);
   gtl::vector<VkExtensionProperties> extensionProperties(count);
   vkEnumerateDeviceExtensionProperties(m_handle, layerName.data(), &count, extensionProperties.data());

   return extensionProperties;
}

const gtl::vector<VkLayerProperties> VulkanPhysicalDevice::getAvailableLayers() const
{
   uint32_t count;
   vkEnumerateDeviceLayerProperties(m_handle, &count, nullptr);
   gtl::vector<VkLayerProperties> layerProperties(count);
   vkEnumerateDeviceLayerProperties(m_handle, &count, layerProperties.data());

   return layerProperties;
}