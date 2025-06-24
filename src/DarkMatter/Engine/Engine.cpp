#include <DarkMatter/Engine/Engine.h>
#include <DarkMatter/Renderer/Renderer.h>

using Engine = DarkMatter::Engine;

Engine::Engine()
   : m_game(nullptr), m_window(nullptr)
{}

Engine::~Engine() {}

void Engine::setGame(std::unique_ptr<IGame> game)
{
   m_game = std::move(game);
}

bool Engine::initialize()
{
   if (m_game.get() == nullptr)
      return false;

   m_window = std::make_unique<Window>(m_game->getTitle());
   m_window->initialize();
   m_window->setEventCallback([this](const DarkMatter::Events::Event& event)
      {
         // TODO: renderer resize callback and shit like that
         m_game->onEvent(event);

         if (event.type == Events::EventType::QUIT)
            m_running = false;
      }
   );

   using Renderer = DarkMatter::Renderer::Renderer;
   using RendererCreateInfo = DarkMatter::Renderer::RendererCreateInfo;

   const RendererCreateInfo rendererCreateInfo =
   {
      .api = DarkMatter::Renderer::RendererAPI::VULKAN,
      .window = *m_window
   };

   Renderer::Init(rendererCreateInfo);

   return m_game->onInitialize();
}

void Engine::run()
{
   while (m_running)
   {
      m_window->handleEvents();
      update();
      render();
   }
}

void Engine::shutdown()
{
   m_game->onShutdown();
}

void Engine::update()
{
   m_game->onUpdate();
}

void Engine::render()
{
   m_game->onRender();
}

DarkMatter::IEngine* CreateEngine()
{
   return new DarkMatter::Engine;
}

void DestroyEngine(DarkMatter::IEngine* engine)
{
   delete engine;
}