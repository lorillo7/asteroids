#pragma once

#include <SFML/System/Time.hpp>
#include "./typedefs.hpp"

namespace consts {
	inline constexpr int WINDOW_WIDTH = 1000;
	inline constexpr int WINDOW_HEIGHT = 800;

	inline constexpr float SHIP_ACCELERATION = 0.5f;
	inline constexpr float SHIP_DELTA_ANGLE = 200.f;
	inline constexpr float MAX_SHIP_VELOCITY = 400.f;
	inline constexpr float SHIP_DECELERATION = -15.f;

	inline constexpr int BULLET_WIDTH = 3;
	inline constexpr int BULLET_HEIGHT = 12;
	inline constexpr float BULLET_VELOCITY = 500.f;
	inline constexpr float MAX_BULLET_DISTANCE = 800.f;

	const sf::Time reloadTime = sf::seconds(0.3f);

	inline constexpr short int N_ASTEROIDS = 20;

	inline constexpr double PI = 3.1415926535897932;
}

namespace sprites {
	static const char* ship = "res/ship/ship.png";
	static const char* bigAsteroids = "res/asteroids/bigs.png";
	static const char* mediumAsteroids = "res/asteroids/meds.png";
	static const char* smallAsteroids = "res/asteroids/smalls.png";
	static const char* bullet = "res/bullet/bullet.png";
	
	inline constexpr unsigned int BIG_SIZE = 64;
	inline constexpr unsigned int MEDIUM_SIZE = 32;
	inline constexpr unsigned int SMALL_SIZE = 16;
}

namespace font {
	static const char* font = "res/font/Pixeltype.ttf";
	inline constexpr i32 size = 50;
}

namespace values {
	inline constexpr u16 bigAsteroid = 20;
	inline constexpr u16 mediumAsteroid = 50;
	inline constexpr u16 smallAsteroid = 100;
}

namespace audio {
	static const char* shootPath = "res/audio/shoot.wav";
}