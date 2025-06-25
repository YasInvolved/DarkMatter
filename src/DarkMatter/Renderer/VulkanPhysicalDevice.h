#ifndef _DM_RENDERER_VULKAN_PHYSICAL_DEVICE_H_INCLUDED_
#define _DM_RENDERER_VULKAN_PHYSICAL_DEVICE_H_INCLUDED_

namespace DarkMatter
{
   class VulkanPhysicalDevice
   {
   public:
      struct QueueFamilies
      {
         std::optional<uint32_t> graphics;
         std::optional<uint32_t> compute;
         std::optional<uint32_t> transfer;
         std::optional<uint32_t> sparseResources;
         std::optional<uint32_t> videoDecode;
         std::optional<uint32_t> videoEncode;
         std::optional<uint32_t> opticalFlow;

         bool isComplete() const
         {
            return graphics.has_value() && transfer.has_value();
         }
      };

      VulkanPhysicalDevice(VkPhysicalDevice device);
      ~VulkanPhysicalDevice();

      operator VkPhysicalDevice() const { return m_handle; }

      static const gtl::vector<VulkanPhysicalDevice> getPhysicalDevices(VkInstance instance);

      const QueueFamilies& getQueueFamilies() const { return m_queueFamilies; }
      const gtl::vector<VkExtensionProperties> getAvailableExtensions(const std::string_view layerName = { nullptr }) const;
      const gtl::vector<VkLayerProperties> getAvailableLayers() const;

   private:
      VkPhysicalDevice m_handle;
      QueueFamilies m_queueFamilies;
   };
}

#endif