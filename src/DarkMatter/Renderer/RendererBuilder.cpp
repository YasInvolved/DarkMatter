#include <DarkMatter/Renderer/RendererBuilder.h>
#include <DarkMatter/Renderer/VulkanRenderer.h>

using RendererBuilder = DarkMatter::RendererBuilder;

std::unique_ptr<DarkMatter::IRenderer> RendererBuilder::build(const Engine& engine) const
{
   if (!m_api.has_value() || m_api.value() == RendererAPI::VULKAN)
   {
      assert(!m_appName.empty());
      return std::make_unique<VulkanRenderer>(engine, m_appName);
   }
}