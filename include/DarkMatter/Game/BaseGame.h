#ifndef _DM_BASE_GAME_H_INCLUDED_
#define _DM_BASE_GAME_H_INCLUDED_

#include <DarkMatter/definitions.h>
#include <DarkMatter/Game/Window.h>

namespace DarkMatter::Game
{
   class DM_API BaseGame
   {
      bool m_isRunning = true;
      
      Window m_window;
   public:
      BaseGame();
      virtual ~BaseGame();

      void run();
   };
}

#endif