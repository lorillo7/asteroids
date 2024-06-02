#include "../headers/AsteroidManager.hpp"
#include <random>
#include <cstdlib>
#include <ctime>
#include <vector>

namespace gbl {
	extern float dt;
}

AsteroidManager::AsteroidManager(const Ship& i_ship) {
	std::srand(std::time(0));

	std::random_device rd;
	std::mt19937_64 eng(rd());
	std::uniform_int_distribution<int> X_dist(0, consts::WINDOW_WIDTH);
	std::uniform_int_distribution<int> Y_dist(0, consts::WINDOW_HEIGHT);
	std::uniform_int_distribution<int> velocityDist(-30, 30);

	for (int i = 15; i; --i) {

		sf::Vector2f newPos{0.f, 0.f};
		do {
			newPos = {static_cast<float>(X_dist(eng)), static_cast<float>(Y_dist(eng))};
		} while (Entity::pitagora2(newPos, i_ship.getPosition()) < 150);		// asteroids shouldn't spawn too close to the ship

		Asteroid newAstr(
			newPos,
			{static_cast<float>(velocityDist(eng)), static_cast<float>(velocityDist(eng))},
			static_cast<unsigned char>(std::rand() % 3)
		);

		m_asteroidList.push_back(newAstr);
	}
}

void AsteroidManager::update(const Ship& i_ship) {
	
	std::vector<std::list<Asteroid>::iterator> explodingAsteroids;

	for (auto i = m_asteroidList.begin(); i != m_asteroidList.end(); ++i) {
		i->update();
		i->checkHits(*i_ship.getBulletListPtr());
		i->checkShipCollision(i_ship);

		if (i->checkExplosion())
			explodingAsteroids.push_back(i);
	}

	for (auto& i : explodingAsteroids)
		i->explode(m_asteroidList);

	m_asteroidList.remove_if(
		[](const Asteroid& a) {
			return a.checkExplosion();
		}
	);
}

void AsteroidManager::render(sf::RenderWindow& i_window) const {
	for (const Asteroid& a : m_asteroidList)
		a.render(i_window);
}
