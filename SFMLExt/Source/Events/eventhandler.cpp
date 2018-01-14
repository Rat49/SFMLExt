#include <Events\eventhandler.h>

void EventHandler::addHandler(EventCallback cb)
{
	m_callbacks.insert(cb);
}

void EventHandler::removeHandler(EventCallback cb)
{
	m_callbacks.erase(cb);
}

void EventHandler::raise(std::any&& data)
{
	for (const auto& cb : m_callbacks)
	{
		cb(m_id, data);
	}
}

void EventHandler::post(std::any&& data)
{
	m_data.emplace(std::forward<std::any>(data));
}

std::any EventHandler::take()
{
	std::any result;
	if (!m_data.empty())
	{
		result = m_data.front();
		m_data.pop();
	}
	return result;
}
