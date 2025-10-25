
#include <iostream>
#include "constants.h"
#include "SFML/Graphics.hpp"
#include "constants.h"
#include "times.h"
#include "entities.h"


Pipe::Pipe(sf::Texture& texture, float x, float y) : sf::Sprite{ texture } {
	setPosition(x, y);
}



PipePair::PipePair(Pipe* p1, Pipe* p2) {
	pipes = std::make_tuple(
		p1, p2
	);
}


PipePair::PipePair(sf::Texture& texture, float xPos, float yPos) {

}

void PipePair::draw(sf::RenderWindow& window) {
	auto p1 = *std::get<0>(pipes);
	auto p2 = *std::get<1>(pipes);
	window.draw(p1);
	window.draw(p2);
}

void PipePair::move(float pixels) {

	// wrap around screen
	if (xPos < -WIDTH) {
		pixels += CONST::PIPE_COUNT * CONST::PIPE_GAP;
		hasPoint = true;

		// set to random height
		auto position = (*getpipe(0)).getPosition();
		auto pipeX = position.x;
		auto pipeY = position.y;
		pipeY = static_cast<float>(randint(50, CONST::WINDOW_HEIGHT - 250));
		(*getpipe(0)).setPosition(pipeX, pipeY - HEIGHT);
		(*getpipe(1)).setPosition(pipeX, pipeY + 200.0f);

	}

	// move both pipes
	(*std::get<0>(pipes)).move(pixels, 0.0f);
	(*std::get<1>(pipes)).move(pixels, 0.0f);

	// reset object position attribute
	xPos = (*std::get<0>(pipes)).getPosition().x;
}

Pipe* PipePair::getpipe(int index) {
	if (!index) { return std::get<0>(pipes); }
	else { return std::get<1>(pipes); }
}


bool PipePair::checkCollision(float x, float y, float r) {

	// move bird position to reference center
	x += r / 2;
	y += r / 2;

	// get corner positions of pipes
	float x1 = xPos;
	float x2 = xPos + WIDTH;
	float y1 = getpipe(0)->getPosition().y + HEIGHT;
	float y2 = getpipe(1)->getPosition().y;

	return (
		(x + r / 2 > x1) &&
		(x - r / 2 < x2) &&
		(y < y1 || y > y2) ||
		(y < 0) || ((y + r) > CONST::WINDOW_HEIGHT)
	);
}

int PipePair::checkPassed(float x) {
	bool passed = ((x > xPos) && hasPoint);
	hasPoint = (!passed && hasPoint);
	return passed;
}