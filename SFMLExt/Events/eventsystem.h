#pragma once
#include <map>
#include "eventhandler.h"
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

class EventSystem final
{
public:
	void addHandler(sf::Uint32 id, EventCallback cb);
	void removeHandler(sf::Uint32 id, EventCallback cb);

	void raise(sf::Uint32 id, std::any&& data);
	void post(sf::Uint32 id, std::any&& data);
	void schedule(sf::Uint32 id, sf::Uint32 msBeforeStart, std::any&& data);

	std::any take(sf::Uint32 id);

	EventHandler& operator[](sf::Uint32 id);

	void update(sf::Window* wnd = nullptr);

private:
	struct PostponedEvent
	{
		PostponedEvent(sf::Uint32 id, sf::Uint32 ms, std::any&& data);

		sf::Uint32 m_id;
		sf::Uint32 m_msLeft;
		std::any m_data;
	};

	sf::Clock m_lastUpdate;
	std::map<sf::Uint32, EventHandler> m_handlers;
	std::vector<PostponedEvent> m_postponed;
};
 