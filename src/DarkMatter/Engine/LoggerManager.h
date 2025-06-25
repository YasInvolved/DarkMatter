#ifndef _DM_LOGGER_MANAGER_H_INCLUDED_
#define _DM_LOGGER_MANAGER_H_INCLUDED_

#include <DarkMatter/ILoggerManager.h>

namespace DarkMatter
{
   class LoggerManager : public ILoggerManager
   {
   public:
      LoggerManager();
      ~LoggerManager();

      spdlog::logger& getLoggerByName(const std::string& name) const override;
      spdlog::logger& getSystemLogger() const;
   private:
      std::unique_ptr<spdlog::logger> m_systemLogger;

      std::shared_ptr<spdlog::sinks::basic_file_sink_mt> m_fileSink;
      std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> m_consoleSink;

      mutable std::unordered_map<std::string, std::unique_ptr<spdlog::logger>> m_loggers; // mutation is justified because it's 100% internal
   };
}

#endif