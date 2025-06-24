#include <DarkMatter/Renderer/Renderer.h>

using Renderer = DarkMatter::Renderer::Renderer;
using IRenderer = DarkMatter::Renderer::IRenderer;

std::unique_ptr<IRenderer> Renderer::s_internalRenderer;

bool Renderer::Init(const DarkMatter::Renderer::RendererCreateInfo& info)
{
   if (info.api == DarkMatter::Renderer::RendererAPI::VULKAN)
      s_internalRenderer = std::make_unique<VulkanRenderer>();
   else
      return false; // unsupported API

   return true;
}

void Renderer::Shutdown()
{
   s_internalRenderer->Shutdown();
}

void Renderer::BeginFrame()
{
   s_internalRenderer->BeginFrame();
}

void Renderer::EndFrame()
{
   s_internalRenderer->EndFrame();
}