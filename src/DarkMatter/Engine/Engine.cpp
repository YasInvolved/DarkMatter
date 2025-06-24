#include <DarkMatter/Engine/Engine.h>
#include <DarkMatter/Renderer/RendererBuilder.h>

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

   m_renderer = RendererBuilder()
      .setAPI(DarkMatter::RendererAPI::VULKAN)
      .setApplicationName(m_game->getTitle())
      .build();

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