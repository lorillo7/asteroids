#pragma once

#include "./Bullet.hpp"
#include <list>

class Ship : public Entity {
public:
	explicit Ship() : Entity() {}

	Ship(const sf::Vector2f& i_pos, const sf::Vector2f& i_vec);

	virtual void update() override;

	virtual void render(sf::RenderWindow& i_window) const override;

	bool hasDied() const;

	void setState(bool i_value) const;

	const std::list<Bullet>* getBulletListPtr() const;

	u64 getScore() const;

private:
	std::list<Bullet> m_bulletList;
	mutable bool m_isAlive;
	sf::Clock m_clock;
	u64 m_score;
	sf::Sound m_shootSound;
};