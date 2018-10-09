#include <iostream>
#include "main.h"

using namespace std;

int main(int argc, char** argv) {
	// boolean to check when window is minimized
	bool paused = false;

	// create main window
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Pong - SFML", sf::Style::Titlebar | sf::Style::Close);

	// instantiate the GameLogic and the HumanView
	GameLogic gameLogic = GameLogic();
	HumanView humanView = HumanView();
	// set pointers to each other for referencing
	humanView.setPointer(&gameLogic);
	gameLogic.setPointer(&humanView);

	// instantiate the AIView
	AIView aiView = AIView(&gameLogic);

	// load and play the music
	if (!music.openFromFile("africa.wav")) {
		std::cout << "sound load error" << std::endl;
	}
	music.setVolume(30);
	music.play();

	// start main loop
	sf::Clock clock;
	while (gameLogic.isRunning()) {
		sf::Time delta = clock.getElapsedTime();
		sf::Event event;
		while (App.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				gameLogic.shutdown();
			// if the window is minimized, pause and pause music
			else if (event.type == sf::Event::LostFocus) {
				paused = true;
				music.pause();
			}
			// if the window regains focus, unpause and play music
			else if (event.type == sf::Event::GainedFocus) {
				paused = false;
				music.play();
			}
		}
		humanView.handleInput();

		// if in play state, update and step the AI
		if (!gameLogic.isGameOver() && !paused) {
			aiView.step();
			gameLogic.update(delta.asSeconds() * 1000);
		}

		humanView.draw(App);

		App.display();
		clock.restart();
	}
	return 0;
}