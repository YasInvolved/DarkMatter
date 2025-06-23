#ifndef _DM_IGAME_H_INCLUDED_
#define _DM_IGAME_H_INCLUDED_

#include <string>

namespace DarkMatter
{
   class IGame
   {
   public:
      virtual ~IGame() = default;

      virtual bool onInitialize() = 0;
      virtual void onShutdown() = 0;
      virtual void onUpdate() = 0;
      virtual void onRender() = 0;

      virtual std::string getTitle() const = 0;
   };
}

#endif