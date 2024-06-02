#pragma once

#include "./Asteroid.hpp"
#include <list>

class AsteroidManager {
public:
	explicit AsteroidManager() = default;

	AsteroidManager(const Ship& i_ship);

	void update(const Ship& i_ship);

	void render(sf::RenderWindow& i_window) const;

private:
	std::list<Asteroid> m_asteroidList;
};