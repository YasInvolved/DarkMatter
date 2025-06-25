#ifndef _DM_RENDERER_VULKAN_PHYSICAL_DEVICE_H_INCLUDED_
#define _DM_RENDERER_VULKAN_PHYSICAL_DEVICE_H_INCLUDED_

namespace DarkMatter
{
   class VulkanPhysicalDevice
   {
   public:
      VulkanPhysicalDevice(VkPhysicalDevice device);
      ~VulkanPhysicalDevice();

      operator VkPhysicalDevice() const { return m_handle; }

      static const gtl::vector<VkPhysicalDevice> getPhysicalDevices(VkInstance instance);
   private:
      VkPhysicalDevice m_handle;
   };
}

#endif