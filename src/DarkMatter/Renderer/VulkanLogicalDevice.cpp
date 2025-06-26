#include "VulkanLogicalDevice.h"

using VulkanLogicalDevice = DarkMatter::VulkanLogicalDevice;

VulkanLogicalDevice::VulkanLogicalDevice(const VulkanPhysicalDevice& physicalDevice)
   : m_physicalDevice(physicalDevice)
{
   m_extensionProperties = m_physicalDevice.getAvailableExtensions();
   m_layerProperties = m_physicalDevice.getAvailableLayers();
}

VulkanLogicalDevice::~VulkanLogicalDevice()
{
   if (m_isInitialized)
   {
      vkDestroyDevice(m_handle, nullptr);
      m_isInitialized = false;
   }
}

bool VulkanLogicalDevice::requestExtension(const std::string_view extensionName)
{
   for (const auto& property : m_extensionProperties)
   {
      if (std::strcmp(property.extensionName, extensionName.data()) == 0)
      {
         m_enabledExtensions.emplace_back(property.extensionName);
         return true;
      }
   }

   return false;
}

bool VulkanLogicalDevice::requestLayer(const std::string_view layerName)
{
   for (const auto& property : m_layerProperties)
   {
      if (std::strcmp(property.layerName, layerName.data()) == 0)
      {
         m_enabledExtensions.emplace_back(property.layerName);
         return true;
      }
   }

   return false;
}

void VulkanLogicalDevice::requestQueues(uint32_t family, uint32_t count)
{
   if (!m_requestedQueues.contains(family))
   {
      m_requestedQueues.emplace(family, count);
      return;
   }

   m_requestedQueues[family] += count;
}

bool VulkanLogicalDevice::initialize()
{
   gtl::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
   queueCreateInfos.reserve(m_requestedQueues.size());

   auto transformToQueueCreateInfo = [](uint32_t famIdx, uint32_t count)
      {
         static constexpr float priority = 1.0f;

         return VkDeviceQueueCreateInfo
         {
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .queueFamilyIndex = famIdx,
            .queueCount = count,
            .pQueuePriorities = &priority,
         };
      };

   for (const auto& [family, count] : m_requestedQueues)
   {
      queueCreateInfos.emplace_back(transformToQueueCreateInfo(family, count));
   }

   const VkDeviceCreateInfo deviceCreateInfo =
   {
      .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size()),
      .pQueueCreateInfos = queueCreateInfos.data(),
      .enabledLayerCount = static_cast<uint32_t>(m_enabledLayers.size()),
      .ppEnabledLayerNames = m_enabledLayers.data(),
      .enabledExtensionCount = static_cast<uint32_t>(m_enabledExtensions.size()),
      .ppEnabledExtensionNames = m_enabledExtensions.data(),
      .pEnabledFeatures = nullptr, // TODO: enable needed features
   };

   m_isInitialized = vkCreateDevice(m_physicalDevice, &deviceCreateInfo, nullptr, &m_handle) == VK_SUCCESS;
   if (!m_isInitialized)
      return false;

   volkLoadDevice(m_handle);
   return true;
}