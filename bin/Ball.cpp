#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Ball::Ball() {
	//radius of the ball
	size = 10;

	//set a basic minimum speed after scoring
	initSpeed = 350;
	speed = initSpeed;

	//amount of deflection due to paddle/ball collision
	deflection = 6;

	resetLeft();
}

void Ball::update(float delta) {
	pos += vel * delta;
}

// bounce on the top wall
void Ball::bounceTop() { vel.y = abs(vel.y); }
// bounce on the bottom wall
void Ball::bounceBot() { vel.y = -abs(vel.y); }

// bounce on the left paddle
void Ball::bounceLeft(float paddleY) {
	// get the distance from the center of the paddle to the hit
	float difference = pos.y - paddleY;
	// multiply it by the deflection and add to the y velocity
	vel.y += difference * deflection;

	vel.x = abs(vel.x);
	// normalize the velocity to maintain the constant speed
	vel = normalize(vel)*speed;
}

// bounce on the right paddle
void Ball::bounceRight(float paddleY) {
	float difference = pos.y - paddleY;
	vel.y += difference * deflection;
	
	vel.x = -abs(vel.x);
	vel = normalize(vel)*speed;
}

// reset the ball after left (human) scores
void Ball::resetLeft() {
	pos = sf::Vector2f(400, 300);
	// revert to the inital speed
	speed = initSpeed;

	// pick a random angle to launch the ball
	int randY = std::rand() % 200 - 100;
	vel = normalize(sf::Vector2f(speed, randY)) * speed;
}


// reset the ball after left (ai) scores
void Ball::resetRight() {
	pos = sf::Vector2f(400, 300);
	speed = initSpeed;

	int randY = std::rand() % 200 - 100;
	vel = normalize(sf::Vector2f(-speed, randY)) * speed;
}

//normalize vectors for maintaining a constant speed/magnitude of velocity
sf::Vector2f normalize(sf::Vector2f vec) {
	float length = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	return vec / length;
}