#pragma once
#include <SFML\graphics.hpp>
#include <SFML\Audio.hpp>
#include "GameLogic.h"

class HumanView {
private:
	sf::Font font;
	sf::SoundBuffer soundBuffer;
	sf::Sound oofSound;
	class GameLogic *logicPt;

public:
	HumanView();

	void handleInput();
	void draw(sf::RenderWindow &App);
	void bounceSound();

	void setPointer(GameLogic *l) { logicPt = l; }
};