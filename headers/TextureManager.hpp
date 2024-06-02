#pragma once

#include "../headers/vals.hpp"
#include "../headers/ErrorManager.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <array>

class TextureManager {
public:
	explicit TextureManager() = default;
	void load();
	const sf::Texture& getShipTexture() const;
	const sf::Texture& getAsteroidTexture(unsigned char idx) const;
	const sf::Texture& getBulletTexture() const;
	const sf::Font& getFont() const;
	const sf::SoundBuffer& getShootSoundBuffer() const;

private:
	std::array<sf::Texture, 9> m_asteroidTextures;
	sf::Texture m_shipTexture,
				m_bulletTexture;
	sf::Font m_font;
	sf::SoundBuffer m_shootSoundBuffer;
};