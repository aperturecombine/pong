#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"

class Ball {
private:
	sf::Vector2f pos;
	sf::Vector2f vel;

	float size;

	float initSpeed;
	float speed;
	float deflection;

public:
	Ball();

	void update(float dt);
	sf::Vector2f getPos() { return pos; }
	float getSize() { return size; }

	void bounceTop();
	void bounceBot();

	void bounceLeft(float paddleY);
	void bounceRight(float paddleY);

	sf::Vector2f getVel() { return vel; }

	void resetLeft();
	void resetRight();

	int setSpeed() { return speed; }
	void setSpeed(int newSpeed) { speed = newSpeed; }
};

sf::Vector2f normalize(sf::Vector2f vec);