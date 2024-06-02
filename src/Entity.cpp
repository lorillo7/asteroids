#include "../headers/Entity.hpp"

namespace gbl {
	extern TextureManager textureManager;
	extern ErrorManager ERRORS;
}

Entity::Entity(const sf::Vector2f& i_pos, const sf::Vector2f& i_vec, Type i_type, unsigned char i_asteroidType) : type(i_type), m_velocity(i_vec) {
	using namespace std::string_literals;

	switch (type) {
	case Type::Bullet:
		if (i_asteroidType != 255)
			gbl::ERRORS.addError("Entity created is not an asteroid but size was still given ("s + std::to_string(i_asteroidType) + '\'');
		m_sprite.setTexture(gbl::textureManager.getBulletTexture());
		break;
	case Type::Ship:
		m_sprite.setTexture(gbl::textureManager.getShipTexture());
		break;
	case Type::Asteroid:
		if (i_asteroidType == 255)
			gbl::ERRORS.addError("Attempted asteroid creation but no size was given");
		m_sprite.setTexture(gbl::textureManager.getAsteroidTexture(i_asteroidType));
		break;
	}

	sf::Vector2u size = m_sprite.getTexture()->getSize();
	m_sprite.setOrigin({static_cast<float>(size.x) / 2.f,
						static_cast<float>(size.y) / 2.f});
	m_sprite.setPosition(i_pos);
}

const sf::Vector2f& Entity::getVelocity() const { return m_velocity; }

const sf::Vector2f& Entity::getPosition() const { 
	return m_sprite.getPosition();
}

void Entity::render(sf::RenderWindow& i_window) const {
	i_window.draw(m_sprite);
}

float Entity::degToRad(float deg) {
	return deg * (consts::PI / 180);
}

float Entity::getModuloVelocity() {
	return pitagora1(m_velocity);
}

bool Entity::isColliding(const Entity& obj) const {
	return m_sprite.getGlobalBounds().intersects(obj.m_sprite.getGlobalBounds());
}

bool Entity::checkIntersection(const sf::Vector2f& i_pos) const {
	return m_sprite.getGlobalBounds().contains(i_pos);
}

float Entity::pitagora1(const sf::Vector2f& v) {
	return std::sqrt(v.x * v.x + v.y * v.y);
}

float Entity::pitagora2(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	float dtX = v1.x - v2.x,
		  dtY = v1.y - v2.y;
	return std::sqrt(dtX * dtX + dtY * dtY);
}