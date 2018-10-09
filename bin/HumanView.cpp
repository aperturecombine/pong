#include "HumanView.h"
#include <iostream>

using namespace std;

HumanView::HumanView() {

	//load font and oof sound effect
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "font load error" << std::endl;
	}
	if (!soundBuffer.loadFromFile("oof.wav")) {
		std::cout << "sound load error" << std::endl;
	}
	oofSound.setBuffer(soundBuffer);
}

void HumanView::handleInput() {

	//if in play state
	if (!logicPt->isGameOver()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			logicPt->moveLeftPaddle(-1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			logicPt->moveLeftPaddle(1);
		}
	}
	//if in game over state
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			logicPt->restartGame();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			logicPt->shutdown();
		}
	}
}

void HumanView::draw(sf::RenderWindow &App) {
	App.clear(sf::Color::Black);

	// draw score text
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setString(std::to_string(logicPt->getScoreLeft()) + " : " + std::to_string(logicPt->getScoreRight()));
	scoreText.setCharacterSize(40);
	scoreText.setFillColor(sf::Color::White);
	// create rectangle for centering text
	sf::FloatRect textRect = scoreText.getLocalBounds();
	scoreText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	scoreText.setPosition(sf::Vector2f(800 / 2.0f, 50));
	App.draw(scoreText);

	//if in play state
	if (!logicPt->isGameOver()) {
		// draw ball
		sf::CircleShape ballShape(logicPt->getBallSize());
		sf::Vector2f drawPos = sf::Vector2f(logicPt->getBallPos().x - logicPt->getBallSize(),
			logicPt->getBallPos().y - logicPt->getBallSize());
		ballShape.setPosition(drawPos);
		ballShape.setFillColor(sf::Color(255, 255, 0));
		App.draw(ballShape);

		// draw left paddle
		sf::RectangleShape leftPaddleShape;
		leftPaddleShape.setSize(sf::Vector2f(15, logicPt->getLeftPaddleSize()));
		leftPaddleShape.setFillColor(sf::Color(255, 0, 0));
		drawPos = sf::Vector2f(logicPt->getLeftPaddlePos().x,
			logicPt->getLeftPaddlePos().y - logicPt->getLeftPaddleSize() / 2);
		leftPaddleShape.setPosition(drawPos);
		App.draw(leftPaddleShape);

		// draw right paddle
		sf::RectangleShape rightPaddleShape;
		rightPaddleShape.setSize(sf::Vector2f(15, logicPt->getRightPaddleSize()));
		rightPaddleShape.setFillColor(sf::Color(255, 0, 0));
		drawPos = sf::Vector2f(logicPt->getRightPaddlePos().x,
			logicPt->getRightPaddlePos().y - logicPt->getRightPaddleSize() / 2);
		rightPaddleShape.setPosition(drawPos);
		App.draw(rightPaddleShape);
	}

	// if in game over state
	else if(logicPt->isGameOver()){
		// draw game over text
		sf::Text gameOverText;
		gameOverText.setFont(font);
		// determine who actually won and create the string
		std::string whoWonText = (logicPt->getScoreLeft() > logicPt->getScoreRight()) ? "You" : "Computer";
		gameOverText.setString(whoWonText + " won!\nPress SPACE to restart\nor Q to quit!");
		gameOverText.setCharacterSize(60);
		gameOverText.setFillColor(sf::Color::White);
		// creaet a rectangle for centering the text
		sf::FloatRect textRect = gameOverText.getLocalBounds();
		gameOverText.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		gameOverText.setPosition(sf::Vector2f(400, 150));
		App.draw(gameOverText);
	}
}

void HumanView::bounceSound() {
	oofSound.play();
}