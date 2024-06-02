#include <iostream>
#include <fstream>
#include <filesystem>
#include "../headers/AsteroidManager.hpp"

namespace gbl {
	std::string path;
	ErrorManager ERRORS;
	TextureManager textureManager;
	float dt;
}

// kids, don't try this at home
using namespace std::string_literals;

std::optional<u64> readHighScore() {
	std::ifstream file(gbl::path + "res/highScore.txt");
	if (!file.is_open() || file.bad()) {
		gbl::ERRORS.addError("Failed to load highScore.txt!");
		return std::nullopt;
	}

	u64 score{};
	file >> score;

	file.close();
	return score;
}

void writeHighScore(u64 score) {
	std::ofstream file(gbl::path + "res/highScore.txt");
	file << score << std::endl;
	file.close();
}

int main(int argc, char** argv) {
	sf::RenderWindow window(sf::VideoMode(consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT), "ASTEROIDS", sf::Style::Close | sf::Style::Titlebar);

	if (!window.isOpen()) {
		std::cerr << "Window failed to load window!\n";
		return EXIT_FAILURE;
	}

	gbl::path = std::filesystem::current_path().parent_path().string() + "/";

	gbl::textureManager.load();

	sf::Event event;
	sf::Clock clock;
	i64 score{};
	u64 highScore{};
	sf::Text text;

	Ship ship({consts::WINDOW_WIDTH / 2.f, consts::WINDOW_HEIGHT / 2.f}, {0.f, 0.f});
	AsteroidManager asteroidManager(ship);

	if (gbl::ERRORS.hasError()) {
		gbl::ERRORS.print();
		window.close();
		return EXIT_FAILURE;
	}

	auto highScoreOpt = readHighScore();
	if (!highScoreOpt.has_value()) {
		gbl::ERRORS.print();
		window.close();
		return EXIT_FAILURE;
	}
	highScore = highScoreOpt.value();

	text.setFont(gbl::textureManager.getFont());
	text.setCharacterSize(font::size);
	text.setFillColor({200, 200, 200, 200});
	text.setPosition({10.f, -10.f});
	text.setString("SCORE: 0	HS: " + std::to_string(highScore));

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				return 0;
			
			case sf::Event::KeyPressed:

				switch(event.key.code) {
				case sf::Keyboard::Escape:
					window.close();
					return 0;
				}
			}
		}

		gbl::dt = clock.restart().asSeconds();

		ship.update();
		asteroidManager.update(ship);

		if (ship.hasDied())
			window.close();

		if (score != ship.getScore()) {
			score = ship.getScore();
			if (score > highScore) {
				highScore = score;
				writeHighScore(highScore);
			}
			text.setString("SCORE: "s + std::to_string(score) + "	HS: " + std::to_string(highScore));
		}

		window.clear({50, 50, 50});

		ship.render(window);
		asteroidManager.render(window);

		window.draw(text);

		window.display();
	}
	return 0;
}