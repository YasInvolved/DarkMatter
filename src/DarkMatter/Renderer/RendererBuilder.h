#ifndef _DM_RENDERER_FACTORY_H_INCLUDED_
#define _DM_RENDERER_FACTORY_H_INCLUDED_

#include <DarkMatter/Renderer/IRenderer.h>
#include <DarkMatter/Engine/Engine.h>

namespace DarkMatter
{
   enum class RendererAPI
   {
      VULKAN
   };

   class RendererBuilder
   {
   public:
      RendererBuilder() = default;
      ~RendererBuilder() = default;

      RendererBuilder& setAPI(RendererAPI api) { m_api = api; return *this; }
      RendererBuilder& setApplicationName(const std::string_view name) { m_appName = name; return *this; }
      std::unique_ptr<IRenderer> build(const Engine& engine) const;

   private:
      std::optional<RendererAPI> m_api;
      std::string_view m_appName;
   };
}

#endif