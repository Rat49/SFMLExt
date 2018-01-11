#pragma once
#include <cstdint>
#include <any>

using EventCallback = void(*)(uint32_t, std::any&);

class EventHandler final
{

};

class EventManager final
{
public:
	void addEventHandler(uint32_t id, EventCallback cb);
	void removeEventHandler(uint32_t id, EventCallback cb);

	void raise(uint32_t id, std::any& data);
	void post(uint32_t id, std::any& data, uint32_t timeoutMs);
};