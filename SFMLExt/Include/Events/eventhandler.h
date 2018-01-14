#pragma once
#include <any>
#include <set>
#include <queue>
#include <SFML\Config.hpp>

struct EventID
{
	static constexpr sf::Uint32 WindowEvents = { 0 };
	static constexpr sf::Uint32 UserEvents = { 1000 };
};

using EventCallback = void(*)(sf::Uint32, const std::any&);

class EventHandler final
{
public:
	explicit EventHandler(sf::Uint32 id) : m_id(id) {}
	sf::Uint32 getId() const { return m_id; }

	void addHandler(EventCallback cb);
	void removeHandler(EventCallback cb);
	void raise(std::any&& data);
	void post(std::any&& data);
	std::any take();

private:
	sf::Uint32 m_id;
	std::set<EventCallback> m_callbacks;
	std::queue<std::any> m_data;
};
