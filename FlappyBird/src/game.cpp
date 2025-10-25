



// modules and libraries
#include "SFML/Graphics.hpp"
#include "constants.h"
#include "entities.h"
#include "text.h"
#include "times.h"



// main
void runGame(sf::RenderWindow& window) {

	// starting stuff
	using namespace std;
	FrameTimer frame = FrameTimer();

	// text & fonts
	ScoreText score = ScoreText();

	// declare textures
	sf::Texture t_background;
	sf::Texture t_bird0;
	sf::Texture t_bird1;
	sf::Texture t_pipebase;
	sf::Texture t_piperoof;

	// load textures
	t_background.loadFromFile("assets/images/background.psd");
	t_bird0.loadFromFile("assets/images/flappybird_0.psd");
	t_bird1.loadFromFile("assets/images/flappybird_1.psd");
	t_pipebase.loadFromFile("assets/images/pipebase.psd");
	t_piperoof.loadFromFile("assets/images/piperoof.psd");
	
	// create bird
	Bird bird(t_bird0, t_bird1);

	// create pipes
	vector<PipePair> pipePairs;
	for (int i = 0; i < CONST::PIPE_COUNT; i++) {
		Pipe* pipe1 = new Pipe(t_piperoof, CONST::PIPE_FIRST_X + CONST::PIPE_GAP * i, -500.0f);
		Pipe* pipe2 = new Pipe(t_pipebase, CONST::PIPE_FIRST_X + CONST::PIPE_GAP * i, 500.0f);
		PipePair pipePair(pipe1, pipe2);
		pipePairs.push_back(pipePair);
	}

	// create objects
	sf::Sprite background(t_background);
	sf::Event events;

	// mainloop for game
	while (window.isOpen()) {

		// update display
		window.display();
		window.clear();
		window.draw(background);
		frame.update();

		// interupt events
		while (window.pollEvent(events)) {
			if (events.type == events.Closed) { window.close(); }
			if (events.type == sf::Event::TextEntered) {
				if (events.text.unicode == 32) { bird.vel = -400; } // jump
			}
		}

		// iterate through pipes
		for (auto &pipePair : pipePairs) {

			// move pipe
			pipePair.move(pipePair.vel * frame.delta);
			pipePair.draw(window);

			// check collision with bird
			if (pipePair.checkCollision(bird.xPos, bird.getPosition().y, bird.width / 2.0f)) {
				sleep(1.0f);
				return;
			}

			// get point if passed
			if (pipePair.checkPassed(bird.xPos))
				score.addPoint();
		}

		// move bird
		bird.vel += bird.acceleration * frame.delta;
		if (bird.vel > bird.maxFallingVel)
			bird.vel = bird.maxFallingVel;
		bird.move(0.0f, bird.vel * frame.delta);
		bird.flapwing(frame.delta);

		// draw
		window.draw(bird);
		window.draw(score.text);
	}
}