#include <DarkMatter/Renderer/VulkanRenderer.h>
#include <DarkMatter/Embedded/basic_vert_glsl.h>
#include <DarkMatter/Embedded/basic_frag_glsl.h>

using VulkanRenderer = DarkMatter::VulkanRenderer;

VulkanRenderer::VulkanRenderer(const Engine& engine, const std::string_view gameName)
   : m_gameName(gameName), m_engine(engine)
{ }

bool VulkanRenderer::Init()
{
   auto& logger = m_engine.getLoggerManager().getLoggerByName(s_loggerName);
   auto& threadPool = m_engine.getThreadPool();

   auto vertexShaderCompileFuture = threadPool.enqueue([this, &logger]()
      {
         std::string shaderCode(Embedded::basic_vert_glsl, Embedded::basic_vert_glsl + Embedded::basic_vert_glsl_len);

         auto result = compileGLSL("basic.vert.glsl", shaderCode, shaderc_shader_kind::shaderc_glsl_vertex_shader);
         if (!result.result)
            throw std::runtime_error("Failed to compile vertex shader");

         return result.data;
      }
   );

   auto fragmentShaderCompileFuture = threadPool.enqueue([this, &logger]()
      {
         std::string shaderCode(Embedded::basic_frag_glsl, Embedded::basic_frag_glsl + Embedded::basic_frag_glsl_len);
         auto result = compileGLSL("basic.frag.glsl", shaderCode, shaderc_shader_kind::shaderc_glsl_fragment_shader);

         if (!result.result)
            throw std::runtime_error("Failed to compile fragment shader");

         return result.data;
      }
   );

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
#ifdef DM_DEBUG
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

   m_commandPool = std::make_unique<VulkanCommandPool>(*m_device, m_device->getPhysicalDevice().getQueueFamilies().graphics.value());

   return buildBasicGraphicsPipeline(vertexShaderCompileFuture.get(), fragmentShaderCompileFuture.get());
}

void VulkanRenderer::Shutdown()
{
   vkDeviceWaitIdle(*m_device);

   m_commandPool.reset();
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

VulkanRenderer::ShaderCompileResult VulkanRenderer::compileGLSL(const std::string_view filename, const std::string& source, shaderc_shader_kind kind)
{
   static shaderc::Compiler s_shaderCompiler;
   static shaderc::CompileOptions s_compileOptions;
   static auto& s_logger = m_engine.getLoggerManager().getLoggerByName(s_loggerName);
   s_compileOptions.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_3);

   auto result = s_shaderCompiler.CompileGlslToSpv(source, kind, filename.data(), s_compileOptions);

   if (result.GetCompilationStatus() != shaderc_compilation_status_success)
   {
      s_logger.error("Failed to compile {}: {}", filename, result.GetErrorMessage());
      return { false, {} };
   }

   s_logger.info("{} compiled successfully!", filename);
   return { true, { result.begin(), result.end() } };
}

bool VulkanRenderer::buildBasicGraphicsPipeline(const gtl::vector<uint32_t>& vertShaderBinary, const gtl::vector<uint32_t>& fragShaderBinary)
{
   static auto& s_logger = m_engine.getLoggerManager().getLoggerByName(s_loggerName);
   assert(m_device.get() != nullptr);

   s_logger.info("Vertex shader size: {}", vertShaderBinary.size());
   s_logger.info("Fragment shader size: {}", fragShaderBinary.size());

   const VkShaderModuleCreateInfo vertShaderCreateInfo =
   {
      .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .codeSize = vertShaderBinary.size() * sizeof(uint32_t),
      .pCode = vertShaderBinary.data(),
   };

   VkShaderModule vertShader;
   if (!vkCreateShaderModule(*m_device, &vertShaderCreateInfo, nullptr, &vertShader))
      return false;

   const VkShaderModuleCreateInfo fragShaderCreateInfo =
   {
      .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .codeSize = fragShaderBinary.size() * sizeof(uint32_t),
      .pCode = fragShaderBinary.data()
   };

   VkShaderModule fragShader;
   if (!vkCreateShaderModule(*m_device, &fragShaderCreateInfo, nullptr, &fragShader))
      return false;

   vkDestroyShaderModule(*m_device, fragShader, nullptr);
   vkDestroyShaderModule(*m_device, vertShader, nullptr);
   return true;
}