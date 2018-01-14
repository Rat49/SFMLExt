#include <Windows.h>
#include <Logging\log.h>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	LoggerSettings s;
	s.LogToConsole = false;
	s.LogToFile = true;

	LOGGER_SETUP(s);
	LOG_INFO("TEST", "Some log information");
	LOG_WARNING("TEST", "Some %s information %s", "special", "or maybe not");
	LOG_ERROR("TEST", "Other log information %d", 1024);
	return 0;
}