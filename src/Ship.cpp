#include "../headers/Ship.hpp"
#include <cstdlib>
#include <ctime>

namespace gbl {
	extern float dt;
	extern TextureManager textureManager;
}

Ship::Ship(const sf::Vector2f& i_pos, const sf::Vector2f& i_vec) :
	Entity(i_pos, i_vec, Entity::Type::Ship),
	m_isAlive(true),
	m_score(0),
	m_shootSound(gbl::textureManager.getShootSoundBuffer()),
	m_clock()
{}

void Ship::update() {
	// keyboard input
	std::srand(std::time(nullptr));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_sprite.rotate(0 - consts::SHIP_DELTA_ANGLE * gbl::dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_sprite.rotate(consts::SHIP_DELTA_ANGLE * gbl::dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_velocity += {
			consts::SHIP_ACCELERATION * std::cos(degToRad(m_sprite.getRotation() - 90)),
			consts::SHIP_ACCELERATION * std::sin(degToRad(m_sprite.getRotation() - 90))
		};
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_clock.getElapsedTime().asSeconds() >= consts::reloadTime.asSeconds()) {
		m_bulletList.emplace_back(getPosition(), getVelocity(), m_sprite.getRotation());
		m_shootSound.setPitch(
			static_cast<float>(std::rand() % 10 * 5 + 50) / 100.f
		);
		m_shootSound.play();
		m_clock.restart();
	}

	// velocity is too high
	m_velocity = {
		std::abs(m_velocity.x) > consts::MAX_SHIP_VELOCITY ? sign(m_velocity.x) * consts::MAX_SHIP_VELOCITY : m_velocity.x,
		std::abs(m_velocity.y) > consts::MAX_SHIP_VELOCITY ? sign(m_velocity.y) * consts::MAX_SHIP_VELOCITY : m_velocity.y,
	};

	// velocity is too low
	m_velocity = {
		std::abs(m_velocity.x) <= 0.001f ? 0 : m_velocity.x + (consts::SHIP_DECELERATION * sign(m_velocity.x) * gbl::dt),
		std::abs(m_velocity.y) <= 0.001f ? 0 : m_velocity.y + (consts::SHIP_DECELERATION * sign(m_velocity.y) * gbl::dt),
	};

	// move sprite
	m_sprite.move({
		m_velocity.x * gbl::dt,
		m_velocity.y * gbl::dt
	});

	// screen wrapping
	sf::Vector2f pos = m_sprite.getPosition();
	
	if (pos.x >= consts::WINDOW_WIDTH)
		m_sprite.setPosition(pos.x - consts::WINDOW_WIDTH, pos.y);
	else if (pos.x <= 0)
		m_sprite.setPosition(consts::WINDOW_WIDTH + pos.x, pos.y);

	if (pos.y >= consts::WINDOW_HEIGHT)
		m_sprite.setPosition(pos.x, pos.y - consts::WINDOW_HEIGHT);
	else if (pos.y <= 0)
		m_sprite.setPosition(pos.x, consts::WINDOW_HEIGHT + pos.y);

	for (Bullet& e : m_bulletList)
		e.update();

	// remove used bullets
	m_bulletList.remove_if([this](const Bullet& b) {
		const sf::Vector2f p = b.getPosition();
		
		if (b.getTravelledDistance() >= consts::MAX_BULLET_DISTANCE)
			return true;
		
		if (b.wasUsed()) {
			this->m_score += b.getHitValue();
			return true;
		}
		return false;
	});
}

void Ship::render(sf::RenderWindow& i_window) const {
	i_window.draw(m_sprite);
	for (const Bullet& e : m_bulletList)
		e.render(i_window);
}

bool Ship::hasDied() const { return !m_isAlive; }

void Ship::setState(bool i_value) const { m_isAlive = i_value; }

const std::list<Bullet>* Ship::getBulletListPtr() const { return &m_bulletList; }

u64 Ship::getScore() const { return m_score; }
