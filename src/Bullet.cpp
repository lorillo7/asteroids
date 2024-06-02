#include "../headers/Bullet.hpp"

namespace gbl {
	extern float dt;
}

Bullet::Bullet(const sf::Vector2f& i_pos, const sf::Vector2f& i_shooterVelocity, float i_angle) : 
	Entity (
		i_pos, {
			consts::BULLET_VELOCITY * std::cos(degToRad(i_angle - 90)) + i_shooterVelocity.x,
			consts::BULLET_VELOCITY * std::sin(degToRad(i_angle - 90)) + i_shooterVelocity.y
		},
		Entity::Type::Bullet
	),
	m_distanceTravelled(0.f, 0.f),
	m_wasUsed(false) {
		m_sprite.setRotation(i_angle);
	}

void Bullet::update() {
	m_sprite.move({
		m_velocity.x * gbl::dt,
		m_velocity.y * gbl::dt
	});

	m_distanceTravelled += {
		std::abs(m_velocity.x * gbl::dt),
		std::abs(m_velocity.y * gbl::dt)
	};

	sf::Vector2f pos = getPosition();

	if (pos.x >= consts::WINDOW_WIDTH)
		m_sprite.setPosition(pos.x - consts::WINDOW_WIDTH, pos.y);
	else if (pos.x <= 0)
		m_sprite.setPosition(consts::WINDOW_WIDTH + pos.x, pos.y);

	pos = getPosition();

	if (pos.y >= consts::WINDOW_HEIGHT)
		m_sprite.setPosition(pos.x, pos.y - consts::WINDOW_HEIGHT);
	else if (pos.y <= 0)
		m_sprite.setPosition(pos.x, consts::WINDOW_HEIGHT + pos.y);

}

void Bullet::render(sf::RenderWindow& i_window) const {
	i_window.draw(m_sprite);
}

float Bullet::getTravelledDistance() const {
	return std::sqrt(m_distanceTravelled.x * m_distanceTravelled.x + m_distanceTravelled.y * m_distanceTravelled.y);
}

bool Bullet::wasUsed() const { return m_wasUsed; }

void Bullet::use(unsigned short int i_value) const {
	m_wasUsed = true;
	m_hitValue = i_value;
}

u32 Bullet::getHitValue() const { return m_hitValue; }