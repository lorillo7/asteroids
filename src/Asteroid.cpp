#include "../headers/Asteroid.hpp"
#include <list>
#include <cstdlib>
#include <ctime>

namespace gbl {
	extern float dt;
}

Asteroid::Asteroid(const sf::Vector2f& i_pos, const sf::Vector2f& i_vec, unsigned char i_type) :
	Entity(
		i_pos,
		i_vec,
		Entity::Type::Asteroid,
		i_type
	),
	m_hasExploded(false),
	m_asteroidType(i_type)
	{
		if (m_asteroidType >= 6)
			m_value = values::smallAsteroid;
		else if (m_asteroidType < 6 && m_asteroidType >= 3)
			m_value = values::mediumAsteroid;
		else
			m_value = values::bigAsteroid;
	}

void Asteroid::explode(std::list<Asteroid>& i_list) {
	std::srand(std::time(0));

	if (m_asteroidType >= 6)
		return;
	
	for (int i = std::rand() % 3 + 2; i; --i) {
		Asteroid newAstr(
			getPosition(),
			{ getVelocity().x + std::rand() % 100 - 50, getVelocity().y + std::rand() % 100 - 50 },
			static_cast<unsigned char>(m_asteroidType + 3)
		);
		i_list.emplace_back(newAstr);
	}
}

void Asteroid::update() {
	m_sprite.move({
		m_velocity.x * gbl::dt,
		m_velocity.y * gbl::dt
	});

	sf::Vector2f pos = getPosition();
	sf::Vector2u size = m_sprite.getTexture()->getSize();

	if (pos.x - size.x >= consts::WINDOW_WIDTH)
		m_sprite.setPosition(pos.x - consts::WINDOW_WIDTH - size.x * 2, pos.y);
	else if (pos.x + size.x<= 0)
		m_sprite.setPosition(consts::WINDOW_WIDTH + pos.x + size.x * 2, pos.y);

	pos = getPosition();

	if (pos.y - size.y >= consts::WINDOW_HEIGHT)
		m_sprite.setPosition(pos.x, pos.y - consts::WINDOW_HEIGHT - size.y * 2);
	else if (pos.y + size.y <= 0)
		m_sprite.setPosition(pos.x, consts::WINDOW_HEIGHT + pos.y + size.y * 2);
}

void Asteroid::checkHits(const std::list<Bullet>& i_list) const {
	for (const Bullet& b : i_list)
		if (isColliding(b) && !b.wasUsed()) {
			m_hasExploded = true;
			b.use(m_value);
			return;
		}
}

void Asteroid::checkShipCollision(const Ship& i_ship) const {
	if (i_ship.isColliding(*this))
		i_ship.setState(false);
}

bool Asteroid::checkExplosion() const { return m_hasExploded; }

u16 Asteroid::getValue() const { return m_value; }