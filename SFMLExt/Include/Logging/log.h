#pragma once
#include <SFML\Config.hpp>
#include <SFML\System\String.hpp>

struct LoggerLevel
{
	static constexpr sf::Uint32 Info		= 0x01;
	static constexpr sf::Uint32 Warning		= Info | 0x02;
	static constexpr sf::Uint32 Error		= Info | Warning | 0x04;
	static constexpr sf::Uint32 Exception	= Info | Warning | Error | 0x08;
	static constexpr sf::Uint32 Verbose		= Info | Warning | Error | Exception | 0x10;
};

struct LoggerSettings
{
	sf::String PathToLog = { "./output.log" };

	bool LogToFile = { false };
	bool LogToConsole = { true };
	bool LogTimestamp = { true };
	bool LogFileline = { true };
	sf::Uint32 LogLevel = { LoggerLevel::Verbose };
};

#ifdef SFMLEXT_LOG
	class Logger final
	{
	public:
		static void setup(const LoggerSettings& settings);
		static void log(sf::Uint32 level, const char* category, const char* file, sf::Uint32 line, const char* message, ...);
	};

	#define LOGGER_SETUP(Settings)					Logger::setup(Settings)
	#define LOG_INFO(Category, Message, ...)		Logger::log(LoggerLevel::Info, Category, __FILE__, __LINE__, Message, __VA_ARGS__)
	#define LOG_WARNING(Category, Message, ...)		Logger::log(LoggerLevel::Warning, Category, __FILE__, __LINE__, Message, __VA_ARGS__)
	#define LOG_ERROR(Category, Message, ...)		Logger::log(LoggerLevel::Error, Category, __FILE__, __LINE__, Message, __VA_ARGS__)
	#define LOG_EXCEPTION(Category, Message, ...)	Logger::log(LoggerLevel::Exception, Category, __FILE__, __LINE__, Message, __VA_ARGS__)
#else
	#define LOGGER_SETUP(Settings)
	#define LOG_INFO(Category, Message, ...)
	#define LOG_WARNING(Category, Message, ...)
	#define LOG_ERROR(Category, Message, ...)
	#define LOG_EXCEPTION(Category, Message, ...)
#endif