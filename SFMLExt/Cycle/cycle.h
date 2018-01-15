#pragma once

#include <SFML\Graphics.hpp>

class Cycle final
{
public:
	void addDrawable();
	void removeDrawable();

	void setView(const sf::View& view);
	const sf::View& getView() const;

private:
	std::vector<sf::Drawable> m_subscribers;
	sf::RenderWindow m_window;
};