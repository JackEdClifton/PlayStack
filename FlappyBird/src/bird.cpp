#pragma once

#include <SFML/Graphics.hpp>
#include "entities.h"

// methods
Bird::Bird(sf::Texture& Texture_0, sf::Texture Texture_1) {
	setPosition(xPos, 250.0f);
	texture_0 = Texture_0;
	texture_1 = Texture_1;
}

void Bird::flapwing(float num) {
	flap += num;
	if (flap > flapDelay) {
		flap -= flapDelay;
		texture = !texture;
		if (texture) { setTexture(texture_1); }
		else { setTexture(texture_0); }
	}
}




