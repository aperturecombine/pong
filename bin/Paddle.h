#pragma once
#include <SFML/graphics.hpp>

class Paddle
{
private:
	sf::Vector2f pos;
	float size;
	float speed;
	int dir;

public:
	Paddle(sf::Vector2f p);
	~Paddle();

	void update(float dt);
	void move(int dir);

	void reset();

	sf::Vector2f getPos() { return pos; }
	float getSize() { return size; }
};