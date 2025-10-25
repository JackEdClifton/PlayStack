#pragma once
#include "SFML/Graphics.hpp"

/* score text */
struct ScoreText : sf::Font, sf::Text {
	int score = 0;
	sf::Font font;
	sf::Text text;
	
	ScoreText() {
		font.loadFromFile("assets/Fonts/Pangolin-Regular.ttf");
		text.setFont(font);
		text.setFillColor(sf::Color::Color(0, 0, 0));
		text.setPosition(280, 10);
		text.setString("0");
	}
	
	void addPoint() {
		score++;
		text.setString(std::to_string(score));
	}
};