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

      // always available getters
      const VulkanPhysicalDevice& getPhysicalDevice() const { return m_physicalDevice; }

      // configuration functions
      bool requestExtension(const std::string_view extensionName);
      bool requestLayer(const std::string_view layerName);
      void requestQueues(uint32_t family, uint32_t count); // TODO: add priority when needed

      bool initialize();

      operator VkDevice() const { return m_handle; }

   private:
      bool m_isInitialized = false;

      const VulkanPhysicalDevice& m_physicalDevice;
      VkDevice m_handle = nullptr;

      gtl::vector<VkExtensionProperties> m_extensionProperties;
      gtl::vector<const char*> m_enabledExtensions;
      gtl::flat_hash_map<uint32_t, uint32_t> m_requestedQueues;

      gtl::vector<VkLayerProperties> m_layerProperties;
      gtl::vector<const char*> m_enabledLayers;
   };
}

#endif