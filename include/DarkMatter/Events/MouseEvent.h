#ifndef _DM_MOUSE_EVENT_H_INCLUDED_
#define _DM_MOUSE_EVENT_H_INCLUDED_

#include <stdint.h>

namespace DarkMatter::Events
{
   // TODO: Map mouse buttons

   struct MouseEvent
   {
      uint32_t x, y;
      int button;
   };
}

#endif