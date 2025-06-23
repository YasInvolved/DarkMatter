#ifndef _DM_WINDOW_H_INCLUDED_
#define _DM_WINDOW_H_INCLUDED_

namespace DarkMatter::Game
{
   class BaseGame;

   class Window
   {
      void* m_handle;
   public:
      Window();
      ~Window();
   };
}

#endif