#ifndef _DM_VULKAN_RENDERER_H_INCLUDED_
#define _DM_VULKAN_RENDERER_H_INCLUDED_

#include <DarkMatter/Renderer/IRenderer.h>

namespace DarkMatter
{
   class VulkanRenderer : public IRenderer
   {
   public:
      VulkanRenderer(const std::string_view gameName);

      void Init() override;
      void Shutdown() override;

      void BeginFrame() override;
      void EndFrame() override;

      void Resize(uint32_t w, uint32_t h) override;

      // void DrawMesh() override;

   private:
      const std::string m_gameName;
   };
}

#endif