#ifndef _DM_ENGINE_H_INCLUDED_
#define _DM_ENGINE_H_INCLUDED_

#include <DarkMatter/IEngine.h>
#include <DarkMatter/Engine/Window.h>

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

      // forward to window
      void registerEventCallback(EventCallback cb) override;

      void update();
      void render();
   private:
      bool m_running = true;

      std::unique_ptr<IGame> m_game;
      std::unique_ptr<Window> m_window;
   };
}

#endif