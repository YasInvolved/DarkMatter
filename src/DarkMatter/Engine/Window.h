#ifndef _DM_WINDOW_H_INCLUDED_
#define _DM_WINDOW_H_INCLUDED_

#include <SDL3/SDL.h>
#include <DarkMatter/Events/Event.h>

namespace DarkMatter
{
   class Window
   {
   public:
      using EventCallback = std::function<void(const DarkMatter::Events::Event& e)>;

      Window(const std::string& title);
      ~Window();

      Window(const Window&) = delete;
      Window& operator=(const Window&) = delete;

      bool initialize();
      
      void handleEvents();

      void setEventCallback(EventCallback cb);

      SDL_Window* const GetHandle() const { assert(m_window != nullptr); return m_window; }
   private:
      std::string m_title;
      SDL_Window* m_window;

      EventCallback m_callback;

      static bool TranslateSDLEvent(const SDL_Event& sdlEvent, Events::Event& outEvent);
   };
}

#endif