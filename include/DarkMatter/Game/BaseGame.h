#ifndef _DM_BASE_GAME_H_INCLUDED_
#define _DM_BASE_GAME_H_INCLUDED_

#include <DarkMatter/definitions.h>

namespace DarkMatter::Game
{
   class DM_API BaseGame
   {
   public:
      BaseGame();
      virtual ~BaseGame();

      void run();
   };
}

#endif