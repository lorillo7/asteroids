#include "../headers/vals.hpp"
#include "../headers/TextureManager.hpp"

#include <string>
#include <iostream>
#include <cstdlib>

namespace gbl {
	extern ErrorManager ERRORS;
	extern std::string path;
}

void TextureManager::load() {
	static int callCount = 0;
	++callCount;
	if (callCount != 1)	{
		gbl::ERRORS.addError("Texture loaded twice!");
		gbl::ERRORS.print();
		std:exit(EXIT_FAILURE);
	}

	if (gbl::path.empty()) {
		gbl::ERRORS.addError("Path variable is empty!");
		return;
	}

	std::string shipPath{gbl::path + sprites::ship},
				bigAsteroidsPath{gbl::path + sprites::bigAsteroids},
				mediumAsteroidsPath{gbl::path + sprites::mediumAsteroids},
				smallAsteroidsPath{gbl::path + sprites::smallAsteroids},
				bulletPath{gbl::path + sprites::bullet},
				fontPath{gbl::path + font::font},
				shootSoundPath{gbl::path + audio::shootPath};
	
	using namespace std::string_literals;

	if (!m_shipTexture.loadFromFile(shipPath))
		gbl::ERRORS.addError("Failed to load texture from '"s + shipPath + '\'');

	int i = 0;

	// load big asteroids
	sf::IntRect itrRect(0, 0, sprites::BIG_SIZE, sprites::BIG_SIZE);
	do {
		if (!m_asteroidTextures.at(i).loadFromFile(bigAsteroidsPath, itrRect))
			gbl::ERRORS.addError("Failed to load texture from '"s + bigAsteroidsPath + '\'');
		itrRect.left += sprites::BIG_SIZE;
		++i;
	} while (itrRect.left <= 2 * sprites::BIG_SIZE);

	// load medium asteroids
	itrRect.top = 0;
	itrRect.left = 0;
	itrRect.width = sprites::MEDIUM_SIZE;
	itrRect.height = sprites::MEDIUM_SIZE;

	do {
		if (!m_asteroidTextures.at(i).loadFromFile(mediumAsteroidsPath, itrRect))
			gbl::ERRORS.addError("Failed to load texture from '"s + mediumAsteroidsPath + '\'');
		itrRect.left += sprites::MEDIUM_SIZE;
		++i;
	} while (itrRect.left <= 2 * sprites::MEDIUM_SIZE);

	// load small asteroids
	itrRect.top = 0;
	itrRect.left = 0;
	itrRect.width = sprites::SMALL_SIZE;
	itrRect.height = sprites::SMALL_SIZE;

	do {
		if (!m_asteroidTextures.at(i).loadFromFile(smallAsteroidsPath, itrRect))
			gbl::ERRORS.addError("Failed to load texture from '"s + smallAsteroidsPath + '\'');
		itrRect.left += sprites::SMALL_SIZE;
		++i;
	} while (itrRect.left <= 2 * sprites::SMALL_SIZE);

	if (!m_bulletTexture.loadFromFile(bulletPath))
		gbl::ERRORS.addError("Failed to load texture from '"s + bulletPath + '\'');
	
	if (!m_font.loadFromFile(fontPath))
		gbl::ERRORS.addError("Failed to load font from '"s + fontPath + '\'');

	if (!m_shootSoundBuffer.loadFromFile(shootSoundPath))
		gbl::ERRORS.addError("Failed to load sound from \'"s + shootSoundPath + '\'');
}

const sf::Texture& TextureManager::getShipTexture() const {
	return m_shipTexture;
}

const sf::Texture& TextureManager::getAsteroidTexture(unsigned char idx) const {
	return m_asteroidTextures.at(idx);
}

const sf::Texture& TextureManager::getBulletTexture() const {
	return m_bulletTexture;
}

const sf::Font& TextureManager::getFont() const {
	return m_font;
}

const sf::SoundBuffer& TextureManager::getShootSoundBuffer() const {
	return m_shootSoundBuffer;
}