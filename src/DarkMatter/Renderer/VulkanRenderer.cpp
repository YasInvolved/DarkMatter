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

   // TODO: validation layer
   const VkInstanceCreateInfo instanceCreateInfo =
   {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .pApplicationInfo = &applicationInfo,
      .enabledLayerCount = 0,
      .ppEnabledLayerNames = nullptr,
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

   return true;
}

void VulkanRenderer::Shutdown()
{
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