#include <DarkMatter/Renderer/VulkanRenderer.h>

using VulkanRenderer = DarkMatter::VulkanRenderer;

VulkanRenderer::VulkanRenderer(const Engine& engine, const std::string_view gameName)
   : m_gameName(gameName), m_engine(engine)
{ }

bool VulkanRenderer::Init()
{
   VkResult result = volkInitialize();
   if (result != VK_SUCCESS)
      return false;

   const VkApplicationInfo applicationInfo =
   {
      .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .pNext = nullptr,
      .pApplicationName = m_gameName.empty() ? "Game" : m_gameName.c_str(),
      .applicationVersion = VK_MAKE_VERSION(1, 0, 0), // TODO: Application version in RendererCreateInfo struct
      .pEngineName = "Dark Matter",
      .engineVersion = VK_MAKE_VERSION(1, 0, 0),
      .apiVersion = VK_API_VERSION_1_3,
   };

   uint32_t count;
   SDL_Vulkan_GetInstanceExtensions(&count);

   static constexpr const char* usedLayers[] = { 
#ifndef _NDEBUG
      "VK_LAYER_KHRONOS_validation" 
#endif
   };

   // TODO: validation layer
   const VkInstanceCreateInfo instanceCreateInfo =
   {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .pApplicationInfo = &applicationInfo,
      .enabledLayerCount = sizeof(usedLayers) / sizeof(const char*),
      .ppEnabledLayerNames = usedLayers,
      .enabledExtensionCount = count,
      .ppEnabledExtensionNames = SDL_Vulkan_GetInstanceExtensions(&count),
   };

   result = vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance);
   if (result != VK_SUCCESS)
      return false;

   volkLoadInstance(m_instance);

   if (!SDL_Vulkan_CreateSurface(m_engine.getWindow().GetHandle(), m_instance, nullptr, &m_surface))
      return false;

   m_availableDevices = VulkanPhysicalDevice::getPhysicalDevices(m_instance);
   for (const auto& physicalDevice : m_availableDevices)
   {
      if (physicalDevice.getQueueFamilies().isComplete())
         m_device = std::make_unique<VulkanLogicalDevice>(physicalDevice);
   }

   if (m_device.get() == nullptr)
      return false;

   // TODO: just check if another device has it
   if (!m_device->requestExtension(VK_KHR_SWAPCHAIN_EXTENSION_NAME))
      return false;

   m_device->requestQueues(m_device->getPhysicalDevice().getQueueFamilies().graphics.value(), 1);

   if (!m_device->initialize())
      return false;

   auto surfaceCapabilities = m_device->getPhysicalDevice().getSurfaceCapabilities(m_surface);
   const auto surfaceFormats = m_device->getPhysicalDevice().getSurfaceFormats(m_surface);

   uint32_t imageCount = surfaceCapabilities.minImageCount + 1;
   if (imageCount > surfaceCapabilities.maxImageCount)
      imageCount = std::clamp(imageCount, surfaceCapabilities.minImageCount, surfaceCapabilities.maxImageCount);

   const auto gfxQueueFamilyIndex = m_device->getPhysicalDevice().getQueueFamilies().graphics.value();

   const VkSwapchainCreateInfoKHR swapchainCreateInfo =
   {
      .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
      .pNext = nullptr,
      .flags = 0,
      .surface = m_surface,
      .minImageCount = imageCount,
      .imageFormat = surfaceFormats[0].format, // TODO: actually select a format
      .imageColorSpace = surfaceFormats[0].colorSpace, 
      .imageExtent = surfaceCapabilities.currentExtent,
      .imageArrayLayers = 1,
      .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
      .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
      .queueFamilyIndexCount = 1,
      .pQueueFamilyIndices = &gfxQueueFamilyIndex,
      .preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
      .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
      .presentMode = VK_PRESENT_MODE_FIFO_KHR,
      .clipped = VK_FALSE,
      .oldSwapchain = nullptr
   };

   if (vkCreateSwapchainKHR(*m_device, &swapchainCreateInfo, nullptr, &m_swapchain) != VK_SUCCESS)
      return false;

   const VkCommandPoolCreateInfo commandPoolCreateInfo =
   {
      .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .queueFamilyIndex = gfxQueueFamilyIndex,
   };  

   if (vkCreateCommandPool(*m_device, &commandPoolCreateInfo, nullptr, &m_commandPool) != VK_SUCCESS)
      return false;

   const VkCommandBufferAllocateInfo commandBufferAllocateInfo =
   {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
      .pNext = nullptr,
      .commandPool = m_commandPool,
      .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
      .commandBufferCount = 1,
   };

   if (vkAllocateCommandBuffers(*m_device, &commandBufferAllocateInfo, &m_commandBuffer) != VK_SUCCESS)
      return false;

   return true;
}

void VulkanRenderer::Shutdown()
{
   vkDeviceWaitIdle(*m_device);

   vkFreeCommandBuffers(*m_device, m_commandPool, 1, &m_commandBuffer);
   vkDestroyCommandPool(*m_device, m_commandPool, nullptr);
   vkDestroySwapchainKHR(*m_device, m_swapchain, nullptr);
   m_device.reset();
   SDL_Vulkan_DestroySurface(m_instance, m_surface, nullptr);
   vkDestroyInstance(m_instance, nullptr);
}

void VulkanRenderer::BeginFrame()
{

}

void VulkanRenderer::EndFrame()
{

}

void VulkanRenderer::Resize(uint32_t w, uint32_t h)
{

}