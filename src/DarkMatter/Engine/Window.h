#ifndef _DM_WINDOW_H_INCLUDED_
#define _DM_WINDOW_H_INCLUDED_

#include <SDL3/SDL.h>

namespace DarkMatter
{
   class Window
   {
   public:
      Window(const std::string& title);
      ~Window();

      bool initialize();
      
      // returns false if game should exit
      void handleEvents();
   private:
      std::string m_title;
      SDL_Window* m_window;
   };
}

#endif