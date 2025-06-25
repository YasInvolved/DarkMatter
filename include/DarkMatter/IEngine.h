#ifndef _DM_IENGINE_H_INCLUDED_
#define _DM_IENGINE_H_INCLUDED_

#include <DarkMatter/ExportAPI.h>
#include <DarkMatter/IGame.h>
#include <DarkMatter/ILoggerManager.h>

#include <memory>

namespace DarkMatter
{
   class IEngine
   {
   public:
      virtual ~IEngine() = default;

      virtual void setGame(std::unique_ptr<IGame> game) = 0;

      virtual bool initialize() = 0;
      virtual void run() = 0;
      virtual void shutdown() = 0;

      virtual const ILoggerManager& getLoggerManager() const = 0;
   };
}

DM_API DarkMatter::IEngine* CreateEngine();
DM_API void DestroyEngine(DarkMatter::IEngine* engine);

#endif