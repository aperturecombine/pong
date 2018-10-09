#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"
#include "HumanView.h"

class GameLogic {
private:
	Ball *ball;
	Paddle *rightPaddle;
	Paddle *leftPaddle;

	class HumanView *humanViewPt;

	bool gameOverState = false;
	bool running = true;

	const int WINSCORE = 11;
	int volleyCount = 0;

public:
	GameLogic();
	~GameLogic();
	
	int scoreRightInt = 0;
	int scoreLeftInt = 0;
	
	void update(float delta);

	void moveLeftPaddle(float dir);
	void moveRightPaddle(float dir);

	void GameLogic::paddleCollision(Paddle *p, float dir);

	void win();
	bool isGameOver() { return gameOverState; }

	void restartGame() {
		leftPaddle->reset();
		rightPaddle->reset();
		ball->resetRight();

		scoreRightInt = 0;
		scoreLeftInt = 0;

		gameOverState = false;
	}

	bool isRunning() { return running; }
	void shutdown() { running = false; }

	int getScoreLeft() { return scoreLeftInt; }
	int getScoreRight() { return scoreRightInt; }

	void scoreLeft() {
		scoreLeftInt += 1;
		ball->resetRight();
		leftPaddle->reset();
		rightPaddle->reset();
	}
	void scoreRight() {
		scoreRightInt += 1;
		ball->resetLeft();
		leftPaddle->reset();
		rightPaddle->reset();
	}

	sf::Vector2f getBallPos() { return ball->getPos(); }
	sf::Vector2f getLeftPaddlePos() { return leftPaddle->getPos(); }
	sf::Vector2f getRightPaddlePos() { return rightPaddle->getPos(); }

	float getBallSize() { return ball->getSize(); }
	float getLeftPaddleSize() { return leftPaddle->getSize(); }
	float getRightPaddleSize() { return rightPaddle->getSize(); }

	void setPointer(HumanView* pt) { humanViewPt = pt; }
};