#include "GameLogic.h"
#include <iostream>

GameLogic::GameLogic() {
	ball = new Ball();
	leftPaddle = new Paddle(sf::Vector2f(10,300));
	rightPaddle = new Paddle(sf::Vector2f(780,300));
}

GameLogic::~GameLogic() { }

void GameLogic::update(float dt) {
	// check if either player has won
	if (getScoreLeft() >= WINSCORE || getScoreRight() >= WINSCORE) { win(); }

	// if the volley (paddle bounces) count is greater than 3, increase the ball speed;
	if (volleyCount >= 3) {
		ball->setSpeed(ball->setSpeed() + 25);
		volleyCount = 0;
	}

	sf::Vector2f ballPos = ball->getPos();
	float size = ball->getSize();

	// top and bottom collision checks
	if (ballPos.y < 0 + size) { ball->bounceTop(); }
	if (ballPos.y >= 600 - size) { ball->bounceBot(); }

	// score collision checks
	if (ballPos.x < 0 + size) { scoreRight(); }
	if (ballPos.x > 800 - size) { scoreLeft(); }

	// left paddle collision check. If the ball is in the valid x range,
	//  is within the top and bottom of the paddle, and is moving left
	if ((ballPos.x - size < 25 && ballPos.x - size > 10) &&
		(ballPos.y > leftPaddle->getPos().y - leftPaddle->getSize()/2 - 5) &&
		(ballPos.y < leftPaddle->getPos().y + leftPaddle->getSize()/2 + 5) &&
		ball->getVel().x < 0) {

		// increase the volley/bounce count
		volleyCount++;
		humanViewPt->bounceSound();

		// bounce off of the left paddle
		ball->bounceLeft(leftPaddle->getPos().y);
	}

	// right paddle collision check. If the ball is in the valid x range,
	//  is within the top and bottom of the paddle, and is moving right
	if ((ballPos.x + size < 800 - 10 && ballPos.x + size > 785) &&
		(ballPos.y > rightPaddle->getPos().y - rightPaddle->getSize() / 2 - ball->getSize()) &&
		(ballPos.y < rightPaddle->getPos().y + rightPaddle->getSize() / 2 + ball->getSize()) &&
		ball->getVel().x > 0) {

		volleyCount++;
		humanViewPt->bounceSound();
		ball->bounceRight(rightPaddle->getPos().y);
	}

	ball->update(dt);
	leftPaddle->update(dt);
	rightPaddle->update(dt);
}

void GameLogic::moveLeftPaddle(float dir) {
	paddleCollision(leftPaddle, dir);
}

void GameLogic::moveRightPaddle(float dir) {
	paddleCollision(rightPaddle, dir);
}

void GameLogic::paddleCollision(Paddle *p, float dir) {
	// make sure that the paddle is within the screen's bounds when it moves
	float paddleBot = p->getPos().y - p->getSize() / 2;
	float paddleTop = p->getPos().y + p->getSize() / 2;

	if (dir < 0 && paddleBot > 0 || dir > 0 && paddleTop < 600) {
		p->move(dir);
	}
}

void GameLogic::win() {
	gameOverState = true;
}