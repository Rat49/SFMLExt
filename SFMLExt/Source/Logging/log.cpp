#include <Logging\log.h>
#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <iostream>


#ifdef SFMLEXT_LOG
namespace
{
	constexpr sf::Uint32 MaxBufferSize = { 1024 };

	char g_logBuffer[MaxBufferSize];
	std::ofstream g_logFile;
	LoggerSettings g_currentSettings;

	const char* getLevelStr(sf::Uint32 level)
	{
		switch (level)
		{
		case LoggerLevel::Info:			return "INF";
		case LoggerLevel::Warning:		return "WRN";
		case LoggerLevel::Error:		return "ERR";
		case LoggerLevel::Exception:	return "EXC";
		case LoggerLevel::Verbose:		return "VRB";
		default:						return "UND";
		}
	}
}

void Logger::setup(const LoggerSettings& settings)
{
	if (g_logFile.is_open())
	{
		g_logFile.close();
	}

	if (settings.LogToFile)
	{
		g_logFile.open(settings.PathToLog.toAnsiString(), std::ios::app | std::ios::out);
	}

	g_currentSettings = settings;
}

void Logger::log(sf::Uint32 level, const char* category, const char* file, sf::Uint32 line, const char* message, ...)
{
	if ((g_currentSettings.LogLevel & level) == 0) //wrong level. exit.
	{
		return;
	}

	if (!g_currentSettings.LogToFile && !g_currentSettings.LogToConsole) //nowhere to log. exit.
	{
		return;
	}

	int currentPos = { 0 };

	if (g_currentSettings.LogTimestamp)
	{
		auto globalNow = time(nullptr);
		tm now;
		localtime_s(&now, &globalNow);
		currentPos += snprintf(&g_logBuffer[currentPos], MaxBufferSize - currentPos, "[%04d-%02d-%02d %02d:%02d:%02d] ", 
			now.tm_year + 1900, now.tm_mon + 1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);
	}

	currentPos += snprintf(&g_logBuffer[currentPos], MaxBufferSize - currentPos, "%s(%s): ", category, getLevelStr(level));

	va_list args;
	va_start(args, message);
	currentPos += vsnprintf(&g_logBuffer[currentPos], MaxBufferSize - currentPos, message, args);
	va_end(args);

	if (g_currentSettings.LogFileline)
	{
		currentPos += snprintf(&g_logBuffer[currentPos], MaxBufferSize - currentPos, " [%s:%d]", file, line);
	}

	currentPos += snprintf(&g_logBuffer[currentPos], MaxBufferSize - currentPos, "\n");

	if (g_currentSettings.LogToConsole)
	{
		std::cout.write(g_logBuffer, currentPos);
	}
	if (g_currentSettings.LogToFile)
	{
		g_logFile.write(g_logBuffer, currentPos);
	}
}

#endif//SFMLEXT_LOG
