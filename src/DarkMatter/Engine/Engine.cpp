#include <DarkMatter/Engine/Engine.h>
#include <DarkMatter/Renderer/RendererBuilder.h>

#include <DarkMatter/Embedded/basic_glsl_vert_glsl.h>

using Engine = DarkMatter::Engine;

Engine::Engine()
   : m_game(nullptr), 
   m_window(nullptr), 
   m_loggerManager(std::make_unique<LoggerManager>())
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
      .build(*this);
   
   if (!m_renderer->Init())
      return false;

   m_loggerManager->getSystemLogger().info("Embedded resource length: {}", Embedded::basic_glsl_vert_glsl_len);

   return m_game->onInitialize(*this);
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
   m_renderer->Shutdown();
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

const DarkMatter::ILoggerManager& Engine::getLoggerManager() const
{
   return *m_loggerManager;
}

DarkMatter::IEngine* CreateEngine()
{
   return new DarkMatter::Engine;
}

void DestroyEngine(DarkMatter::IEngine* engine)
{
   delete engine;
}