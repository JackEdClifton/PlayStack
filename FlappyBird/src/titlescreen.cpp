
// modules and libraries
#include "SFML/Graphics.hpp"
#include "constants.h"
#include "gameModes.h"

// start menu
void titlescreen() {

	// window
	sf::RenderWindow window(sf::VideoMode(CONST::WINDOW_WIDTH, CONST::WINDOW_HEIGHT), "Flappy Bird", sf::Style::Close);
	sf::Image icon; icon.loadFromFile("assets/icons/bird.png");
	icon.getSize();
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


	// background object
	sf::Texture t_background;
	sf::Texture t_titlescreen;
	t_background.loadFromFile("assets/images/background.psd");
	t_titlescreen.loadFromFile("assets/images/titlescreen.psd");
	sf::Sprite background(t_background);
	sf::Sprite titlescreen(t_titlescreen);

	// mainloop for title screen
	sf::Event events;
	while (window.isOpen()) {

		// update display
		window.display();
		window.clear();
		window.draw(background);
		window.draw(titlescreen);

		// interupt events
		while (window.pollEvent(events)) {
			if (events.type == events.Closed) { window.close(); } // close
			if (events.type == sf::Event::TextEntered) {
				if (events.text.unicode == 32) { runGame(window); } // run game when space is pressed
			}
		}

		// run when start button clicked*/
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mousepos = sf::Mouse::getPosition();
			sf::Vector2i windowpos = window.getPosition();
			mousepos -= windowpos;
			if (mousepos.x > 198 && mousepos.x < 397) {
				if (mousepos.y > 343 && mousepos.y < 442) {
					runGame(window);
				}
			}
		}
	}
}