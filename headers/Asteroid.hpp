#pragma once

#include "./Ship.hpp"
#include <list>

class Asteroid : public Entity {
public:
	explicit Asteroid() = default;

	Asteroid(const sf::Vector2f& i_pos, const sf::Vector2f& i_vec, unsigned char i_type);
	
	virtual ~Asteroid() = default;

	virtual void update() override;

	void checkHits(const std::list<Bullet>& i_list) const;

	void checkShipCollision(const Ship& i_ship) const;

	void explode(std::list<Asteroid>& i_list);

	bool checkExplosion() const;

	u16 getValue() const;

private:
	mutable bool m_hasExploded;
	unsigned char m_asteroidType;
	unsigned short int m_value;
};