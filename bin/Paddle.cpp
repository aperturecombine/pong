#include "Paddle.h"

Paddle::Paddle(sf::Vector2f p) {
	pos = p;
	size = 120;
	speed = 220;
	dir = 0;
}

Paddle::~Paddle() { }

void Paddle::update(float dt) {
	pos.y += speed * dir * dt;
	dir = 0;
}

void Paddle::move(int d) {
	dir = d;
}

void Paddle::reset() {
	pos.y = 300;
}