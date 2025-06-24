#ifndef _DM_EVENT_H_INCLUDED_
#define _DM_EVENT_H_INCLUDED_

#include <DarkMatter/Events/KeyEvent.h>
#include <DarkMatter/Events/MouseEvent.h>

namespace DarkMatter::Events
{
   enum class EventType
   {
      QUIT,
      KEY_DOWN, KEY_UP,
      MOUSE_MOVE, MOUSE_BTN_DOWN, MOUSE_BTN_UP,
      WINDOW_RESIZE
   };

   struct WindowResizeEvent
   {
      uint32_t w, h;
   };

   struct Event
   {
      EventType type;
      union
      {
         KeyEvent keyEvent;
         MouseEvent mouseEvent;
         WindowResizeEvent windowResizeEvent;
      };
   };
}

#endif