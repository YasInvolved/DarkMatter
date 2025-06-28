#ifndef _DM_ENGINE_H_INCLUDED_
#define _DM_ENGINE_H_INCLUDED_

#include <DarkMatter/IEngine.h>
#include <DarkMatter/Engine/Window.h>
#include <DarkMatter/Engine/LoggerManager.h>
#include <DarkMatter/Engine/ThreadPool.h>
#include <DarkMatter/Renderer/IRenderer.h>

namespace DarkMatter
{
   class Engine : public IEngine
   {
   public:
      Engine();
      ~Engine() override;

      void setGame(std::unique_ptr<IGame> game) override;
      
      bool initialize() override;
      void run() override;
      void shutdown() override;

      const ILoggerManager& getLoggerManager() const override;
      const Window& getWindow() const { return *m_window; }
      ThreadPool& getThreadPool() const { return *m_threadPool; }

      void update();
      void render();

   private:
      bool m_running = true;

      std::unique_ptr<LoggerManager> m_loggerManager;

      std::unique_ptr<IGame> m_game;
      std::unique_ptr<Window> m_window;
      std::unique_ptr<IRenderer> m_renderer;
      std::unique_ptr<ThreadPool> m_threadPool;
   };
}

#endif