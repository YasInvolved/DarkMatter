#include <DarkMatter/Renderer/RendererBuilder.h>
#include <DarkMatter/Renderer/VulkanRenderer.h>

using RendererBuilder = DarkMatter::RendererBuilder;

std::unique_ptr<DarkMatter::IRenderer> RendererBuilder::build(const Engine& engine) const
{
   return std::make_unique<VulkanRenderer>(engine, m_appName);
}