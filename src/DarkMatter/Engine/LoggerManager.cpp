#include <DarkMatter/Engine/LoggerManager.h>

using LoggerManager = DarkMatter::LoggerManager;

static constexpr const char* s_loggerPattern = "[DarkMatter-%n %T.%3e] [%=8l] %v";

LoggerManager::LoggerManager()
   : m_fileSink(std::make_shared<spdlog::sinks::basic_file_sink_mt>("log.txt", true)),
   m_consoleSink(std::make_shared<spdlog::sinks::stdout_color_sink_mt>())
{
   m_fileSink->set_pattern(s_loggerPattern);
   m_fileSink->set_level(spdlog::level::trace);

   m_consoleSink->set_pattern("%^" + std::string(s_loggerPattern) + "%$");
   m_consoleSink->set_level(spdlog::level::warn); // TODO: level dependent on build mode (Debug, Release...)

   m_systemLogger = std::make_unique<spdlog::logger>("system", spdlog::sinks_init_list{ m_fileSink, m_consoleSink });
}

LoggerManager::~LoggerManager()
{}

spdlog::logger& LoggerManager::getSystemLogger() const
{
   return *m_systemLogger;
}

spdlog::logger& LoggerManager::getLoggerByName(const std::string& name) const
{
   if (m_loggers.contains(name))
      return *m_loggers[name];
   
   m_loggers[name] = std::make_unique<spdlog::logger>(name, spdlog::sinks_init_list{ m_fileSink, m_consoleSink });
   return *m_loggers[name];
}