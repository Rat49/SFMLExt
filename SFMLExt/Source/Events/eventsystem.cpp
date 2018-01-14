#include <Events\eventsystem.h>

void EventSystem::addHandler(sf::Uint32 id, EventCallback cb)
{
	(*this)[id].addHandler(cb);
}

void EventSystem::removeHandler(sf::Uint32 id, EventCallback cb)
{
	(*this)[id].removeHandler(cb);
}

void EventSystem::raise(sf::Uint32 id, std::any&& data)
{
	(*this)[id].raise(std::forward<std::any>(data));
}

void EventSystem::post(sf::Uint32 id, std::any&& data)
{
	(*this)[id].post(std::forward<std::any>(data));
}

void EventSystem::schedule(sf::Uint32 id, sf::Uint32 msBeforeStart, std::any&& data)
{
	m_postponed.emplace_back(id, msBeforeStart, std::forward<std::any>(data));
}

std::any EventSystem::take(sf::Uint32 id)
{
	return (*this)[id].take();
}

EventHandler& EventSystem::operator[](sf::Uint32 id)
{
	auto it = m_handlers.find(id);
	if (it == m_handlers.end())
	{
		it = m_handlers.try_emplace(it, id, EventHandler(id));
	}

	return it->second;
}

void EventSystem::update(sf::Window* wnd)
{
	sf::Uint32 deltaTime = m_lastUpdate.restart().asMilliseconds();

	auto it = m_postponed.begin();
	while (it != m_postponed.end())
	{
		it->m_msLeft -= std::min(deltaTime, it->m_msLeft);
		if (it->m_msLeft != 0)
		{
			++it;
			continue;
		}

		raise(it->m_id, std::move(it->m_data));
		it = m_postponed.erase(it);
	}

	if (wnd == nullptr)
	{
		return;
	}

	sf::Event ev;
	while (wnd->pollEvent(ev))
	{
		post(EventID::WindowEvents, std::move(ev));
	}
}

EventSystem::PostponedEvent::PostponedEvent(sf::Uint32 id, sf::Uint32 ms, std::any&& data)
	: m_id(id)
	, m_msLeft(ms)
	, m_data(data)
{
}
