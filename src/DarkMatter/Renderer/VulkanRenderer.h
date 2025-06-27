#ifndef _DM_VULKAN_RENDERER_H_INCLUDED_
#define _DM_VULKAN_RENDERER_H_INCLUDED_

#include <DarkMatter/Engine/Engine.h>
#include <DarkMatter/Renderer/IRenderer.h>
#include <DarkMatter/Renderer/VulkanPhysicalDevice.h>
#include <DarkMatter/Renderer/VulkanLogicalDevice.h>

namespace DarkMatter
{
   class VulkanRenderer : public IRenderer
   {
   public:
      VulkanRenderer(const Engine& engine, std::string_view gameName);

      bool Init() override;
      void Shutdown() override;

      void BeginFrame() override;
      void EndFrame() override;

      void Resize(uint32_t w, uint32_t h) override;

      // void DrawMesh() override;

   private:
      const std::string m_gameName;
      const Engine& m_engine;

      VkInstance m_instance = VK_NULL_HANDLE;
      VkSurfaceKHR m_surface = VK_NULL_HANDLE;
      VkSwapchainKHR m_swapchain = VK_NULL_HANDLE;
      gtl::vector<VulkanPhysicalDevice> m_availableDevices;
      std::unique_ptr<VulkanLogicalDevice> m_device;
   };
}

#endif