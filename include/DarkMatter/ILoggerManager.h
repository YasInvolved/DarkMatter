#ifndef _DM_ILOGGER_MANAGER_H_INCLUDED_
#define _DM_ILOGGER_MANAGER_H_INCLUDED_

#include <string>
#include <spdlog/spdlog.h>

namespace DarkMatter
{
   class ILoggerManager
   {
   public:
      virtual ~ILoggerManager() = default;

      virtual spdlog::logger& getLoggerByName(const std::string& name) const = 0;
;  };
}

#endif