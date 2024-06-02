#pragma once

#include "./TextureManager.hpp"
#include <cmath>
#include <iostream>
#include "./typedefs.hpp"

class Entity {
public:
	enum class Type {
		Ship, Asteroid, Bullet
	};

	explicit Entity() = default;

	Entity(const sf::Vector2f& i_pos, const sf::Vector2f& i_vec, Type i_type, unsigned char i_asteroidType = -1);
	
	const sf::Vector2f& getVelocity() const;
	
	const sf::Vector2f& getPosition() const;
	
	float getModuloVelocity();
	
	bool isColliding(const Entity& obj) const;
	
	bool checkIntersection(const sf::Vector2f& i_pos) const;
	
	virtual void render(sf::RenderWindow& i_window) const;
	
	virtual void update() = 0;
	
	virtual ~Entity() = default;

	static float pitagora1(const sf::Vector2f& v1);
	static float pitagora2(const sf::Vector2f& v1, const sf::Vector2f& v2);

	Type type;

protected:
	sf::Sprite m_sprite;
	sf::Vector2f m_velocity;

	static float degToRad(float deg);

	template <typename T>
	static signed char sign(const T n) {
		if (n)
			return (n > 0) ? 1 : 0-1;
		return 0;
	}
};