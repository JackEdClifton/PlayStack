#pragma once


#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"
#include "SFML/Graphics.hpp"
#include "constants.h"
#include "times.h"


struct Bird : public sf::Sprite {

	// position
	const float width = 50.0f;
	const float height = 50.0f;
	const float xPos = 120.0f;

	// mechanics
	const float acceleration = 1000.0f;
	const float maxFallingVel = 400.0f;
	const float jumpVel = -400.0f;
	float vel = 0.0f;

	// graphics
	float flap = 0.0f;
	const float flapDelay = 0.1f;
	int texture = 0;
	sf::Texture texture_0, texture_1;

	// methods
	Bird(sf::Texture& Texture_0, sf::Texture Texture_1);
	void flapwing(float num);
};


// single pipe
struct Pipe : public sf::Sprite {

	// methods
	Pipe(sf::Texture& texture, float x, float y);
};

// pipe pairs
class PipePair {

	// store top and bottom pipes
	std::tuple<Pipe*, Pipe*> pipes;

	sf::Sprite pipeHi;
	sf::Sprite pipeLo;

	float xPos = 0.0f;
	bool hasPoint = 1;

public:
	const float WIDTH = 50.0f;
	const float HEIGHT = 800.0f;
	const float vel = -150.0f;


	// methods
	PipePair(Pipe* p1, Pipe* p2);
	PipePair(sf::Texture& texture, float xPos, float yPos);
	void draw(sf::RenderWindow& window);
	void move(float pixels);
	Pipe* getpipe(int index);
	bool checkCollision(float x, float y, float r);
	int checkPassed(float x);
};