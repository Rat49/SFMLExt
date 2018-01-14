#pragma once

#include <SFML\Graphics.hpp>

class Cycle final
{
public:
	void addDrawable();
	void removeDrawable();

private:
	std::vector<sf::Drawable> m_subscribers;
	

};