#pragma once

#include "./Entity.hpp"

class Bullet : public Entity {
public:
	explicit Bullet() = default;
	virtual ~Bullet() = default;
	
	Bullet(const sf::Vector2f& i_pos, const sf::Vector2f& i_shooterVelocity, float i_angle);

	virtual void update() override;

	virtual void render(sf::RenderWindow& i_window) const override;

	float getTravelledDistance() const;

	bool wasUsed() const;

	void use(unsigned short int i_value) const;

	unsigned int getHitValue() const;

private:
	mutable bool m_wasUsed;
	mutable unsigned short int m_hitValue;
	sf::Vector2f m_distanceTravelled;
};