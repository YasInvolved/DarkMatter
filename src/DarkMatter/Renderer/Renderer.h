#ifndef _DM_RENDERER_FACTORY_H_INCLUDED_
#define _DM_RENDERER_FACTORY_H_INCLUDED_

#include <DarkMatter/Renderer/IRenderer.h>
#include <DarkMatter/Renderer/VulkanRenderer.h>
#include <DarkMatter/Engine/Window.h>

namespace DarkMatter::Renderer
{
   enum class RendererAPI
   {
      VULKAN
   };

   struct RendererCreateInfo
   {
      RendererAPI api;
      const Window& window;
   };

   class Renderer
   {
   public:
      static bool Init(const RendererCreateInfo& info);
      static void Shutdown();
      static void BeginFrame();
      static void EndFrame();

   private:
      static std::unique_ptr<IRenderer> s_internalRenderer;
   };
}

#endif